<?php
/**
 * @file
 * gettysw_annotation_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function gettysw_annotation_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access resource scribe_annotation'.
  $permissions['access resource scribe_annotation'] = array(
    'name' => 'access resource scribe_annotation',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'restws',
  );

  // Exported permission: 'access resource scribe_attachment'.
  $permissions['access resource scribe_attachment'] = array(
    'name' => 'access resource scribe_attachment',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'restws',
  );

  // Exported permission: 'create annotations'.
  $permissions['create annotations'] = array(
    'name' => 'create annotations',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'scribe',
  );

  // Exported permission: 'delete any image annotations'.
  $permissions['delete any image annotations'] = array(
    'name' => 'delete any image annotations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'scribe',
  );

  // Exported permission: 'delete any text annotations'.
  $permissions['delete any text annotations'] = array(
    'name' => 'delete any text annotations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'scribe',
  );

  // Exported permission: 'delete own image annotations'.
  $permissions['delete own image annotations'] = array(
    'name' => 'delete own image annotations',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'scribe',
  );

  // Exported permission: 'delete own text annotations'.
  $permissions['delete own text annotations'] = array(
    'name' => 'delete own text annotations',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'scribe',
  );

  // Exported permission: 'update any image annotations'.
  $permissions['update any image annotations'] = array(
    'name' => 'update any image annotations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'scribe',
  );

  // Exported permission: 'update any text annotations'.
  $permissions['update any text annotations'] = array(
    'name' => 'update any text annotations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'scribe',
  );

  // Exported permission: 'update own image annotations'.
  $permissions['update own image annotations'] = array(
    'name' => 'update own image annotations',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'scribe',
  );

  // Exported permission: 'update own text annotations'.
  $permissions['update own text annotations'] = array(
    'name' => 'update own text annotations',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'scribe',
  );

  // Exported permission: 'view image annotations'.
  $permissions['view image annotations'] = array(
    'name' => 'view image annotations',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'scribe',
  );

  // Exported permission: 'view text annotations'.
  $permissions['view text annotations'] = array(
    'name' => 'view text annotations',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'scribe',
  );

  return $permissions;
}
