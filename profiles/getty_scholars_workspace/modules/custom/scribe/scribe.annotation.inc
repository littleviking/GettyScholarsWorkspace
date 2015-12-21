<?php


/**
 * Load the entity that any given annotation is ultimately attached to.
 */
function scribe_annotation_load_parent_entity($annotation) {
  // // Retrieve the root annotation ID
  // $annotation_id = $annotation->annotation_id;
  // $parent_id = $annotation->parent_id;

  // while ($parent_id != 0) {
  //   // Set the current annotation to the old parent
  //   $annotation_id = $parent_id;

  //   // Retrieve the parent ID of the next parent
  //   $vals = array(
  //     ':annotation_id' => $parent_id,
  //   );
  //   $parent_id = db_query("SELECT parent_id FROM scribe_annotation WHERE annotation_id = :annotation_id", $vals)->fetchField();
  // }

  // TODO: Maybe we want all annotations anywhere in the thread to point
  // to the parent attachment.  That way we don't need to do a costly
  // tree traversal for this.
  //$annotation = entity_load_single('scribe_annotation', $parent_id);
  if (isset($annotation->field_parent_ref['id'])) {
    $attachment_id = $annotation->field_parent_ref['id'];
  }
  else {
    $attachment_id = $annotation->field_parent_ref[LANGUAGE_NONE][0]['target_id'];
  }

  // Load the entity data from the attachment
  $entity_data = db_select('scribe_attachment', 's')
     ->fields('s', array('entity_type', 'entity_id'))
     ->condition('attachment_id',  $attachment_id)
     ->execute()
     ->fetchObject();

  // Load the resulting entity
  return array(
    'entity_type' => $entity_data->entity_type,
    'entity_id' => $entity_data->entity_id,
    'entity' => entity_load_single($entity_data->entity_type, $entity_data->entity_id),
  );
}
