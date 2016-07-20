<?php
/**
 * @file
 * gettysw_user_permissions.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function gettysw_user_permissions_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:project:access cropzoom'
  $permissions['node:project:access cropzoom'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:add group container'
  $permissions['node:project:add group container'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:add group forum'
  $permissions['node:project:add group forum'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:add user'
  $permissions['node:project:add user'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:administer group'
  $permissions['node:project:administer group'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:approve and deny subscription'
  $permissions['node:project:approve and deny subscription'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:approve comment_node_bibliography'
  $permissions['node:project:approve comment_node_bibliography'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:approve comment_node_comparison'
  $permissions['node:project:approve comment_node_comparison'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:approve comment_node_essay'
  $permissions['node:project:approve comment_node_essay'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:approve comment_node_forum'
  $permissions['node:project:approve comment_node_forum'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:approve comment_node_image'
  $permissions['node:project:approve comment_node_image'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:approve comment_node_manuscript'
  $permissions['node:project:approve comment_node_manuscript'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:approve comment_node_page'
  $permissions['node:project:approve comment_node_page'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:approve comment_node_project'
  $permissions['node:project:approve comment_node_project'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:approve comment_node_timeline_date'
  $permissions['node:project:approve comment_node_timeline_date'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:create annotations'
  $permissions['node:project:create annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:create bibliography content'
  $permissions['node:project:create bibliography content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:create comparison content'
  $permissions['node:project:create comparison content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:create essay content'
  $permissions['node:project:create essay content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:create forum content'
  $permissions['node:project:create forum content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:create image content'
  $permissions['node:project:create image content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:create manuscript content'
  $permissions['node:project:create manuscript content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:create page content'
  $permissions['node:project:create page content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:create timeline_date content'
  $permissions['node:project:create timeline_date content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete any bibliography content'
  $permissions['node:project:delete any bibliography content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete any comparison content'
  $permissions['node:project:delete any comparison content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete any essay content'
  $permissions['node:project:delete any essay content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete any forum content'
  $permissions['node:project:delete any forum content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete any image annotations'
  $permissions['node:project:delete any image annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete any image content'
  $permissions['node:project:delete any image content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete any manuscript content'
  $permissions['node:project:delete any manuscript content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete any page content'
  $permissions['node:project:delete any page content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete any text annotations'
  $permissions['node:project:delete any text annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete any timeline_date content'
  $permissions['node:project:delete any timeline_date content'] = array(
    'roles' => array(
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

  // Exported og permission: 'node:project:delete comment_node_comparison'
  $permissions['node:project:delete comment_node_comparison'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete comment_node_essay'
  $permissions['node:project:delete comment_node_essay'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete comment_node_forum'
  $permissions['node:project:delete comment_node_forum'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete comment_node_image'
  $permissions['node:project:delete comment_node_image'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete comment_node_manuscript'
  $permissions['node:project:delete comment_node_manuscript'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete comment_node_page'
  $permissions['node:project:delete comment_node_page'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete comment_node_project'
  $permissions['node:project:delete comment_node_project'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete comment_node_timeline_date'
  $permissions['node:project:delete comment_node_timeline_date'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:delete own bibliography content'
  $permissions['node:project:delete own bibliography content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete own comparison content'
  $permissions['node:project:delete own comparison content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete own essay content'
  $permissions['node:project:delete own essay content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete own forum content'
  $permissions['node:project:delete own forum content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete own image annotations'
  $permissions['node:project:delete own image annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete own image content'
  $permissions['node:project:delete own image content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete own manuscript content'
  $permissions['node:project:delete own manuscript content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete own page content'
  $permissions['node:project:delete own page content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete own text annotations'
  $permissions['node:project:delete own text annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:delete own timeline_date content'
  $permissions['node:project:delete own timeline_date content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:edit comment_node_bibliography'
  $permissions['node:project:edit comment_node_bibliography'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit comment_node_comparison'
  $permissions['node:project:edit comment_node_comparison'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit comment_node_essay'
  $permissions['node:project:edit comment_node_essay'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit comment_node_forum'
  $permissions['node:project:edit comment_node_forum'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit comment_node_image'
  $permissions['node:project:edit comment_node_image'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit comment_node_manuscript'
  $permissions['node:project:edit comment_node_manuscript'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit comment_node_page'
  $permissions['node:project:edit comment_node_page'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit comment_node_project'
  $permissions['node:project:edit comment_node_project'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit comment_node_timeline_date'
  $permissions['node:project:edit comment_node_timeline_date'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit group container'
  $permissions['node:project:edit group container'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit group forum'
  $permissions['node:project:edit group forum'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit own comment_node_bibliography'
  $permissions['node:project:edit own comment_node_bibliography'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit own comment_node_comparison'
  $permissions['node:project:edit own comment_node_comparison'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit own comment_node_essay'
  $permissions['node:project:edit own comment_node_essay'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit own comment_node_forum'
  $permissions['node:project:edit own comment_node_forum'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit own comment_node_image'
  $permissions['node:project:edit own comment_node_image'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit own comment_node_manuscript'
  $permissions['node:project:edit own comment_node_manuscript'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit own comment_node_page'
  $permissions['node:project:edit own comment_node_page'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit own comment_node_project'
  $permissions['node:project:edit own comment_node_project'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:edit own comment_node_timeline_date'
  $permissions['node:project:edit own comment_node_timeline_date'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:manage members'
  $permissions['node:project:manage members'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:manage permissions'
  $permissions['node:project:manage permissions'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:manage roles'
  $permissions['node:project:manage roles'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:project:post comment_node_bibliography'
  $permissions['node:project:post comment_node_bibliography'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:post comment_node_comparison'
  $permissions['node:project:post comment_node_comparison'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:post comment_node_essay'
  $permissions['node:project:post comment_node_essay'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:post comment_node_forum'
  $permissions['node:project:post comment_node_forum'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:post comment_node_image'
  $permissions['node:project:post comment_node_image'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:post comment_node_manuscript'
  $permissions['node:project:post comment_node_manuscript'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:post comment_node_page'
  $permissions['node:project:post comment_node_page'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:post comment_node_project'
  $permissions['node:project:post comment_node_project'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:post comment_node_timeline_date'
  $permissions['node:project:post comment_node_timeline_date'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:subscribe'
  $permissions['node:project:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:project:subscribe without approval'
  $permissions['node:project:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:project:unsubscribe'
  $permissions['node:project:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:project:update any bibliography content'
  $permissions['node:project:update any bibliography content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update any comparison content'
  $permissions['node:project:update any comparison content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update any essay content'
  $permissions['node:project:update any essay content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update any forum content'
  $permissions['node:project:update any forum content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update any image annotations'
  $permissions['node:project:update any image annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update any image content'
  $permissions['node:project:update any image content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update any manuscript content'
  $permissions['node:project:update any manuscript content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update any page content'
  $permissions['node:project:update any page content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update any text annotations'
  $permissions['node:project:update any text annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update any timeline_date content'
  $permissions['node:project:update any timeline_date content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
    ),
  );

  // Exported og permission: 'node:project:update group'
  $permissions['node:project:update group'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
    ),
  );

  // Exported og permission: 'node:project:update own bibliography content'
  $permissions['node:project:update own bibliography content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:update own comparison content'
  $permissions['node:project:update own comparison content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:update own essay content'
  $permissions['node:project:update own essay content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:update own forum content'
  $permissions['node:project:update own forum content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:update own image annotations'
  $permissions['node:project:update own image annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:update own image content'
  $permissions['node:project:update own image content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:update own manuscript content'
  $permissions['node:project:update own manuscript content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:update own page content'
  $permissions['node:project:update own page content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:update own text annotations'
  $permissions['node:project:update own text annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:update own timeline_date content'
  $permissions['node:project:update own timeline_date content'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:view group forum list'
  $permissions['node:project:view group forum list'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:view image annotations'
  $permissions['node:project:view image annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  // Exported og permission: 'node:project:view text annotations'
  $permissions['node:project:view text annotations'] = array(
    'roles' => array(
      'group administrator member' => 'group administrator member',
      'member' => 'member',
      'research assistant' => 'research assistant',
      'scholar' => 'scholar',
    ),
  );

  return $permissions;
}
