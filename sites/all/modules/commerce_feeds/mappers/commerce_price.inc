<?php

/**
 * @file
 * On behalf implementation of Feeds mapping API for commerce_price.module.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 *
 * @see FeedsNodeProcessor::getMappingTargets().
 */
function _commerce_price_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);
    if ($info['type'] == 'commerce_price') {
      $targets[$name . ":amount"] = array(
        'name' => $instance['label'] . ': Amount',
        'callback' => 'commerce_price_feeds_set_target',
        'description' => t('The price amount for the @name field.', array('@name' => $instance['label'])),
        'real_target' => $name,
      );
      $targets[$name . ":currency_code"] = array(
        'name' => $instance['label'] . ': Currency',
        'callback' => 'commerce_price_feeds_set_target',
        'description' => t('The currency for the @name field.', array('@name' => $instance['label'])),
        'real_target' => $name,
      );
    }
  }
}

/**
 * Callback for mapping. Here is where the actual mapping happens.
 *
 * When the callback is invoked, $target contains the name of the field the
 * user has decided to map to and $value contains the value of the feed item
 * element the user has picked as a source.
 */
function commerce_price_feeds_set_target($source, $entity, $target, $value) {
  if (!isset($value)) {
    return;
  }

  // Handle non-multiple value fields.
  if (!is_array($value)) {
    $value = array($value);
  }

  // Get field information.
  list($field_name, $sub_field) = explode(':', $target);
  $info = field_info_field($field_name);
  $field = isset($entity->$field_name) ? $entity->$field_name : array();

  // Iterate over all values.
  foreach ($value as $i => $v) {
    if (!is_array($v) && !is_object($v)) {
      // always put the default currency
      $field[LANGUAGE_NONE][$i]['currency_code'] = commerce_default_currency();
      if ($sub_field == 'amount') {
        $field[LANGUAGE_NONE][$i]['amount'] = (!empty($v) && is_numeric($v)) ? $v : 0;
        if (module_exists('commerce_tax')) {
          $config = $source->importer->getConfig();
          if (!empty($config['processor']['config']['tax_rate'])) {
            $field[LANGUAGE_NONE][$i]['data']['include_tax'] = $config['processor']['config']['tax_rate'];
          }
        }
      }
      elseif ($sub_field == 'currency_code') {
        $field[LANGUAGE_NONE][$i]['currency_code'] = $v;
      }
    }
    if ($info['cardinality'] == 1) {
      break;
    }
  }
  
  $entity->{$field_name} = $field;
}
