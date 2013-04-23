<?php

/**
 * @file
 * Settings file.
 */

/**
 * Generates form to configure module.
 */
function regression_status_form() {
  
  drupal_add_css(drupal_get_path('module', 'regression') . '/styles/regression.css');
  
  $form['regression_status']['list'] = array(
    '#title' => t('Paths status'),
    '#type'  => 'fieldset',
  );

  $header = array(
    'menu_path'     => t('Menu path'),
    'page_path'     => t('Page path'),
    'path_args'     => t('Page arguments'),
    'module'        => t('Related module'),
    'assignee'      => t('Assignee'),
    'last_working'  => t('Last working revision'),
    'state'         => t('Status'),
    'actions'       => t('Actions'),
  );
    
  $status_rows = regression_status();
  
  $paths_rows = array();
  
  foreach ($status_rows as $row) {
    
    if ($row['state'] == REGRESSION_ENTRY_STATE_CANDIDATE) {
      $actions = '<b>' . l(t('Take action'), 'admin/config/regression/review/' . $row['last_revision_pid']) . '</b>';
    }
    else {
      $actions = '<b>' . l(t('View'), 'admin/config/regression/review/' . $row['last_revision_pid']) . '</b>';
    }
    
    $actions .= ' | ' . l(t('Delete'), 'admin/config/regression/paths/' . base64_encode($row['path']) . '/remove');
    
    $actions .= ' | ' . l(t('Path settings'), 'admin/config/regression/paths/' . base64_encode($row['path']));
      
    switch ($row['state']) {
      case REGRESSION_ENTRY_STATE_CANDIDATE:
        $state_text  = t('Awaiting approval');
        $state_class = 'state-awaiting-approval';
        break;
        
      case REGRESSION_ENTRY_STATE_APPROVED:
        $state_text  = t('Approved');
        $state_class = 'state-approved';
        break;
        
      case REGRESSION_ENTRY_STATE_BROKEN:
        $state_text  = t('Broken');
        $state_class = 'state-broken';
        break;
        
      case REGRESSION_ENTRY_STATE_REGRESSION:
        $state_text  = t('Regression');
        $state_class = 'state-regression';
        break;
    }

    $assignee_user = user_load_by_name(check_plain($row['assignee']));
    
    if ($assignee_user) {
      $assignee = l($assignee_user->name, 'user/' . $assignee_user->uid);
    }
    else {
      $assignee = check_plain($assignee);
    }
    
    if (!empty($row['current_working_revision_pid'])) {
      if ($row['current_working_revision_pid'] === $row['current_revision_pid']) {
        $title = t('#!num (Current revision)', array(
          '!num'  => '<b>' . $row['current_working_revision_id'] . '</b>',
        ));
      }
      else {
        $title = t('#!num on %date', array(
          '!num'  => '<b>' . $row['current_working_revision_id'] . '</b>',
          '%date' => date('d/m/Y H:i:s', $row['updated'])
        ));
      }
      $last_working_revision = l($title, 'admin/config/regression/review/' . $row['current_working_revision_pid'], array('html' => TRUE));
    }
    else {
       $last_working_revision = t('N/A');
    }
      
    
    
    $paths_rows[] = array(
      'menu_path'     => $row['path'],
      'page_path'     => ($row['uri'] !== '') ? l($row['uri'], $row['uri']) : 'N/A',
      'path_args'     => $row['path_args'],
      'module'        => $row['related_module_name'],
      'assignee'      => $assignee,
      'last_working'  => $last_working_revision,
      'state'         => '<div class="state ' . $state_class . '">' . $state_text . '</div>',
      'actions'       => $actions,
    );
  }

  $form['regression_status']['list']['table'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $paths_rows)),
    '#weight' => 0,
  );

  $form = system_settings_form($form);
  
  unset($form['#submit']);
  unset($form['actions']['submit']);

  return $form;
}

/**
 * Validate form submission.
 */
function regression_status_form_validate($form, &$form_state) {
}

/**
 * Implements hook_form_submit().
 */
function regression_status_form_submit($form, &$form_state) {
}
