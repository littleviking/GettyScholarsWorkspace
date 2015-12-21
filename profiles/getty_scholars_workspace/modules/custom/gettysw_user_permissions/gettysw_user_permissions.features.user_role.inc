<?php
/**
 * @file
 * gettysw_user_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function gettysw_user_permissions_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  return $roles;
}
