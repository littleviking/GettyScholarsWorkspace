<?php
/**
 * @file
 * bibliography_support.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function bibliography_support_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'bibliography';
  $feeds_importer->config = array(
    'name' => 'Bibliography Import',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'ris rdf',
        'direct' => 0,
        'directory' => 'public://feeds',
        'allowed_schemes' => array(
          'public' => 'public',
          'private' => 'private',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'getty_bib_parser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'field_author_first_name',
            'target' => 'field_author_first_name',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'field_author_last_name',
            'target' => 'field_author_last_name',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'field_biblio_date',
            'target' => 'field_biblio_date',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'field_biblio_edition',
            'target' => 'field_biblio_edition',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'field_biblio_isbn',
            'target' => 'field_biblio_isbn',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'field_biblio_publisher',
            'target' => 'field_biblio_publisher',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'field_publisher_location',
            'target' => 'field_publisher_location',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'field_biblio_short_title',
            'target' => 'field_biblio_short_title',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'field_biblio_type',
            'target' => 'field_biblio_type',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'field_biblio_url',
            'target' => 'field_biblio_url',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'field_biblio_volume',
            'target' => 'field_biblio_volume',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'bibliography',
        'update_non_existent' => 'skip',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['bibliography'] = $feeds_importer;

  return $export;
}
