<?php
/**
 * @file
 * timeline.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function timeline_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create timeline_date content'.
  $permissions['create timeline_date content'] = array(
    'name' => 'create timeline_date content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any timeline_date content'.
  $permissions['delete any timeline_date content'] = array(
    'name' => 'delete any timeline_date content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own timeline_date content'.
  $permissions['delete own timeline_date content'] = array(
    'name' => 'delete own timeline_date content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any timeline_date content'.
  $permissions['edit any timeline_date content'] = array(
    'name' => 'edit any timeline_date content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own timeline_date content'.
  $permissions['edit own timeline_date content'] = array(
    'name' => 'edit own timeline_date content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
