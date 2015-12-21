<?php

/**
 * A text attachment entity.
 */
class ScribeAttachment extends Entity {
  protected function defaultLabel() {
    return $this->entity_type . ' - ' . $this->bundle . ' - ' . $this->field_name . ' Annotation';
  }

  protected function defaultUri() {
    return array('path' => 'scribe_attachment/' . $this->identifier());
  }
}

/**
 * Text attachment controller class.
 */
class ScribeAttachmentController extends EntityAPIController {
  public function create(array $values = array()) {
    global $user;
    $values += array(
      'created' => REQUEST_TIME,
      'updated' => REQUEST_TIME,
      'uid' => $user->uid,
    );

    return parent::create($values);
  }
}
