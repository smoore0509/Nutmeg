<?php

/**
 * @file
 * Handles rate request/response related stuff for the Commerce USPS module.
 */

/**
 * Builds the USPS rate request.
 *
 * @param object $order
 *   The commerce order object
 *
 * @return string
 *   A USPS Web Tools XML request string
 */
function commerce_usps_build_rate_request($order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);

  // Determine the shipping profile reference field name for the order.
  $field_name = commerce_physical_order_shipping_field_name($order);
  $shipping_profile = $order_wrapper->{$field_name}->value();

  // Prepare the shipping address for use in the request.
  if (!empty($order_wrapper->{$field_name}->commerce_customer_address)) {
    $shipping_address = $order_wrapper->{$field_name}->commerce_customer_address->value();
  }
  else {
    $shipping_address = addressfield_default_values();
  }

  // Get the orders weight and calculate lbs and ozs.
  // @todo: Create multiple packages if over 70 lbs.
  $weight = commerce_physical_order_weight($order, 'lb');
  // If order contains no weight skip sending request to usps.
  if (!is_array($weight) || $weight['weight'] == NULL) {
      return FALSE;
  }
  $ounces = 16 * ($weight['weight'] - floor($weight['weight']));
  $pounds = floor($weight['weight']);

  // Build a USPS request.
  // @todo: Implement additional options for more accurate shipping quotes
  // (see https://www.usps.com/webtools/htm/Rate-Calculators-v1-3.htm).
  $request = new SimpleXMLElement('<RateV4Request/>');
  $request->addAttribute('USERID', variable_get('commerce_usps_user', ''));

  // Add a package to the request for each enabled service.
  $i = 1;
  foreach (variable_get('commerce_usps_services', array()) as $service) {
    if ($service) {
      $package = $request->addChild('Package');
      $package->addAttribute('ID', $i);
      $package->addChild('Service', $service);
      $package->addChild('FirstClassMailType', 'PARCEL');
      $package->addChild('ZipOrigination', variable_get('commerce_usps_postal_code', ''));
      $package->addChild('ZipDestination', $shipping_address['postal_code']);
      $package->addChild('Pounds', $pounds);
      $package->addChild('Ounces', $ounces);
      $package->addChild('Container', 'VARIABLE');
      $package->addChild('Size', 'REGULAR');
      $package->addChild('Machinable', 'TRUE');
      ++$i;
    }
  }

  return 'API=RateV4&XML=' . $request->asXML();
}

/**
 * Submits an API request to USPS.
 *
 * @param string $request
 *   A request string.
 * @param string $message
 *   Optional log message.
 *
 * @return string
 *   XML string response from USPS
 */
function commerce_usps_api_request($request, $message = '') {
  // Log the API request if specified.
  // @todo: Add ability for admin to toggle logging of request.
  // if (in_array('request', variable_get('commerce_usps_log', array()))) {
  if (empty($message)) {
    $message = t('Submitting API request to USPS.');
  }
  watchdog('usps', '@message:<pre>@request</pre>', array('@message' => $message, '@request' => $request));
  // }
  // Send the request.
  $response = drupal_http_request(variable_get('commerce_usps_connection_address', 'http://Production.ShippingAPIs.com/ShippingAPI.dll'), array('method' => 'POST', 'data' => $request));

  // If we received a response.
  if (!empty($response->data)) {
    // Log the API request if specified.
    // @todo: Add ability for admin to toggle logging of response.
    // if (in_array('response', variable_get('commerce_usps_log', array()))) {
      watchdog('usps', 'Response code:@code<br />Response:<pre>@response</pre>', array('@code' => $response->code, '@response' => $response->data));
    // }
    // Return the response as an XML response object.
    return new SimpleXMLElement($response->data);
  }

  return FALSE;
}
