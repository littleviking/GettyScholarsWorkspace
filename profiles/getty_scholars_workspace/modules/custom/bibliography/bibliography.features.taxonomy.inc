<?php
/**
 * @file
 * bibliography.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function bibliography_taxonomy_default_vocabularies() {
  return array(
    'bibliography_categories' => array(
      'name' => 'Bibliography Categories',
      'machine_name' => 'bibliography_categories',
      'description' => 'Category tags for bibliography entries',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
