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
    '#type'  => 'fieldset'
  );

  $form['regression_status']['list']['default'] = array(
   '#type' => 'link',
    '#title' => t('Edit default regression test settings.'),
    '#href' => 'admin/config/regression/paths/default',
    '#options' => array(
      'html' => true,
    ),
    '#suffix' => '<div style="height: 10px;"></div>',
  );
  
  $header = array(
    'menu_path' => t('Menu path'),
    'page_path' => t('Page path'),
    'path_args' => t('Page arguments'),
    'state'     => t('Status'),
    'actions'   => t('Actions'),
  );
    
  $status_rows = regression_status();
  
  $paths_rows = array();
  
  foreach ($status_rows as $row) {
    
    $actions =
      l(t('Edit settings'), 'admin/config/regression/paths/' . base64_encode($row['path'])) . ' | ' .
      l(t('Delete'),        'admin/config/regression/paths/' . base64_encode($row['path']) . '/remove');
    
    switch ($row['state']) {
      case REGRESSION_ENTRY_STATE_CANDIDATE:
        $state_text  = t('Awaiting approval');
        $state_class = 'state-awaiting-approval';
        $actions    .= ' | ' . l(t('Take action'), 'admin/config/regression/take-action/' . $row['last_revision_pid']);
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
    
    $paths_rows[] = array(
      'menu_path' => $row['path'],
      'page_path' => ($row['uri'] !== '') ? l($row['uri'], $row['uri']) : 'N/A',
      'path_args' => $row['path_args'],
      'state'     => '<div class="state ' . $state_class . '">' . $state_text . '</div>',
      'actions'   => $actions,
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
