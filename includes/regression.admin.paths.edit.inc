<?php

/**
 * @file
 * Settings file.
 */

/**
 * Generates form to configure new or existing regression path.
 */
function regression_paths_add_form() {

  $form['regression_paths_edit_edit']['basic_info']['path_pattern'] = array(
    '#title'       => t('Page path pattern'),
    '#description' => t("You may use '%' token to describe dynamic parameter value. E.g.: node/%/edit"),
    '#type'        => 'textfield',
    '#size'        => '50',
  );
  
  $form = system_settings_form($form);
  
  $form['actions']['submit']['#value'] = t('Next ››');
  $form['#submit'] = array('regression_paths_add_form_submit'); 
  
  return $form;
}

/**
 * Validate form submission.
 */
function regression_paths_add_form_validate($form, &$form_state) {
  if (!regression_set_path_configuration($form_state['input']['path_pattern'], array())) {
    // Path already exists.
  }
}

/**
 * Implements hook_form_submit.
 */
function regression_paths_add_form_submit($form, &$form_state) {
  $path_pattern = $form_state['values']['path_pattern']; 
  drupal_goto('admin/config/regression/paths/' . base64_encode($path_pattern));
}

/**
 * Generates form to configure new or existing regression path.
 */
function regression_paths_edit_form() {
  
  if (arg(4) == 'default') {
    // Editing default settings.
    $path_pattern = '__default';
    
    $form['regression_paths_edit_edit']['basic_info']['path'] = array(
      '#type'        => 'hidden',
      '#value'       => $path_pattern,
    );
  }
  else {
  
    $path_pattern = base64_decode(arg(4));
  
    $form['regression_paths_edit_edit']['basic_info']['path'] = array(
      '#title'       => t('Page path pattern'),
      '#type'        => 'textfield',
      '#size'        => '50',
      '#value'       => $path_pattern,
      '#attributes'  => array('disabled' => 'disabled'),
    );
  }
  
  
  $form['regression_paths_edit_edit']['key_segments'] = array(
    '#title' => t('How to identify that the page is unique'),
    '#type'  => 'fieldset',
    '#theme' => 'form_panel_table',
  );
  
  $settings         = regression_get_path_configuration($path_pattern);
  $default_settings = regression_get_path_configuration('__default');
  $keys             = regression_keys();
  
  foreach ($keys as $name => $key) {
    
    $form_container = array(
      '#type' => 'markup',
    );
    
    $form_container['checkbox'] = array(
      '#type'          => 'checkbox',
      '#title'         => t('Has unique <b>!name</b>.', array('!name' => lcfirst($key['title']))),
      '#name'          => 'key_segments_enabled[' . $name . ']',
      '#default_value' => isset($settings['key_segments_enabled']) ? isset($settings['key_segments_enabled'][$name]) : $key['default'],
    );
    
    if (isset($key['form'])) {
      $form_container['settings']['#type']   = 'fieldset';
      $form_container['settings']['#id']     = $name . '-settings-form';
      $form_container['settings']['#name']   = $name . '-settings-form';
      $form_container['settings']['#states'] = array(
        'visible' => array(
          ':input[name="key_segments_enabled[' . $name . ']"]' => array('checked' => TRUE),
        )
      );
      
      
      $key_segment_settings = isset($settings['key_segments'][$name]) ?
        $settings['key_segments'][$name] : array();
      
      if (call_user_func_array($key['form'],
          array(&$form_container['settings'], $path_pattern, $key_segment_settings)) === FALSE) {
        // Callback don't want settings form.
        $form_container['settings'] = array();
      }
      
    }
    
    $form['regression_paths_edit_edit']['key_segments'][] = $form_container;
  }
   
  $form = system_settings_form($form);
  
  
  // Notifications.
  $form['regression_notifications']['notifications'] = array(
    '#title' => t('Notifications'),
    '#type'  => 'fieldset'
  );
  
  if ($path_pattern != '__default') {
    // Notifications / Override default recipient list
    $form['regression_notifications']['notifications']['override_default_notifications_email_recipients'] = array(
      '#title'   => t('Override default recipient list'),
      '#type'    => 'checkbox',
      '#default_value' => isset($settings['override_default_notifications_email_recipients']) ?
          $settings['override_default_notifications_email_recipients'] : FALSE,
    );
    
  }

  // Notifications / Default email recipients
  $form['regression_notifications']['notifications']['default_notifications_email_recipients'] = array(
    '#name'          => 'notifications_email_recipients',
    '#title'         => t('Email recipients (default list)'),
    '#type'          => 'textarea',
    '#rows'          => 2,
    '#default_value' => isset($default_settings['notifications_email_recipients']) ? implode("\n", $default_settings['notifications_email_recipients']) : '',
  );
  
  if ($path_pattern != '__default') {
    // Displaying default recipient list for a quick look.
    $form['regression_notifications']['notifications']['default_notifications_email_recipients']['#attributes'] =
      array('disabled' => 'disabled');
    
    $form['regression_notifications']['notifications']['default_notifications_email_recipients']['#states'] =
      array(
        'visible' => array(
          ':input[name="override_default_notifications_email_recipients"]' => array('checked' => FALSE),
        )
      );
    
    // Notifications / Additional email recipients
    $form['regression_notifications']['notifications']['additional_notifications_email_recipients'] = array(
      '#name'          => 'notifications_email_recipients',
      '#title'         => t('Email recipients'),
      '#description'   => t('Please provide e-mails each on a new line.'),
      '#type'          => 'textarea',
      '#rows'          => 2,
      '#default_value' => isset($settings['notifications_email_recipients']) ? implode("\n", $settings['notifications_email_recipients']) : '',
    );
  }
  
  if ($path_pattern == '__default') {
    
    // Notifications / Regression notification e-mail template.
    $form['regression_notifications']['notifications']['notifications_email_regression_template'] = array(
      '#title'         => t('Regression notification e-mail template'),
      '#description'   => t('You can use replacements presented below.'),
      '#type'          => 'textarea',
      '#rows'          => 16,
      '#default_value' => isset($settings['notifications_email_regression_template']) ? $settings['notifications_email_regression_template'] : '',
    );
    
    // Notifications / Regression notification e-mail template replacements
    $form['regression_notifications']['notifications']['replacements'] = array(
      '#type'          => 'fieldset',
      '#title'         => 'Available replacements',
      '#collapsible'   => TRUE,
      '#collapsed'     => FALSE,
      '#attributes'    => array(
        'class' => array('collapsible'),
      ),
    );
    
    $header = array(
      'pattern' => t('Pattern'),
      'title'   => t('Description'),
      'example' => t('Example replacement'),
    );
    
    $patterns = regression_replacement_patterns_list();
    
    ksort ($patterns);
    
    $pattern_rows = array();
    foreach ($patterns as $pattern => $row) {
      $pattern_rows[] = array_merge(
        array('pattern' => '[' . $pattern . ']'),
        $row
      );
    }
  
    $form['regression_notifications']['notifications']['replacements']['table'] = array(
      '#markup' => theme('table', array('header' => $header, 'rows' => $pattern_rows)),
      '#weight' => 0,
    );
  }
  
  
  $form['actions']['submit']['#value'] = t('Save settings');
  $form['actions']['submit']['#weight'] = 1;
  
  $form['#submit'] = array('regression_paths_edit_form_submit');
  
  return $form;
}

/**
 * Implements hook_form_submit().
 */
function regression_paths_edit_form_submit($form, &$form_state) {
  
  $settings = array(
    'key_segments'         => array(),
    'key_segments_enabled' => array(),
  );
  
  $keys = regression_keys();
  
  foreach ($keys as $name => $key) {
    if (isset($form_state['input'][$name])) {
      // There are settings for the key segment.
      $settings['key_segments'][$name] = $form_state['input'][$name];
    }
  }
  
  $settings['key_segments_enabled'] =
    isset($form_state['input']['key_segments_enabled']) ?
    $form_state['input']['key_segments_enabled'] : '';
  
  $settings['notifications_email_recipients'] =
    isset($form_state['input']['notifications_email_recipients']) ?
    explode("\n", $form_state['input']['notifications_email_recipients']) : array();
  
  $settings['notifications_email_regression_template'] =
    isset($form_state['input']['notifications_email_regression_template']) ?
    $form_state['input']['notifications_email_regression_template'] : '';
  
  $settings['override_default_notifications_email_recipients'] =
    isset($form_state['input']['override_default_notifications_email_recipients']) ?
    $form_state['input']['override_default_notifications_email_recipients'] : FALSE;
  
  regression_set_path_configuration($form_state['values']['path'], $settings);
  
  drupal_set_message(t('Path settings have been saved.'));
}

/**
 * Generates form to configure unique page arguments.
 * 
 * @param array $container
 *   Form API fieldset.
 * @param string $path_patern
 *   Menu path pattern.
 * @param array $settings
 *   Array of settings previously saved using this form.
 */
function regression_paths_edit_page_arguments_form(&$container, $path_pattern, $settings) {

  if ($path_pattern == '__default') {
    // We don't provide settings for the default pattern.
    return FALSE;
  }
  
  $container['#title']      = t('Please select unique parameters');
  $container['#attributes'] = array('class' => array('container-inline'));
  
  $segments     = explode('/', $path_pattern);
  $num_segments = count($segments);
  
  // Generating path trail with checkboxes.
  $param_index = 0;
  for ($i = 0; $i < $num_segments; $i++) {
    $segment = &$segments[$i];
    
    if ($segment == '%') {
      // Dynamic parameter, creating checkbox.
      $container['uniques'][] = array(
        '#type'          => 'checkbox',
        '#title'         => '',
        '#name'          => 'builtin-page-arguments[uniques][' . $param_index . ']',
        '#default_value' => isset($settings['uniques'][$param_index]) ? $settings['uniques'][$param_index] : FALSE,
      );
      
      ++$param_index;
    }
    else {
      // Slash.
      $container['uniques'][] = array(
        '#markup' => '<span>' . $segment . '</span>',
      );
    }
    
    if ($i < $num_segments - 1) {
      // This is not the last segment, we're adding slash to separate segments.
      $container['uniques'][] = array(
        '#markup' => '<span style="font-size: 18px; margin: 0 5px;">/</span>',
      );
    }
  }

  if (0)
  $container['custom_unique_args'] = array(
    '#title'         => t('Email recipients (default list)'),
    '#description'   => t('Please separate argument indexes by comma. Index number starts from 0 and counts every path segment.'),
    '#type'          => 'textfield',
    '#size'          => 50,
    '#default_value' => isset($settings['custom_unique_args']) ? $default_settings['custom_unique_args'] : '',
  );
}
