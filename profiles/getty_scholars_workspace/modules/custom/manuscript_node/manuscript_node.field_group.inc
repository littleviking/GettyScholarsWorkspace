<?php
/**
 * @file
 * manuscript_node.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function manuscript_node_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_english|node|manuscript|default';
  $field_group->group_name = 'group_english';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'English',
    'weight' => '22',
    'children' => array(
      0 => 'field_english',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-english field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_english|node|manuscript|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_english|node|manuscript|form';
  $field_group->group_name = 'group_english';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'English',
    'weight' => '21',
    'children' => array(
      0 => 'field_english',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-english field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_english|node|manuscript|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_facsimile|node|manuscript|default';
  $field_group->group_name = 'group_facsimile';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Facsimile',
    'weight' => '20',
    'children' => array(
      0 => 'field_facsimile',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Facsimile',
      'instance_settings' => array(
        'hide_in_side_by_side' => 1,
        'id' => '',
        'classes' => 'group-facsimile field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_facsimile|node|manuscript|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_facsimile|node|manuscript|form';
  $field_group->group_name = 'group_facsimile';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Facsimile',
    'weight' => '19',
    'children' => array(
      0 => 'field_facsimile',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Facsimile',
      'instance_settings' => array(
        'hide_in_side_by_side' => 1,
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-facsimile field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_facsimile|node|manuscript|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_french|node|manuscript|default';
  $field_group->group_name = 'group_french';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'French',
    'weight' => '24',
    'children' => array(
      0 => 'field_french',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-french field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_french|node|manuscript|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_french|node|manuscript|form';
  $field_group->group_name = 'group_french';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'French',
    'weight' => '23',
    'children' => array(
      0 => 'field_french',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-french field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_french|node|manuscript|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_german|node|manuscript|default';
  $field_group->group_name = 'group_german';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'German',
    'weight' => '25',
    'children' => array(
      0 => 'field_german',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-german field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_german|node|manuscript|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_german|node|manuscript|form';
  $field_group->group_name = 'group_german';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'German',
    'weight' => '24',
    'children' => array(
      0 => 'field_german',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-german field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_german|node|manuscript|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_hebrew|node|manuscript|default';
  $field_group->group_name = 'group_hebrew';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Hebrew',
    'weight' => '28',
    'children' => array(
      0 => 'field_hebrew',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-hebrew field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_hebrew|node|manuscript|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_hebrew|node|manuscript|form';
  $field_group->group_name = 'group_hebrew';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Hebrew',
    'weight' => '28',
    'children' => array(
      0 => 'field_hebrew',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-hebrew field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_hebrew|node|manuscript|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_italian|node|manuscript|default';
  $field_group->group_name = 'group_italian';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Italian',
    'weight' => '26',
    'children' => array(
      0 => 'field_italian',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-italian field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_italian|node|manuscript|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_italian|node|manuscript|form';
  $field_group->group_name = 'group_italian';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Italian',
    'weight' => '25',
    'children' => array(
      0 => 'field_italian',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-italian field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_italian|node|manuscript|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_latin|node|manuscript|default';
  $field_group->group_name = 'group_latin';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Latin',
    'weight' => '27',
    'children' => array(
      0 => 'field_latin',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-latin field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_latin|node|manuscript|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_latin|node|manuscript|form';
  $field_group->group_name = 'group_latin';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Latin',
    'weight' => '26',
    'children' => array(
      0 => 'field_latin',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-latin field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_latin|node|manuscript|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_spanish|node|manuscript|default';
  $field_group->group_name = 'group_spanish';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Spanish',
    'weight' => '23',
    'children' => array(
      0 => 'field_spanish',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-spanish field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_spanish|node|manuscript|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_spanish|node|manuscript|form';
  $field_group->group_name = 'group_spanish';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Spanish',
    'weight' => '22',
    'children' => array(
      0 => 'field_spanish',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-spanish field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_spanish|node|manuscript|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_transcribe_translate|node|manuscript|default';
  $field_group->group_name = 'group_transcribe_translate';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Transcribe & Translate',
    'weight' => '17',
    'children' => array(
      0 => 'group_english',
      1 => 'group_facsimile',
      2 => 'group_french',
      3 => 'group_german',
      4 => 'group_hebrew',
      5 => 'group_italian',
      6 => 'group_latin',
      7 => 'group_spanish',
      8 => 'group_transcription',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Transcribe & Translate',
      'instance_settings' => array(
        'side_by_side' => 1,
        'classes' => 'group-transcribe-translate field-group-htabs',
      ),
    ),
  );
  $export['group_transcribe_translate|node|manuscript|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_transcribe_translate|node|manuscript|form';
  $field_group->group_name = 'group_transcribe_translate';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Transcribe & Translate',
    'weight' => '1',
    'children' => array(
      0 => 'group_english',
      1 => 'group_facsimile',
      2 => 'group_french',
      3 => 'group_german',
      4 => 'group_hebrew',
      5 => 'group_italian',
      6 => 'group_latin',
      7 => 'group_spanish',
      8 => 'group_transcription',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Transcribe & Translate',
      'instance_settings' => array(
        'side_by_side' => 1,
        'classes' => 'group-transcribe-translate field-group-htabs',
      ),
    ),
  );
  $export['group_transcribe_translate|node|manuscript|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_transcription|node|manuscript|default';
  $field_group->group_name = 'group_transcription';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Transcription',
    'weight' => '21',
    'children' => array(
      0 => 'field_transcription',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-transcription field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_transcription|node|manuscript|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_transcription|node|manuscript|form';
  $field_group->group_name = 'group_transcription';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'manuscript';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_transcribe_translate';
  $field_group->data = array(
    'label' => 'Transcription',
    'weight' => '20',
    'children' => array(
      0 => 'field_transcription',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-transcription field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_transcription|node|manuscript|form'] = $field_group;

  return $export;
}
