<?php

/**
 * Implements hook_scribe_metadata_properties().
 */
function scribe_text_attacher_scribe_metadata_properties() {
  $info = array();
  $properties = &$info['text'];

  $properties['id'] = array(
    'label' => t('Attachment ID'),
    'type' => 'integer',
    'description' => t("The unique content ID."),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'attachment_id',
  );
  $properties['text'] = array(
    'label' => t('Text'),
    'type' => 'text',
    'description' => t('The text of the annotation.'),
    'setter callback' => 'entity_property_verbatim_set',
  );
  $properties['annotator_schema_version'] = array(
    'label' => t('Schema Version'),
    'type' => 'text',
    'description' => t('Schema Version of Annotator being used, by default v1.0'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema' => 'annotator_schema_version',
  );
  $properties['quote'] = array(
    'label' => t('Quoted Text'),
    'type' => 'text',
    'description' => t('The text that is being annotated.'),
    'setter callback' => 'entity_property_verbatim_set',
  );
  $properties['uri'] = array(
    'label' => t('Annotation URI'),
    'type' => 'uri',
    'description' => t('URI of annotated document.'),
    'setter callback' => 'entity_property_verbatim_set',
  );
  $properties['ranges'] = array(
    'label' => t('Annotation Ranges'),
    'type' => 'list<struct>',
    'description' => 'Ranges that are covered by the attachment.',
    'setter callback' => 'entity_property_verbatim_set',
    'property info' => array(
      'end' => array(
        'label' => t('End'),
        'type' => 'text',
        'description' => t('An xpath path to the end element of the annotation.'),
      ),
      'endOffset' => array(
        'label' => t('End Offset'),
        'type' => 'integer',
        'description' => t('The numeric position inside of the element of the end of the annotation.'),
      ),
      'start' => array(
        'label' => t('Start'),
        'type' => 'text',
        'description' => t('An xpath path to the beginning element of the annotation.'),
      ),
      'startOffset' => array(
        'label' => t('Start Offset'),
        'type' => 'integer',
        'description' => t('The numeric position inside of the element of the start of the annotation.'),
      ),
    ),
  );
  $properties['uid'] = array(
    'label' => t('User'),
    'type' => 'user',
    'description' => t('The user that created the attachment'),
    'setter callback' => 'entity_property_verbatim_set',
  );

  return $info;
}
