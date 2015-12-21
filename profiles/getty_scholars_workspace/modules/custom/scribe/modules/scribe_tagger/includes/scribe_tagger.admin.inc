<?php

/**
 * Form for admin settings.
 */
function scribe_tagger_admin_settings($form, &$form_state) {
  // Setup options
  $vocabs = taxonomy_get_vocabularies();
  $options = array();
  $options[''] = t('- None -');
  foreach ($vocabs as $vocab) {
    $options[$vocab->machine_name] = $vocab->name;
  }


  $form['#submit'][] = 'scribe_tagger_setup_fields';

  $form['scribe_tagger_vocabulary'] = array(
    '#type' => 'select',
    '#title' => t('Vocabulary'),
    '#description' => t('The taxonomy vocabulary to use for tagging.  If none is selected the tagging feature will not function.'),
    '#options' => $options,
    '#default_value' => variable_get('scribe_tagger_vocabulary', ''),
  );

  return system_settings_form($form);
}

/**
 * Ensure that the field for tags is setup on all annotation types.
 */
function scribe_tagger_setup_fields($form, &$form_state) {
  $vocab = $form_state['values']['scribe_tagger_vocabulary'];

  // Create a definition for a taxonomy term reference field for the given vocabulary
  $tag_field = array(
    'field_name' => 'field_annotation_tags',
    'type' => 'taxonomy_term_reference',
    'cardinality' => FIELD_CARDINALITY_UNLIMITED,
    'settings' => array(
      'allowed_values' => array(
        0 => array(
          'vocabulary' => $vocab,
          'parent' => 0,
        ),
      ),
    ),
  );

  // If the field doesn't exist create it
  // Otherwise update the existing field
  if (!field_info_field('field_annotation_tags')) {
    field_create_field($tag_field);
  }
  else {
    field_update_field($tag_field);
  }

  // For each scribe_attachment type create a field instance for the tag field if one doesn't exist
  $attachers = module_invoke_all('scribe_attacher_info');
  foreach ($attachers as $bundle => $attacher) {
    $info = field_info_instance('scribe_annotation', 'field_annotation_tags', $bundle);
    if (!$info) {
      $tag_field_instance = array(
        'field_name' => 'field_annotation_tags',
        'entity_type' => 'scribe_annotation',
        'bundle' => $bundle,
        'label' => t('Annotation Tags'),
        'widget' => array(
          'type' => 'taxonomy_autocomplete',
        ),
        'settings' => array(),
      );
      field_create_instance($tag_field_instance);
    }
  }
}



