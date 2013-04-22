<?php

/**
 * @file
 * Settings file.
 */

/**
 * Generates form to configure module.
 */
function regression_take_action_form() {
  
  drupal_add_css(drupal_get_path('module', 'regression') . '/styles/regression.css');

  $revision_pid              = arg(4);
  $revision                  = regression_revision_load($revision_pid);
  $entry                     = regression_entry_load($revision->entry_id);
  $last_working_revision_id  = $entry->current_working_revision_id;
  $last_working_revision_pid = $entry->current_working_revision_pid;
  
  
  $info_header = array(
    'path'                  => t('Menu path'),
    'uri'                   => t('Page path'),
    'last_working_revision' => t('Last working revision'),
    'current_revision'      => t('Revision candidate'),
  );
  
  if ($last_working_revision_id === NULL) {
    $last_working_revision_name = 'N/A';
  }
  else {
    $last_working_revision      = regression_revision_load($last_working_revision_pid);
    $last_working_revision_name = t('#!num on %date', array('!num' => $last_working_revision_id, '%date' => date('d/m/Y H:i:s', $last_working_revision->updated)));
  }
  
  $revision_candidate_text = t('#!num on %date', array('!num' => $revision->revision_id, '%date' => date('d/m/Y H:i:s', $revision->updated)));
  
  $info_rows = array(array(
    'path'                  => $revision->path,
    'uri'                   => l($revision->uri, $revision->uri),
    'last_working_revision' => $last_working_revision_name,
    'current_revision'      => $revision_candidate_text,
  ));
  
  $form['regression_take_action']['info']['table'] = array(
    '#markup' => theme('table', array('header' => $info_header, 'rows' => $info_rows)),
    '#weight' => 0,
  );
    
  if ($entry->state == REGRESSION_ENTRY_STATE_CANDIDATE) {
    
    $form['regression_take_action']['#weight'] = 1;
    $form['regression_take_action']['actions'] = array(
      '#title'         => 'Available actions',
      '#type'          => 'radios',
      '#default_value' => 'approve',
      '#options'       => array(
        'approve'    => t('Approve the change and set the page as default'),
        'ignore'     => t('Mark that change as dynamic (ignore it in the future)'),
        'regression' => t('Mark as regression'),
        'broken'     => t('Mark as broken'),
      ),
     );
    
    
    // Information.
    $form['regression_take_action_changes'] = array(
      '#weight' => 5,
      '#title'  => t('Changes'),
      '#type'   => 'fieldset'
    );
    
    $form['regression_take_action_changes']['diff'] = array(
      '#markup'  => '<div class="diff">' . nl2br($revision->parser_value_plain_text_diff) . '</div>',
    );
    
    $form = system_settings_form($form);
    
    $form['actions']['submit']['#value'] = t('Resolve');
    $form['actions']['#weight'] = 2;
    $form['#submit'] = array('regression_take_action_form_submit');
  }
  else {
    
    switch ($entry->state) {
      case REGRESSION_ENTRY_STATE_APPROVED:
        $state_text = t('approved');
        break;
      case REGRESSION_ENTRY_STATE_BROKEN:
        $state_text = t('broken');
        break;
      case REGRESSION_ENTRY_STATE_REGRESSION:
        $state_text = t('a regression');
        break;
    }
      
    $form['regression_take_action']['state'] = array(
      '#markup' => '<div class="state">' . t('Page is already marked as <b>!state</b>.', array('!state' => $state_text)) . '</div>',
    );
    
    // No actions available.
    unset($form['#submit']);
    unset($form['actions']['submit']);
  }

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
  
  $revision_pid = arg(4);
  
  $revision = regression_revision_load($revision_pid);
  $entry    = regression_entry_load($revision->entry_id);
  
  switch ($form_state['input']['actions']) {
    case 'approve':
      $entry->state                        = REGRESSION_ENTRY_STATE_APPROVED;
      $entry->current_working_revision_id  = $revision->revision_id;
      $entry->current_working_revision_pid = $revision->pid;
      $entry->save();
      break;
    
    case 'ignore':
      break;
    
    case 'regression':
      $entry->state                       = REGRESSION_ENTRY_STATE_REGRESSION;
      $entry->save();
      break;
    
    case 'broken':
      $entry->state                       = REGRESSION_ENTRY_STATE_BROKEN;
      $entry->save();
      break;
  }
  
  
}
