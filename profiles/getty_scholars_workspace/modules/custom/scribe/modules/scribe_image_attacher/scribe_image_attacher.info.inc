<?php

/**
 * Implements hook_scribe_metadata_properties().
 */
function scribe_image_attacher_scribe_metadata_properties() {
  $info = array();
  $properties = &$info['image'];

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
  $properties['annotorious_schema_version'] = array(
    'label' => t('Schema Version'),
    'type' => 'text',
    'description' => t('Schema Version of Annotorious being used, by default v0.3'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema' => 'annotator_schema_version',
  );
  $properties['uri'] = array(
    'label' => t('Annotation URI'),
    'type' => 'uri',
    'description' => t('URI of annotated document.'),
    'setter callback' => 'entity_property_verbatim_set',
  );
  $properties['src'] = array(
    'label' => t('Annotation Image src'),
    'type' => 'uri',
    'description' => t('src property of annotated image.'),
    'setter callback' => 'entity_property_verbatim_set',
  );
  $properties['shape_type'] = array(
    'label' => t('Shape Type'),
    'type' => 'text',
    'description' => t('Shape type. Currently, only \'rect\' (rectangle) is supported'),
    'setter callback' => 'entity_property_verbatim_set',
  );
  $properties['shapes'] = array(
    'label' => t('Describes the shape of the annotation area'),
    'type' => 'list<struct>',
    'description' => 'Ranges that are covered by the attachment.',
    'setter callback' => 'entity_property_verbatim_set',
    'property info' => array(
      // 'shape' => array(
      //   'label' => t('Shape Type'),
      //   'type' => 'text',
      //   'description' => t('Shape type. Currently, only \'rect\' (rectangle) is supported'),
      // ),
      'height' => array(
        'label' => t('Height'),
        'type' => 'text',
        'description' => t('Height of rectangle, using normalized system.'),
      ),
      'width' => array(
        'label' => t('Width'),
        'type' => 'text',
        'description' => t('Width of rectangle, using normalized system.'),
      ),
      'x' => array(
        'label' => t('Starting x-point'),
        'type' => 'text',
        'description' => t('Starting x-point of rectangle, using normalized system.'),
      ),
      'y' => array(
        'label' => t('Starting y-point'),
        'type' => 'text',
        'description' => t('Starting y-point of rectangle, using normalized system.'),
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
