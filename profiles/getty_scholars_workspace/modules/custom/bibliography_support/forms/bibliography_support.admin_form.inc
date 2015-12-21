<?php

/**
 *  @function:
 *    This function is used to provide an admin with a user interface to map biblio to ris
 */
function bibliography_support_admin_form() {
  //variables
  $form = array();
  $available_fields = _getty_bibliography_support_available_fields();
  $variable_name = 'getty_biblio_available_fields';

  //creates a checkbox area
  $form[$variable_name] = array(
    '#type' => 'checkboxes',
    '#title' => t('Available Fields from Bibliography'),
    '#description' => t('Check the fields that you would like to be exposed within the RIS and RDF configuration. More control on those pages.'),
    '#options' => drupal_map_assoc($available_fields),
    '#default_value' => variable_get($variable_name, drupal_map_assoc($available_fields)),
  );
  
  return system_settings_form($form);
}