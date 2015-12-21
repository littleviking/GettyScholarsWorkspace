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
    'name' => 'lighttable_main',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 450,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      3 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
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
    'name' => 'lighttable_thumb',
    'effects' => array(
      5 => array(
        'label' => 'Resize',
        'help' => 'Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.',
        'effect callback' => 'image_resize_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
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
