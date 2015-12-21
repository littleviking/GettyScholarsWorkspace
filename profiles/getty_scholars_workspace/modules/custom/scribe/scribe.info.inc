<?php

/**
 * Implements hook_entity_property_info().
 */
function scribe_entity_property_info() {
  $info = array();
  $properties = &$info['scribe_attachment']['properties'];

  $properties['id'] = array(
    'label' => t('Attachment ID'),
    'type' => 'integer',
    'description' => t("The unique content ID."),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'attachment_id',
  );
  $properties['type'] = array(
    'label' => t('Type'),
    'type' => 'text',
    'description' => t('The type of the attachment being recorded such as text, image, etc.'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'type',
  );
  $properties['field_name'] = array(
    'label' => t('Field Name'),
    'type' => 'text',
    'description' => t('The machine name of the field which is annotated.'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'field_name',
  );
  $properties['entity_type'] = array(
    'label' => t('Entity Type'),
    'type' => 'text',
    'description' => t('The name of the entity type which is annotated.'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'entity_type'
  );
  $properties['bundle'] = array(
    'label' => t('Bundle'),
    'type' => 'text',
    'description' => t('The name of the bundle for the annotated entity.'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'bundle',
  );
  $properties['entity_id'] = array(
    'label' => t('Entity ID'),
    'type' => 'integer',
    'description' => t('The ID of the entity that is annotated.'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'entity_id',
  );
  $properties['created'] = array(
    'label' => t('Creation Date'),
    'type' => 'date',
    'description' => t('The date when the annoation was created.'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'created',
  );
  $properties['updated'] = array(
    'label' => t('Date Updated'),
    'type' => 'date',
    'description' => t('The date when the annoation was updated.'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'updated'
  );
  $properties['uid'] = array(
    'label' => t('User'),
    'type' => 'user',
    'description' => t('The user that created the attachment'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'uid',
  );

  // Add submodule properties into the property info structure
  $module_properties = module_invoke_all('scribe_metadata_properties');
  foreach ($module_properties as $name => $attach_info) {
    $properties[$name . '_attachment_info'] = array(
      'label' => t('@name Attachment Info', array('@name' => drupal_ucfirst($name))),
      'type' => 'struct',
      'setter callback' => 'entity_property_verbatim_set',
      'property info' => $attach_info,
    );
  }

  $annotation_properties = &$info['scribe_annotation']['properties'];
  $annotation_properties['annotation_id'] = array(
    'label' => t('Annotation ID'),
    'type' => 'integer',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'annotation_id',
  );
  $annotation_properties['parent_id'] = array(
    'label' => t('Parent ID'),
    'type' => 'integer',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'parent_id',
  );
  $annotation_properties['type'] = array(
    'label' => t('Type'),
    'type' => 'text',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'type',
  );
  $annotation_properties['text'] = array(
    'label' => t('Annotation Text'),
    'type' => 'text',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'text',
  );

  return $info;
}
