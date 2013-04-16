<?php

/**
 * @file
 * Settings file.
 */

/**
 * Generates form to configure module.
 */
function regression_advanced_form() {

  // Source Parsers.
  $form['regression_advanced']['parsers'] = array(
    '#title' => t('Enabled source parsers'),
    '#type'  => 'fieldset'
  );
  
  // Source Parsers / HTML.
  $form['regression_advanced']['parsers']['regression_advanced_enabled_parsers_html'] = array(
    '#title'         => t('HTML'),
    '#type'          => 'checkbox',
    '#default_value' => variable_get('regression_advanced_enabled_parsers_html', TRUE),
  );

  // Source Parsers / Plain Text.
  $form['regression_advanced']['parsers']['regression_advanced_enabled_parsers_plain_text'] = array(
    '#title'         => t('Plain Text'),
    '#type'          => 'checkbox',
    '#default_value' => variable_get('regression_advanced_enabled_parsers_plain_text', TRUE),
  );
  
  // Source Parsers / Markdown.
  $form['regression_advanced']['parsers']['regression_advanced_enabled_parsers_markdown'] = array(
    '#title'         => t('Markdown'),
    '#type'          => 'checkbox',
    '#default_value' => variable_get('regression_advanced_enabled_parsers_markdown', FALSE),
  );
  

  $form = system_settings_form($form);

  return $form;
}

/**
 * Validate form submission.
 */
function regression_advanced_form_validate($form, &$form_state) {
}

/**
 * Implements hook_form_submit().
 */
function regression_advanced_form_submit($form, &$form_state) {
}
