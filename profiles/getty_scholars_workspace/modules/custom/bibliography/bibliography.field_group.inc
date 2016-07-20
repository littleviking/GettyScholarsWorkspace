<?php
/**
 * @file
 * bibliography.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function bibliography_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_biblio_config|node|bibliography|form';
  $field_group->group_name = 'group_biblio_config';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'bibliography';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Bibliography',
    'weight' => '0',
    'children' => array(
      0 => 'field_biblio_date',
      1 => 'field_biblio_extra_data',
      2 => 'field_biblio_isbn',
      3 => 'field_biblio_publisher',
      4 => 'field_biblio_short_title',
      5 => 'field_biblio_type',
      6 => 'field_biblio_url',
      7 => 'field_biblio_volume',
      8 => 'field_author_first_name',
      9 => 'field_author_last_name',
      10 => 'field_publisher_location',
      11 => 'field_biblio_edition',
      12 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-biblio-config field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_biblio_config|node|bibliography|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_general|node|bibliography|form';
  $field_group->group_name = 'group_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'bibliography';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'General',
    'weight' => '1',
    'children' => array(
      0 => 'field_bibliography_document',
      1 => 'field_url_type',
      2 => 'og_group_ref',
      3 => 'field_url',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-general field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_general|node|bibliography|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Bibliography');
  t('General');

  return $field_groups;
}
