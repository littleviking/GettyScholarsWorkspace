<?php
/**
 * @file
 * comparison_display.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function comparison_display_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'comparison_detail_page';
  $context->description = '';
  $context->tag = 'Comparison';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'comparison' => 'comparison',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-4d3f7a9058c9c98e8ecbdebb931b4314' => array(
          'module' => 'views',
          'delta' => '4d3f7a9058c9c98e8ecbdebb931b4314',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Comparison');
  $export['comparison_detail_page'] = $context;

  return $export;
}
