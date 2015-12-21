<?php

/**
 *  @function:
 *    Takepart oembed admin form
 */
function getty_expose_project_admin_form($form, &$form_state)  {
  $form = array();
  
  //intro message
  $form['getty_expose_project_intro'] = array(
    '#markup' => t("
      Configuration for project service for Getty.<br/>
      Flush cache to clear out all stale cache.<br/><br/>
      Uses: service/project/[format=json|xml]?project=[project_nid][&download=1][&break_cache=1]<br/></br>
      format = json or xml<br/>
      break_cache = true to rebuild cache data<br/><br/>
    "),
  );
  
  //service url
  $form['getty_expose_project_service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL Service Path'),
    '#description' => t('URL service. Empty value will disable service for oembed after menu path rebuilds.'),
    '#default_value' => variable_get('getty_expose_project_service_url', 'service/projects')
  );
  
  //set up cache time
  $form['getty_expose_project_cache_time'] = array(
    '#type' => 'select',
    '#title' => t('Cache Time for API service'),
    '#options' => array(
      0 => 0,
      5 => 5,
      10 => 10,
      15 => 15,
      30 => 30,
      60 => 60
    ),
    '#default_value' => variable_get('getty_expose_project_cache_time', 10)
  );
  
  return system_settings_form($form);
}
