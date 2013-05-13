<?php

/**
 * @file
 * Settings file.
 */

/**
 * Generates form to remove regression path.
 */
function regression_path_remove_form() {

  $form['regression_paths_edit_edit']['basic_info']['path_pattern'] = array(
    '#title'         => t('Page path pattern'),
    '#type'          => 'textfield',
    '#size'          => '50',
    '#default_value' => check_plain(base64_decode(arg(4))),
    '#attributes'    => array('disabled' => 'disabled'),
  );

  $form = system_settings_form($form);

  $form['actions']['submit']['#value'] = t('Remove path');
  $form['#submit'] = array('regression_path_remove_form_submit');

  return $form;
}

/**
 * Implements hook_form_submit().
 */
function regression_path_remove_form_submit($form, &$form_state) {
  $path_pattern = check_plain($form_state['values']['path_pattern']);

  // Removing path configuration.
  db_delete('regression_path_configuration')
    ->condition('path', $path_pattern)
    ->execute();

  // Removing regression entries.
  db_delete('regression_entry')
    ->condition('path', $path_pattern)
    ->execute();

  // Removing regression revisions.
  db_delete('regression_revision')
    ->condition('path', $path_pattern)
    ->execute();

  drupal_set_message(t('Path removed from regression testing.'));
  drupal_goto('admin/config/regression/paths');
}
