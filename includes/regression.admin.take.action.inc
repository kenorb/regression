<?php

/**
 * @file
 * Settings file.
 */

/**
 * Generates form to configure module.
 */
function regression_take_action_form() {

  $revision_pid = arg(4);
  
  $revision     = regression_revision_load($revision_pid);
  
  $form['regression_take_action']['revision_info']['page_path'] = array(
    '#markup'  => '<div class="form-item"><label>' . t('Menu path') . '</label>' . $revision -> path . '</div>',
  );
  
  $form['regression_take_action']['revision_info']['revision'] = array(
    '#markup'  => '<div class="form-item"><label>' . t('Current revision') . '</label>' . $revision -> revision_id . '</div>',
  );
  
  $form['regression_take_action']['actions'] = array(
    '#title'   => 'Available actions',
    '#type'    => 'radios',
    '#options' => array(
      'approve'    => t('Approve the change and set the page as default'),
      'ignore'     => t('Mark that change as dynamic (ignore it in the future)'),
      'regression' => t('Mark as regression'),
      'broken'     => t('Mark as broken'),
    ),
   );
  
  // Information.
  $form['regression_take_action']['changes'] = array(
    '#title' => t('Changes'),
    '#type'  => 'fieldset'
  );
  
  $form['regression_take_action']['changes']['diff'] = array(
    '#markup'  => nl2br($revision->parser_value_plain_text_diff),
  );
  
  $form = system_settings_form($form);

  return $form;
}

/**
 * Validate form submission.
 */
function regression_take_action_form_validate($form, &$form_state) {
}

/**
 * Implements hook_form_submit().
 */
function regression_take_action_form_submit($form, &$form_state) {
}
