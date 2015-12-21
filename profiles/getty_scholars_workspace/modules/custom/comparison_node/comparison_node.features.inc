<?php
/**
 * @file
 * comparison_node.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function comparison_node_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function comparison_node_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function comparison_node_node_info() {
  $items = array(
    'comparison' => array(
      'name' => t('Comparison'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
