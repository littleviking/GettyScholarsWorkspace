<?php
/**
 * @file
 * essay_node.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function essay_node_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create essay content'.
  $permissions['create essay content'] = array(
    'name' => 'create essay content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any essay content'.
  $permissions['delete any essay content'] = array(
    'name' => 'delete any essay content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own essay content'.
  $permissions['delete own essay content'] = array(
    'name' => 'delete own essay content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any essay content'.
  $permissions['edit any essay content'] = array(
    'name' => 'edit any essay content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own essay content'.
  $permissions['edit own essay content'] = array(
    'name' => 'edit own essay content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
