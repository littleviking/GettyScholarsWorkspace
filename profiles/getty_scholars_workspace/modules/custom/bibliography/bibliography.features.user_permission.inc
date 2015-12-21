<?php
/**
 * @file
 * bibliography.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function bibliography_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create bibliography content'.
  $permissions['create bibliography content'] = array(
    'name' => 'create bibliography content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any bibliography content'.
  $permissions['delete any bibliography content'] = array(
    'name' => 'delete any bibliography content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own bibliography content'.
  $permissions['delete own bibliography content'] = array(
    'name' => 'delete own bibliography content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in bibliography_categories'.
  $permissions['delete terms in bibliography_categories'] = array(
    'name' => 'delete terms in bibliography_categories',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any bibliography content'.
  $permissions['edit any bibliography content'] = array(
    'name' => 'edit any bibliography content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own bibliography content'.
  $permissions['edit own bibliography content'] = array(
    'name' => 'edit own bibliography content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in bibliography_categories'.
  $permissions['edit terms in bibliography_categories'] = array(
    'name' => 'edit terms in bibliography_categories',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  return $permissions;
}
