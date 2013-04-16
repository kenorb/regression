<?php

/**
 * @file
 * Settings file.
 */

/**
 * Generates form to configure module.
 */
function regression_paths_form() {
  
  $form['regression_paths']['list'] = array(
    '#title' => t('Configured paths'),
    '#type'  => 'fieldset'
  );

  $form['regression_paths']['list']['default'] = array(
   '#type' => 'link',
    '#title' => t('Edit default regression test settings.'),
    '#href' => 'admin/config/regression/paths/default',
    '#options' => array(
      'html' => true,
    ),
    '#suffix' => '<div style="height: 10px;"></div>',
  );
  
  $header = array(
    'enabled'  => t('Enabled'),
    'path'     => t('Path'),
    'features' => t('Enabled features'),
    'actions'  => t('Actions'),
  );
  
  $configured_paths = regression_paths_configured();
  
  $paths_rows = array();
  
  foreach ($configured_paths as $row) {
    
    $actions =
      l(t('Edit settings'), 'admin/config/regression/paths/' . base64_encode($row['path'])) . ' | ' .
      l(t('Delete'),        'admin/config/regression/paths/' . base64_encode($row['path']) . '/remove');
    
    $enabled_widget = array(
      '#type'    => 'checkbox',
      '#name'    => 'enabled[' . $row['pid'] . ']',
      '#title'   => '',
      '#checked' => $row['enabled'],
    );
    
    $paths_rows[] = array(
      'enabled'  => drupal_render($enabled_widget),
      'path'     => ($row['path'] == '__default') ? ('<b>' . t('Default settings') . '</b>') : $row['path'],
      'features' => $row['features'],
      'actions'  => $actions,
    );
  }

  $form['regression_paths']['list']['table'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $paths_rows)),
    '#weight' => 0,
  );

  $form['regression_paths']['list']['add_new_path'] = array(
    '#type'   => 'submit',
    '#value'  => t('Add new path'),
    '#executes_submit_callback' => TRUE,
    '#submit' => array('regression_path_action_add_path'),
  );
  
  
  $form = system_settings_form($form);
  
  unset($form['#submit']);
  unset($form['actions']['submit']);

  return $form;
}

function regression_path_action_add_path($form, $form_state) {
  drupal_goto('admin/config/regression/paths/add');
}

/**
 * Validate form submission.
 */
function regression_paths_form_validate($form, &$form_state) {
}

/**
 * Implements hook_form_submit().
 */
function regression_paths_form_submit($form, &$form_state) {
  drupal_set_message(t('Path has been added.'));
}
