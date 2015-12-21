<?php
/**
 * @file
 * image_node.file_default_displays.inc
 */

/**
 * Implements hook_file_default_displays().
 */
function image_node_file_default_displays() {
  $export = array();

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => '',
    'alt' => '',
    'title' => '',
  );
  $export['image__default__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__teaser__file_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'thumbnail',
    'alt' => '',
    'title' => '',
  );
  $export['image__teaser__file_image'] = $file_display;

  return $export;
}
