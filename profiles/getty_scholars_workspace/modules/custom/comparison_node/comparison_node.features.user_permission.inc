<?php
/**
 * @file
 * comparison_node.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function comparison_node_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create comparison content'.
  $permissions['create comparison content'] = array(
    'name' => 'create comparison content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any comparison content'.
  $permissions['delete any comparison content'] = array(
    'name' => 'delete any comparison content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own comparison content'.
  $permissions['delete own comparison content'] = array(
    'name' => 'delete own comparison content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any comparison content'.
  $permissions['edit any comparison content'] = array(
    'name' => 'edit any comparison content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own comparison content'.
  $permissions['edit own comparison content'] = array(
    'name' => 'edit own comparison content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
