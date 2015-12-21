<?php


class ScribeAnnotation extends Entity {
  protected function defaultUri() {
    return array('path' => 'scribe_annotation/' . $this->identifier());
  }
}

class ScribeAnnotationController extends EntityAPIController {
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
