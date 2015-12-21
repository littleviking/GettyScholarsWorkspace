<?php
/**
 * @file
 * project_dashboard.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function project_dashboard_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'main_dashboard';
  $context->description = '';
  $context->tag = 'Dashboard';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'dashboard' => 'dashboard',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'project_dashboard-project_dashboard_logo' => array(
          'module' => 'project_dashboard',
          'delta' => 'project_dashboard_logo',
          'region' => 'branding',
          'weight' => '-10',
        ),
        'project_dashboard-my_projects' => array(
          'module' => 'project_dashboard',
          'delta' => 'my_projects',
          'region' => 'menu',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Dashboard');
  $export['main_dashboard'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'project_dashboard';
  $context->description = '';
  $context->tag = 'Dashboard';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'bibliography' => 'bibliography',
        'comparison' => 'comparison',
        'essay' => 'essay',
        'forum' => 'forum',
        'image' => 'image',
        'manuscript' => 'manuscript',
        'page' => 'page',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'path' => array(
      'values' => array(
        'project/*' => 'project/*',
        'lighttable/*' => 'lighttable/*',
        'groups-forums/*' => 'groups-forums/*',
        'essays/*' => 'essays/*',
        'node/add/*/*' => 'node/add/*/*',
        'node/*/group' => 'node/*/group',
        'admin/structure/forum/add/forum/*' => 'admin/structure/forum/add/forum/*',
        'admin/structure/forum/add/container/*' => 'admin/structure/forum/add/container/*',
        'forum/*' => 'forum/*',
        'project/*/search/*' => 'project/*/search/*',
        '~node/add/project' => '~node/add/project',
        'node/*/translate' => 'node/*/translate',
        'import/*' => 'import/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'project_dashboard-project_dashboard_logo' => array(
          'module' => 'project_dashboard',
          'delta' => 'project_dashboard_logo',
          'region' => 'branding',
          'weight' => '-10',
        ),
        'project_dashboard-project_toolbar' => array(
          'module' => 'project_dashboard',
          'delta' => 'project_toolbar',
          'region' => 'branding',
          'weight' => '-9',
        ),
        'project_dashboard-project_search' => array(
          'module' => 'project_dashboard',
          'delta' => 'project_search',
          'region' => 'menu',
          'weight' => '-10',
        ),
        'project_dashboard-current_project' => array(
          'module' => 'project_dashboard',
          'delta' => 'current_project',
          'region' => 'menu',
          'weight' => '-9',
        ),
        'project_dashboard-project_menu' => array(
          'module' => 'project_dashboard',
          'delta' => 'project_menu',
          'region' => 'preface_first',
          'weight' => '-10',
        ),
        'project_dashboard-create_content' => array(
          'module' => 'project_dashboard',
          'delta' => 'create_content',
          'region' => 'preface_first',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Dashboard');
  $export['project_dashboard'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'project_search';
  $context->description = '';
  $context->tag = 'search';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'project/*' => 'project/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'project_dashboard/project_search' => array(
          'module' => 'project_dashboard',
          'delta' => 'project_search',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('search');
  $export['project_search'] = $context;

  return $export;
}
