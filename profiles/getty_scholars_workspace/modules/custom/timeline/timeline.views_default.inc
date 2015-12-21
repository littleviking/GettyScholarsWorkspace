<?php
/**
 * @file
 * timeline.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function timeline_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'project_timeline';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Timeline';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Timeline';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
    ),
  );
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'timelinejs';
  $handler->display->display_options['style_options']['timeline_theme'] = array(
    'width' => '100',
    'width_unit' => '1',
    'height' => '600',
    'height_unit' => '0',
  );
  $handler->display->display_options['style_options']['timeline_fields'] = array(
    'headline' => 'title',
    'bodytext' => 'body',
    'date' => 'field_timeline_dates',
    'media' => 'field_timeline_media_image',
    'credit' => '0',
    'caption' => '0',
    'tag' => '0',
  );
  $handler->display->display_options['style_options']['timeline_config'] = array(
    'link_to_entity' => 1,
    'link_text_enabled' => 0,
    'link_text' => '',
    'strip_tags' => '0',
    'hash_bookmark' => '0',
    'start_at_end' => '0',
    'start_zoom_adjust' => '1',
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no timeline dates entered for this project.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Caption Text */
  $handler->display->display_options['fields']['field_timeline_caption_text']['id'] = 'field_timeline_caption_text';
  $handler->display->display_options['fields']['field_timeline_caption_text']['table'] = 'field_data_field_timeline_caption_text';
  $handler->display->display_options['fields']['field_timeline_caption_text']['field'] = 'field_timeline_caption_text';
  /* Field: Content: Dates */
  $handler->display->display_options['fields']['field_timeline_dates']['id'] = 'field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['table'] = 'field_data_field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['field'] = 'field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['settings'] = array(
    'format_type' => 'mdy',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Media Image */
  $handler->display->display_options['fields']['field_timeline_media_image']['id'] = 'field_timeline_media_image';
  $handler->display->display_options['fields']['field_timeline_media_image']['table'] = 'field_data_field_timeline_media_image';
  $handler->display->display_options['fields']['field_timeline_media_image']['field'] = 'field_timeline_media_image';
  /* Field: Content: Media Link */
  $handler->display->display_options['fields']['field_timeline_media_link']['id'] = 'field_timeline_media_link';
  $handler->display->display_options['fields']['field_timeline_media_link']['table'] = 'field_data_field_timeline_media_link';
  $handler->display->display_options['fields']['field_timeline_media_link']['field'] = 'field_timeline_media_link';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body_1']['id'] = 'body_1';
  $handler->display->display_options['fields']['body_1']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body_1']['field'] = 'body';
  $handler->display->display_options['fields']['body_1']['type'] = 'text_plain';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  /* Contextual filter: Field: Groups audience (og_group_ref) */
  $handler->display->display_options['arguments']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['exception']['value'] = '';
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
    'timeline_date' => 'timeline_date',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'project/%/timeline';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'timeline_container';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $export['project_timeline'] = $view;

  return $export;
}
