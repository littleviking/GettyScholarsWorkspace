<?php
/**
 * @file
 * project_dashboard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function project_dashboard_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function project_dashboard_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function project_dashboard_image_default_styles() {
  $styles = array();

  // Exported image style: project_carousel_thumb.
  $styles['project_carousel_thumb'] = array(
    'label' => 'project_carousel_thumb',
    'effects' => array(
      4 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 111,
          'height' => 100,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: project_dashboard_header.
  $styles['project_dashboard_header'] = array(
    'label' => 'project_dashboard_header',
    'effects' => array(
      5 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 250,
          'height' => 250,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
