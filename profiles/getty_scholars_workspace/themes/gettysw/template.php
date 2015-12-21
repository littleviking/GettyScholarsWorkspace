<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 *
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */

function gettysw_preprocess_node(&$vars) {
  $node = $vars['node'];
  if ($node->type == 'essay' && isset($vars['user'])) {
    $u = user_load($node->uid);
    $vars['submitted'] = t('Author: @name<br />Date: @dt', array('@name' => $u->name, '@dt' => format_date($node->created, 'mdy')));
  }
  elseif ($node->type == 'forum') {
    $vars['submitted'] = t('Submitted by !username<br />!datetime', array('!username' => $vars['name'], '!datetime' => $vars['date']));
  }
}

/**
 * Add link to view full-sized image in colorbox and add caption
 */
function gettysw_preprocess_field(&$vars, $hook) {
  foreach ($vars['element']['#items'] as $delta => $item) {
    if (!empty($vars['element'][$delta])) {
      if (module_exists('image_field_caption') && isset($item['image_field_caption'])) {
        $vars['items'][$delta]['caption'] = check_markup($item['image_field_caption']['value'], $item['image_field_caption']['format']);
      }
      if ($vars['element']['#field_name'] == 'field_image' && isset($item['uri']) && module_exists('colorbox')) {
        $vars['items'][$delta]['colorbox_link'] = '<a class="colorbox" href="' . file_create_url($item['uri']) . '">View full-size image</a>';
      }
    }
  }
}

function gettysw_preprocess_links(&$vars) {
  if (isset($vars['attributes']['id']) && $vars['attributes']['id'] == 'secondary-menu') {
    $links = $vars['links'];
    foreach ($links as $id => $link) {
      if ($link['title'] == 'My account') {
        global $user;
        $vars['links'][$id]['title'] = $user->name;
      }
    }
  }
}

/**
 * Set correct path for comment modification tabs
 */
function gettysw_menu_local_task(&$vars) {
  $link = $vars['element']['#link'];
  $link_text = $link['title'];

  // Add the id to the end of the URL of the local task.
  $id = arg(3);
  $altered_paths = array('comment/%/edit', 'comment/%/delete');
  if (isset($id) && is_numeric($id) && in_array($link['path'], $altered_paths)) {
    $link['href'] .= '/' . $id;
  }

  if (!empty($vars['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  return '<li' . (!empty($vars['element']['#active']) ? ' class="active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
}

function gettysw_preprocess_page(&$vars) {
  switch (current_path()) {
    case 'user':
      if (isset($vars['tabs'])) {
        $vars['tabs'] = null;
        $vars['title_hidden'] = 1;
        break;
      }
    case 'user/register':
      if (isset($vars['tabs'])) {
        $vars['title_hidden'] = 1;
        $vars['tabs'] = null;
        break;
      }
    case 'user/password':
      drupal_set_title('Request a new password');
      if (isset($vars['tabs'])) {
        $vars['tabs'] = null;
        break;
      }
    default:
    break;
  }
}

/**
 * Implements hook_preprocess().
 */
function gettysw_preprocess_html(&$vars) {
  $is_project_dashboard = (arg(0) == 'project' && is_numeric(arg(1)) && arg(2) == NULL);
  $vars['attributes_array']['class'][] = ($is_project_dashboard ? 'is-project-dashboard' : 'not-project-dashboard');
}
