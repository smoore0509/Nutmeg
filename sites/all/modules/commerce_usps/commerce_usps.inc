<?php

/**
 * @file
 * Admin functions for Commerce USPS.
 */

/**
 * Form builder function for module settings.
 *
 * @return string
 *   Drupal form for USPS settings
 */
function commerce_usps_settings() {
  $form['origin'] = array(
    '#title' => t('Ship from location'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );
  $form['origin']['commerce_usps_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#default_value' => variable_get('commerce_usps_postal_code', ''),
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Shipment Settings'),
    '#collapsible' => TRUE,
  );
  $form['settings']['commerce_usps_services'] = array(
    '#type' => 'checkboxes',
    '#title' => t('USPS Services'),
    '#description' => t('Select the USPS services that are available to customers.'),
    '#default_value' => variable_get('commerce_usps_services', array()),
    '#options' => commerce_usps_service_list(),
  );
  $form['settings']['commerce_usps_markup_type'] = array(
    '#type' => 'select',
    '#title' => t('Markup type'),
    '#default_value' => variable_get('commerce_usps_markup_type', 'percentage'),
    '#options' => array(
      'percentage' => t('Percentage (%)'),
      'amount' => t('Amount ($)'),
    ),
  );
  $form['settings']['commerce_usps_markup'] = array(
    '#type' => 'textfield',
    '#title' => t('Shipping rate markup'),
    '#default_value' => variable_get('commerce_usps_markup', '0'),
    '#description' => t('Markup shipping rate quote by a percentage or an amount.'),
  );
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('USPS Connection Settings'),
    '#collapsed' => variable_get('commerce_usps_user', FALSE),
    '#collapsible' => TRUE,
  );
  $form['api']['commerce_usps_connection_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Connection Address'),
    '#default_value' => variable_get('commerce_usps_connection_address', 'http://production.shippingapis.com/ShippingAPI.dll'),
    '#required' => TRUE,
  );
  $form['api']['commerce_usps_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => variable_get('commerce_usps_user', ''),
    '#description' => t('The user name for your USPS account.'),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}
