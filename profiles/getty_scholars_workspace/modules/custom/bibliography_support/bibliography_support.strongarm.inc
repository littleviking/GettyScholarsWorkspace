<?php
/**
 * @file
 * bibliography_support.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function bibliography_support_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'getty_biblio_wrapper_rdf';
  $strongarm->value = array(
    'getty_biblio_fieldset_title' => array(
      'title' => 'bib:* > dc:title',
    ),
    'getty_biblio_fieldset_field_bibliography_document' => array(
      'field_bibliography_document' => '',
    ),
    'getty_biblio_fieldset_field_reference' => array(
      'field_reference' => '',
    ),
    'getty_biblio_fieldset_field_short_reference' => array(
      'field_short_reference' => '',
    ),
    'getty_biblio_fieldset_field_url_type' => array(
      'field_url_type' => '',
    ),
    'getty_biblio_fieldset_og_group_ref' => array(
      'og_group_ref' => '',
    ),
    'getty_biblio_fieldset_field_biblio_date' => array(
      'field_biblio_date' => 'dc:date',
    ),
    'getty_biblio_fieldset_field_biblio_extra_data' => array(
      'field_biblio_extra_data' => '',
    ),
    'getty_biblio_fieldset_field_biblio_isbn' => array(
      'field_biblio_isbn' => 'bib:Book dc:identifier',
    ),
    'getty_biblio_fieldset_field_biblio_publisher' => array(
      'field_biblio_publisher' => 'dc:publisher foaf:name',
    ),
    'getty_biblio_fieldset_field_biblio_short_title' => array(
      'field_biblio_short_title' => 'z:shortTitle',
    ),
    'getty_biblio_fieldset_field_biblio_type' => array(
      'field_biblio_type' => 'z:itemType',
    ),
    'getty_biblio_fieldset_field_biblio_url' => array(
      'field_biblio_url' => '',
    ),
    'getty_biblio_fieldset_field_biblio_volume' => array(
      'field_biblio_volume' => 'prism:volume',
    ),
    'getty_biblio_fieldset_field_bibliographic_tags' => array(
      'field_bibliographic_tags' => 'dc:subject',
    ),
    'getty_biblio_fieldset_field_tags' => array(
      'field_tags' => '',
    ),
    'getty_biblio_fieldset_field_url' => array(
      'field_url' => 'dcterms:URI',
    ),
    'getty_biblio_fieldset_field_edition' => array(
      'field_edition' => 'prism:edition',
    ),
    'getty_biblio_fieldset_field_author_first_name' => array(
      'field_author_first_name' => 'foaf:surname',
    ),
    'getty_biblio_fieldset_field_author_last_name' => array(
      'field_author_last_name' => 'foaf:givenname',
    ),
    'getty_biblio_fieldset_field_publisher_location' => array(
      'field_publisher_location' => 'dc:publisher vcard:locality',
    ),
  );
  $export['getty_biblio_wrapper_rdf'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'getty_biblio_wrapper_ris';
  $strongarm->value = array(
    'getty_biblio_fieldset_title' => array(
      'title' => 'TI',
    ),
    'getty_biblio_fieldset_field_bibliography_document' => array(
      'field_bibliography_document' => '',
    ),
    'getty_biblio_fieldset_field_reference' => array(
      'field_reference' => '',
    ),
    'getty_biblio_fieldset_field_short_reference' => array(
      'field_short_reference' => '',
    ),
    'getty_biblio_fieldset_field_url_type' => array(
      'field_url_type' => '',
    ),
    'getty_biblio_fieldset_og_group_ref' => array(
      'og_group_ref' => '',
    ),
    'getty_biblio_fieldset_field_biblio_author' => array(
      'field_biblio_author' => 'AU',
    ),
    'getty_biblio_fieldset_field_biblio_date' => array(
      'field_biblio_date' => 'DA',
    ),
    'getty_biblio_fieldset_field_biblio_edition' => array(
      'field_biblio_edition' => 'ET',
    ),
    'getty_biblio_fieldset_field_biblio_extra_data' => array(
      'field_biblio_extra_data' => '',
    ),
    'getty_biblio_fieldset_field_biblio_isbn' => array(
      'field_biblio_isbn' => 'SN',
    ),
    'getty_biblio_fieldset_field_biblio_publisher' => array(
      'field_biblio_publisher' => 'PB',
    ),
    'getty_biblio_fieldset_field_biblio_short_title' => array(
      'field_biblio_short_title' => 'ST',
    ),
    'getty_biblio_fieldset_field_biblio_type' => array(
      'field_biblio_type' => 'TY',
    ),
    'getty_biblio_fieldset_field_biblio_url' => array(
      'field_biblio_url' => 'UR',
    ),
    'getty_biblio_fieldset_field_biblio_volume' => array(
      'field_biblio_volume' => 'VL',
    ),
    'getty_biblio_fieldset_field_bibliographic_tags' => array(
      'field_bibliographic_tags' => '',
    ),
    'getty_biblio_fieldset_field_tags' => array(
      'field_tags' => '',
    ),
    'getty_biblio_fieldset_field_url' => array(
      'field_url' => '',
    ),
  );
  $export['getty_biblio_wrapper_ris'] = $strongarm;

  return $export;
}
