<?php

/**
 * @file
 * Wysiwyg API integration on behalf of Node module.
 */
/**
 * Implementation of hook_wysiwyg_plugin().
 */
function bibliography_plugin_bibliography_reference_plugin() {
  $plugins['bibliography_reference'] = array(
    'title' => t('Bibliography Reference'),
    'vendor url' => 'http://drupal.org/project/wysiwyg',
    'icon file' => 'bibliography_image.png',
    'icon title' => t('Add Bibliography Reference'),
    'settings' => array(),
  );
  return $plugins;
}