<?php

/**
 * @file
 * Wysiwyg API integration on behalf of Node module.
 */

/**
 * Implementation of hook_wysiwyg_plugin().
 */
function comparison_plugin_comparison_reference_plugin() {
  $plugins['comparison_reference'] = array(
    'title' => t('Comparison Reference'),
    'vendor url' => 'http://drupal.org/project/wysiwyg',
    'icon file' => 'comparison_image.png',
    'icon title' => t('Add Reference to Comparison Image'),
    'settings' => array(),
  );
  return $plugins;
}