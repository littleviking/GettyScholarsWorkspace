<?php

/**
 *  @function:
 *    This function is used to provide an admin with a user interface to map biblio to rdf
 */
function bibliography_support_rdf_admin_form() {
  //variables
  $form = array();
  $field_prefix = '';
  $variable_name = 'getty_biblio_wrapper_rdf';
  $available_fields =  _getty_bibliography_support_available_fields();
  $fields = variable_get('getty_biblio_available_fields', drupal_map_assoc($available_fields));
  
  $form['getty_biblio_wrapper_rdf'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('Bibliography'),
    '#description' => t('E.G. Title to title. Enter title. Leaving it blank will exclude it from the export.'),
  );
  
  //retrieves all values
  $all_value = variable_get($variable_name, '');

  //loops through each avaiable field
  foreach ($fields as $key => $value) {
    //this ensures that if the value was removed from the previous to continue
    if (empty($value)) {
      continue;
    }
    
    $value_value = (isset($all_value['getty_biblio_fieldset_' . $value])) ? $all_value['getty_biblio_fieldset_' . $value][$field_prefix . $value] : '';

    $form[$variable_name]['getty_biblio_fieldset_' . $value] = array(
      '#title' => t($value),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => (empty($value_value)) ? TRUE : FALSE,
    );
    
    //creates a dynamic field to map to. when empty is set it will not map the field to anything
    $form[$variable_name]['getty_biblio_fieldset_' . $value][$field_prefix . $value] = array(
      '#type' => 'textfield',
      '#title' => t('Map "' . $value . '" to what rdf value?'),
      '#default_value' => $value_value,
    );
  }
  
  //additional submit handler
  $form['#submit'][] = '_bibliography_support_rdf_admin_form_submit';
  
  return system_settings_form($form);
}

/**
 *  @function:
 *    This function is the additional submit handler. Built but not in use.
 */
function _bibliography_support_rdf_admin_form_submit(&$form, &$form_state) {}