<?php

/**
 * @file
 * Implement a cropzoom format for image fields.
 */

/**
 * Implements hook_field_formatter_info().
 */
function cropzoom_field_formatter_info() {
  return array(
    'cropzoom_image' => array(
      'label' => t('CropZoom Image'),
      'field types' => array('image'),
      'settings' => array('image_style' => '', 'image_link' => '', 'enable_cropzoom' => 1),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function cropzoom_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  
  // Use image formatter as base, and add CropZoom option
  $element = image_field_formatter_settings_form($field, $instance, $view_mode, $form, $form_state);
  $element['enable_cropzoom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable CropZoom'),
    '#default_value' => $settings['enable_cropzoom'],
  );

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function cropzoom_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  // User image formatter summary as base, then add CropZoom summary
  $summary = image_field_formatter_settings_summary($field, $instance, $view_mode);

  if (isset($settings['enable_cropzoom']) && $settings['enable_cropzoom']) {
    $summary .= '<br />CropZoom: enabled';
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function cropzoom_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $elements = array();
  // Use image formatter view as base, but use our own theme
  $elements = image_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display);

  foreach ($elements as $delta => $element) {
    $elements[$delta]['#enable_cropzoom'] = $display['settings']['enable_cropzoom'];
    $elements[$delta]['#theme'] = 'cropzoom_image_formatter';
  }

  return $elements;
}

/**
 * Returns HTML for a field formatter.
 *
 * @param $variables
 *   An associative array containing:
 *   - item: Associative array of image data, which may include "uri", "alt",
 *     "width", "height", "title" and "attributes".
 *   - image_style: An optional image style.
 *   - path: An array containing the link 'path' and link 'options'.
 *
 * @ingroup themeable
 */
function theme_cropzoom_image_formatter($variables) {
  drupal_add_library('system', 'ui');
  drupal_add_library('system', 'ui.droppable');
  drupal_add_library('system', 'ui.resizable');
  drupal_add_library('system', 'ui.slider');
  drupal_add_library('system', 'ui.dialog');

  $item = $variables['item'];
  $nid = arg(1);

  // Get group ID for the node
  $node = node_load($nid);
  if (isset($node->og_group_ref['und'][0]['target_id'])) {
    $gid = $node->og_group_ref['und'][0]['target_id'];
  }
  else {
    $gid = NULL;
  }

  // Add this attribute
  $item['attributes'] = array(
    'class' => 'cropzoom-image'
  );

  $image = array(
    'path' => $item['uri'],
  );

  if (array_key_exists('alt', $item)) {
    $image['alt'] = $item['alt'];
  }

  if (isset($item['attributes'])) {
    $image['attributes'] = $item['attributes'];
  }

  if (isset($item['width']) && isset($item['height'])) {
    $image['width'] = $item['width'];
    $image['height'] = $item['height'];
  }

  // Do not output an empty 'title' attribute.
  if (isset($item['title']) && drupal_strlen($item['title']) > 0) {
    $image['title'] = $item['title'];
  }

  if ($variables['image_style']) {
    $image['style_name'] = $variables['image_style'];
    $img_output = theme('image_style', $image);
  }
  else {
    $img_output = theme('image', $image);
  }

  // The link path and link options are both optional, but for the options to be
  // processed, the link path must at least be an empty string.
  if (isset($variables['path']['path'])) {
    $path = $variables['path']['path'];
    $options = isset($variables['path']['options']) ? $variables['path']['options'] : array();
    // When displaying an image inside a link, the html option must be TRUE.
    $options['html'] = TRUE;
    $img_output = l($img_output, $path, $options);
  }

  if ($variables['enable_cropzoom'] && isset($gid) && og_user_access('node', $gid, 'access cropzoom')) {
    // Add markup for cropping and zooming
    $img_container = theme('cropzoom_display', array('czid' => 'cropzoom-f-' . $item['fid'], 'gid' => $gid, 'nid' => $nid, 'fid' => $item['fid'], 'image_output' => $img_output));
    $output = theme('cropzoom_container_display', array('nid' => $nid, 'fid' => $item['fid'], 'image_container' => $img_container));
  }
  else {
    $output = $img_output;
  }

  return $output;
}
