<?php
/**
 * @file
 * bibliography.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function bibliography_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'bibliography';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Bibliography';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Bibliography';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_author_first_name' => 'field_author_first_name',
    'field_author_last_name' => 'field_author_last_name',
    'field_biblio_date' => 'field_biblio_date',
    'field_biblio_publisher' => 'field_biblio_publisher',
    'field_publisher_location' => 'field_publisher_location',
    'title' => 'title',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_author_first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_author_last_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_biblio_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_biblio_publisher' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_publisher_location' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no bibliography items for this project.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: Content: Author First Name */
  $handler->display->display_options['fields']['field_author_first_name']['id'] = 'field_author_first_name';
  $handler->display->display_options['fields']['field_author_first_name']['table'] = 'field_data_field_author_first_name';
  $handler->display->display_options['fields']['field_author_first_name']['field'] = 'field_author_first_name';
  $handler->display->display_options['fields']['field_author_first_name']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Content: Author Last Name */
  $handler->display->display_options['fields']['field_author_last_name']['id'] = 'field_author_last_name';
  $handler->display->display_options['fields']['field_author_last_name']['table'] = 'field_data_field_author_last_name';
  $handler->display->display_options['fields']['field_author_last_name']['field'] = 'field_author_last_name';
  $handler->display->display_options['fields']['field_author_last_name']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_biblio_date']['id'] = 'field_biblio_date';
  $handler->display->display_options['fields']['field_biblio_date']['table'] = 'field_data_field_biblio_date';
  $handler->display->display_options['fields']['field_biblio_date']['field'] = 'field_biblio_date';
  $handler->display->display_options['fields']['field_biblio_date']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Content: Publisher */
  $handler->display->display_options['fields']['field_biblio_publisher']['id'] = 'field_biblio_publisher';
  $handler->display->display_options['fields']['field_biblio_publisher']['table'] = 'field_data_field_biblio_publisher';
  $handler->display->display_options['fields']['field_biblio_publisher']['field'] = 'field_biblio_publisher';
  $handler->display->display_options['fields']['field_biblio_publisher']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Content: Publisher Location */
  $handler->display->display_options['fields']['field_publisher_location']['id'] = 'field_publisher_location';
  $handler->display->display_options['fields']['field_publisher_location']['table'] = 'field_data_field_publisher_location';
  $handler->display->display_options['fields']['field_publisher_location']['field'] = 'field_publisher_location';
  $handler->display->display_options['fields']['field_publisher_location']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = 'hidden';
  $handler->display->display_options['fields']['view_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['text'] = '<li>[view_node]</li>';
  $handler->display->display_options['fields']['view_node']['text'] = 'view';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'hidden';
  $handler->display->display_options['fields']['edit_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '<li>[edit_node]</li>';
  $handler->display->display_options['fields']['edit_node']['text'] = 'edit';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = 'hidden';
  $handler->display->display_options['fields']['delete_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['delete_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['delete_node']['alter']['text'] = '<li>[delete_node]</li>';
  $handler->display->display_options['fields']['delete_node']['text'] = 'delete';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Operations';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<ul class="links inline">[view_node][edit_node][delete_node]</ul>';
  /* Contextual filter: Field: Groups audience (og_group_ref) */
  $handler->display->display_options['arguments']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bibliography' => 'bibliography',
  );
  /* Filter criterion: Content: Has taxonomy term */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = 'Filter by bibliographic grouping';
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'tid';
  $handler->display->display_options['filters']['tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['tid']['type'] = 'select';
  $handler->display->display_options['filters']['tid']['vocabulary'] = 'bibliography_categories';

  /* Display: Bibliography List Block */
  $handler = $view->new_display('block', 'Bibliography List Block', 'block_bibliography_list');
  $export['bibliography'] = $view;

  $view = new view();
  $view->name = 'bibliography_reference';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Bibliography Reference';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Bibliography Reference';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'views-row';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_author_first_name' => 'field_author_first_name',
    'field_author_last_name' => 'field_author_last_name',
    'field_biblio_date' => 'field_biblio_date',
    'field_biblio_publisher' => 'field_biblio_publisher',
    'field_publisher_location' => 'field_publisher_location',
    'title' => 'title',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_author_first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_author_last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_biblio_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_biblio_publisher' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_publisher_location' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no bibliography items for this project.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: Content: Author First Name */
  $handler->display->display_options['fields']['field_author_first_name']['id'] = 'field_author_first_name';
  $handler->display->display_options['fields']['field_author_first_name']['table'] = 'field_data_field_author_first_name';
  $handler->display->display_options['fields']['field_author_first_name']['field'] = 'field_author_first_name';
  $handler->display->display_options['fields']['field_author_first_name']['label'] = 'hidden';
  $handler->display->display_options['fields']['field_author_first_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_author_first_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_author_first_name']['alter']['text'] = '[field_author_first_name], ';
  $handler->display->display_options['fields']['field_author_first_name']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Content: Author Last Name */
  $handler->display->display_options['fields']['field_author_last_name']['id'] = 'field_author_last_name';
  $handler->display->display_options['fields']['field_author_last_name']['table'] = 'field_data_field_author_last_name';
  $handler->display->display_options['fields']['field_author_last_name']['field'] = 'field_author_last_name';
  $handler->display->display_options['fields']['field_author_last_name']['label'] = 'hidden';
  $handler->display->display_options['fields']['field_author_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_author_last_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_author_last_name']['alter']['text'] = '[field_author_first_name][field_author_last_name]. ';
  $handler->display->display_options['fields']['field_author_last_name']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'hidden';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title]. ';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_biblio_date']['id'] = 'field_biblio_date';
  $handler->display->display_options['fields']['field_biblio_date']['table'] = 'field_data_field_biblio_date';
  $handler->display->display_options['fields']['field_biblio_date']['field'] = 'field_biblio_date';
  $handler->display->display_options['fields']['field_biblio_date']['label'] = 'hidden';
  $handler->display->display_options['fields']['field_biblio_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_biblio_date']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_biblio_date']['alter']['text'] = ', [field_biblio_date]';
  $handler->display->display_options['fields']['field_biblio_date']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Content: Publisher Location */
  $handler->display->display_options['fields']['field_publisher_location']['id'] = 'field_publisher_location';
  $handler->display->display_options['fields']['field_publisher_location']['table'] = 'field_data_field_publisher_location';
  $handler->display->display_options['fields']['field_publisher_location']['field'] = 'field_publisher_location';
  $handler->display->display_options['fields']['field_publisher_location']['label'] = 'hidden';
  $handler->display->display_options['fields']['field_publisher_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_publisher_location']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_publisher_location']['alter']['text'] = '[field_publisher_location]: ';
  $handler->display->display_options['fields']['field_publisher_location']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Content: Publisher */
  $handler->display->display_options['fields']['field_biblio_publisher']['id'] = 'field_biblio_publisher';
  $handler->display->display_options['fields']['field_biblio_publisher']['table'] = 'field_data_field_biblio_publisher';
  $handler->display->display_options['fields']['field_biblio_publisher']['field'] = 'field_biblio_publisher';
  $handler->display->display_options['fields']['field_biblio_publisher']['label'] = 'hidden';
  $handler->display->display_options['fields']['field_biblio_publisher']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_biblio_publisher']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_biblio_publisher']['alter']['text'] = '[field_publisher_location][field_biblio_publisher][field_biblio_date]';
  $handler->display->display_options['fields']['field_biblio_publisher']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_author_last_name][title][field_biblio_publisher]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bibliography' => 'bibliography',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'bibliography_items_block');
  $export['bibliography_reference'] = $view;

  return $export;
}
