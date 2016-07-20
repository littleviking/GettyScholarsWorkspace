<?php
/**
 * @file
 * comparison_node.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function comparison_node_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_image_references'.
  $field_bases['field_image_references'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_image_references',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'type' => 'none',
        ),
        'target_bundles' => array(
          'image' => 'image',
        ),
      ),
      'target_type' => 'file',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
