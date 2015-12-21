<?php

/**
 * @file
 * Wysiwyg API integration on behalf of Node module.
 */

/**
 * Implementation of hook_wysiwyg_plugin().
 */
function project_image_plugin_project_image_reference_plugin() {
  $plugins['project_image_reference'] = array(
    'title' => t('Project Image Reference'),
    'vendor url' => 'http://drupal.org/project/wysiwyg',
    'icon file' => 'project_image.png',
    'icon title' => t('Add Project Image'),
    'settings' => array(),
  );
  return $plugins;
}