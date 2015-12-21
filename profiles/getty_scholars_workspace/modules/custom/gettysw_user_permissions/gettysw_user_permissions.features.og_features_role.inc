<?php
/**
 * @file
 * gettysw_user_permissions.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function gettysw_user_permissions_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:project:group administrator member'.
  $roles['node:project:group administrator member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'project',
    'name' => 'group administrator member',
  );

  // Exported OG Role: 'node:project:research assistant'.
  $roles['node:project:research assistant'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'project',
    'name' => 'research assistant',
  );

  // Exported OG Role: 'node:project:scholar'.
  $roles['node:project:scholar'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'project',
    'name' => 'scholar',
  );

  return $roles;
}
