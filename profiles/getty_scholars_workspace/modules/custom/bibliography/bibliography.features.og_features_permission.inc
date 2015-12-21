<?php
/**
 * @file
 * bibliography.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function bibliography_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:project:approve comment_node_bibliography'
  $permissions['node:project:approve comment_node_bibliography'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:create bibliography content'
  $permissions['node:project:create bibliography content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete any bibliography content'
  $permissions['node:project:delete any bibliography content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete comment_node_bibliography'
  $permissions['node:project:delete comment_node_bibliography'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete own bibliography content'
  $permissions['node:project:delete own bibliography content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:edit comment_node_bibliography'
  $permissions['node:project:edit comment_node_bibliography'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit own comment_node_bibliography'
  $permissions['node:project:edit own comment_node_bibliography'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:post comment_node_bibliography'
  $permissions['node:project:post comment_node_bibliography'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:update any bibliography content'
  $permissions['node:project:update any bibliography content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update own bibliography content'
  $permissions['node:project:update own bibliography content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  return $permissions;
}
