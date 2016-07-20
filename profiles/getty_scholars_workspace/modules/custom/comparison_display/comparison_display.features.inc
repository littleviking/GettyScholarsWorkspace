<?php
/**
 * @file
 * comparison_display.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function comparison_display_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function comparison_display_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function comparison_display_image_default_styles() {
  $styles = array();

  // Exported image style: comparison_slider.
  $styles['comparison_slider'] = array(
    'label' => 'comparison_slider',
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 400,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
