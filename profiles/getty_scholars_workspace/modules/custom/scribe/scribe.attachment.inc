<?php

function scribe_attachment_load_multiple($ids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('scribe_attachment', $ids, $conditions, $reset);
}

function scribe_load_attachment() {

}
