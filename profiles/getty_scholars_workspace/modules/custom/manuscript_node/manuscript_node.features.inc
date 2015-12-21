<?php
/**
 * @file
 * manuscript_node.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function manuscript_node_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function manuscript_node_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function manuscript_node_node_info() {
  $items = array(
    'manuscript' => array(
      'name' => t('Transcription'),
      'base' => 'node_content',
      'description' => t('<em>Manuscripts</em> have a built-in hierarchical navigation. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
