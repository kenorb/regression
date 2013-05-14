<?php

/**
 * @file
 * RegressionRevision entity include file.
 */

require_once 'regression.regression_revision.controller.inc';

/**
 * Entity general information.
 */
function regression_regression_revision_entity_info(&$info) {
  $info['regression_revision'] = array(
    'label'            => t('Regression Revision'),
    'entity class'     => 'RegressionRevision',
    'controller class' => 'RegressionRevisionController',
    'views controller class' => 'EntityDefaultViewsController',
    'base table'       => 'regression_revision',
    'uri callback'     => 'entity_class_uri',
    'label callback'   => 'entity_class_label',
    'fieldable'        => TRUE,
    'entity keys' => array(
      'id' => 'pid',
    ),
    'static cache' => TRUE,
    'bundles' => array(
      'regression_revision' => array(
        'label' => 'Regression Revision',
        'admin' => array(
          'path'             => 'admin/structure/regression-revisions',
          'access arguments' => array('regression administration'),
        ),
      ),
    ),
    'view modes' => array(
      'full' => array(
        'label'           => t('Full Regression Revision'),
        'custom settings' => FALSE,
      ),
    ),
    'admin ui' => array(
      'path'             => 'admin/structure/regression-revisions',
      'file'             => 'regression.regression_revision.controller.inc',
      'controller class' => 'RegressionRevisionUIController',
    ),

  );

  // Support entity cache module.
  if (module_exists('entitycache')) {
    $info['regression_revision']['field cache']  = FALSE;
    $info['regression_revision']['entity cache'] = TRUE;
  }
}

/**
 * Adds custom fields into the entity.
 */
function regression_regression_revision_field_extra_fields(&$return) {
  $return['regression_revision']['regression_revision'] = array(
    'form' => array(),
    'display' => array(),
  );
}

/**
 * Implements hook_entity_property_info_alter().
 */
function regression_regression_revision_entity_property_info_alter(&$info) {
  $properties = &$info['regression_revision']['properties'];
}

/**
 * Title of the /admin/structure/regression-revision page.
 */
function regression_regression_revision_info() {
  return 'Regression Revisions';
}

/**
 * Implements the uri callback.
 */
function regression_regression_revision_uri($entity) {
  return array(
    'path' => 'regression/take-action/' . $entity->uuid,
  );
}

/**
 * Returns regression revision record title.
 */
function regression_regression_revision_page_title($entity) {
  return $entity->pid;
}

/**
 * Page that displays the entity.
 */
function regression_regression_revision_page_view($entity, $view_mode = 'full') {
  // Our entity type, for convenience.
  $entity_type = 'regression_revision';

  // Start setting up the content.
  $entity->content = array(
    '#view_mode' => $view_mode,
  );

  // Build fields content - this is where the Field API really comes in to play.
  // field_attach_prepare_view() lets the fields load any data they need
  // before viewing.
  field_attach_prepare_view($entity_type, array($entity->pid => $entity), $view_mode);

  // We call entity_prepare_view() so it can invoke hook_entity_prepare_view()
  // for us.
  entity_prepare_view($entity_type, array($entity->pid => $entity));

  // Now field_attach_view() generates the content for the fields.
  $entity->content += field_attach_view($entity_type, $entity, $view_mode);

  return $entity->content;
}

/**
 * Form of entity edit.
 */
function regression_regression_revision_form_edit($form, &$form_state, $entity) {
  return $form;
}

/**
 * Form of regression revision deletion.
 */
function regression_regression_revision_form_remove($form, &$form_state, $entity) {
  return $form;
}

/**
 * Action of regression revision deletion.
 */
function regression_regression_revision_edit_delete($form, &$form_state) {
}

/**
 * Action of regression revision saving.
 */
function regression_regression_revision_edit_save($form, &$form_state) {
  return $form;
}

/**
 * Form of entity creation.
 */
function regression_regression_revision_form($form, &$form_state, $entity, $input) {
  return $form;
}

/**
 * Validation for the entity creation page.
 */
function regression_regression_revision_form_validate($form, &$form_state) {
  field_attach_form_validate('regression_revision', $entity, $form, $form_state);
}

/**
 * Submission handler for the entity creation page.
 */
function regression_regression_revision_form_submit($form, &$form_state) {
}

/**
 * Submission handler for regression revision adding page.
 */
function regression_regression_revision_form_add($input) {
  return drupal_get_form('regression_regression_revision_form', $entity, $input);
}

/**
 * Provides a list of existing entities and the ability to add more.
 *
 * Tabs provide field and display management.
 */
function regression_regression_revision_admin_page() {
  $content = array();
  $content[] = array(
    '#type' => 'item',
    '#markup' => t('Administration page for regression revisions.'),
  );

  $content['table'] = regression_regression_revision_list_entities();

  return $content;
}

/**
 * Returns list of regression revision entries.
 */
function regression_regression_revision_list_entities() {
  return array();
}

/**
 * Entity management pages paths.
 */
function regression_regression_revision_menu(&$items) {
  $items['admin/structure/regression-revisions'] = array(
    'title'            => 'Regression Revisions',
    'description'      => 'Manage regression revisions',
    'page callback'    => 'regression_regression_revision_admin_page',
    'access arguments' => array('regression administration'),
  );
}

/**
 * Access handler for the entity.
 */
function regression_regression_revision_access($op, $task, $account = NULL, $entity_type = NULL) {
  global $user;

  if (!isset($account)) {
    $account = $user;
  }
  switch ($op) {
    case 'create':
      return FALSE;
  }
}

/**
 * Fetch a basic object.
 *
 * This function ends up being a shim between the menu system and
 * regression_regression_revision_load_multiple().
 *
 * This function gets its name from the menu system's wildcard
 * naming conventions. For example, /path/%wildcard would end
 * up calling wildcard_load(%wildcard value). In our case defining
 * the path: examples/entity_example/basic/%entity_example_basic in
 * hook_menu() tells Drupal to call entity_example_basic_load().
 *
 * @param number $basic_id
 *   Integer specifying the basic entity id.
 * @param bool $reset
 *   A boolean indicating that the internal cache should be reset.
 *
 * @return RegressionRevision
 *   A fully-loaded $basic object or FALSE if it cannot be loaded.
 *
 * @see entity_example_basic_load_multiple()
 * @see entity_example_menu()
 */
function regression_revision_load($basic_id = NULL, $reset = FALSE) {
  $basic_ids = (isset($basic_id) ? array($basic_id) : array());
  $basic = regression_regression_revision_load_multiple($basic_ids, array(), $reset);
  return $basic ? reset($basic) : FALSE;
}

/**
 * Loads multiple basic entities.
 *
 * We only need to pass this request along to entity_load(), which
 * will in turn call the load() method of our entity controller class.
 *
 * @see entity_load()
 * @see EntityFieldQuery
 *
 * @param array $pids
 *   An array of regression revision IDs.
 * @param array $conditions
 *   (deprecated) An associative array of conditions on the node
 *   table, where the keys are the database fields and the values are the
 *   values those fields must have. Instead, it is preferable to use
 *   EntityFieldQuery to retrieve a list of entity IDs loadable by
 *   this function.
 * @param bool $reset
 *   Whether to reset the internal node_load cache.
 *
 * @return array
 *   An array of node objects indexed by ids.
 */
function regression_regression_revision_load_multiple($pids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('regression_revision', $pids, $conditions, $reset);
}

/**
 * Saves regression revision entity.
 */
function regression_regression_revision_save($entity) {
  entity_save('regression_revision', $entity);
  return $entity;
}

/**
 * Deletes a single regression revisions.
 */
function regression_regression_revision_delete($id) {
  entity_delete('regression_revision', entity_id('regression_revision', $id));
}

/**
 * Deletes multiple regression revisions.
 */
function regression_regression_revision_delete_multiple($ids) {
  entity_delete_multiple('regression_revision', $ids);
}
