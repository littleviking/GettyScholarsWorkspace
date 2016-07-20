<?php
/**
 * @file
 * lighttable.features.inc
 */

/**
 * Implements hook_views_api().
 */
function lighttable_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function lighttable_image_default_styles() {
  $styles = array();

  // Exported image style: lighttable_main.
  $styles['lighttable_main'] = array(
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 450,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 450,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'lighttable_main',
  );

  // Exported image style: lighttable_thumb.
  $styles['lighttable_thumb'] = array(
    'effects' => array(
      5 => array(
        'name' => 'image_resize',
        'data' => array(
          'width' => 75,
          'height' => 75,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'lighttable_thumb',
  );

  return $styles;
}
