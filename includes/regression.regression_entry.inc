<?php

require_once 'regression.regression_entry.controller.inc';

/**
 * Entity general information
 */
function regression_regression_entry_entity_info(&$info) {
  $info['regression_entry'] = array(
    'label'            => t('Regression Entry'),
    'entity class'     => 'RegressionEntry',
    'controller class' => 'RegressionEntryController',
    'views controller class' => 'EntityDefaultViewsController',
    'base table'       => 'regression_entry',
    'uri callback'     => 'entity_class_uri',
    'label callback'   => 'entity_class_label',
    'fieldable'        => TRUE,
    'entity keys' => array(
      'id' => 'pid'
    ),
    'static cache' => TRUE,
    'bundles' => array(
      'regression_entry'=> array(
        'label' => 'Regression Entry',
        'admin' => array(
          'path'             => 'admin/structure/regression-entries',
          'access arguments' => array('regression administration'),
        ),
      ),
    ),
    'view modes' => array(
      'full' => array(
        'label'           => t('Full Regression Entry'),
        'custom settings' =>  FALSE,
      ),
    ),
    'admin ui' => array(
      'path'             => 'admin/structure/regression-entries',
      'file'             => 'regression.regression_entry.controller.inc',
      'controller class' => 'RegressionEntryUIController',
    ),
      
  );
  
  // Support entity cache module.
  if (module_exists('entitycache')) {
    $info['regression_entry']['field cache']  = FALSE;
    $info['regression_entry']['entity cache'] = TRUE;
  }
}

/**
 * Adds custom fields into the entity.
 */
function regression_regression_entry_field_extra_fields(&$return) {
  $return['regression_entry']['regression_entry'] = array(
    'form' => array(
      'revision' => array(
        'label'       => t('Revision'),
        'description' => t('ID of the entry revision'),
        'weight'      => 0,
      ),
      'uuid' => array(
        'label'       => t('UUID'),
        'description' => t('Unique identifier of entry'),
        'weight'      => 0,
      ),
      'created' => array(
        'label'       => t('Created'),
        'description' => t('Creation date'),
        'weight'      => 1,
      ),
      'updated' => array(
        'label'       => t('Updated'),
        'description' => t('Last update date'),
        'weight'      => 2,
      ),
      'path' => array(
        'label'       => t('Path to the page'),
        'description' => t('Path to the controlled page'),
        'weight'      => 3,
      ),
      'parser_value_html' => array(
        'label'       => t('Parser value: Original HTML'),
        'description' => t('Original HTML source of the page'),
        'weight'      => 4,
      ),
      'parser_value_plain_text' => array(
        'label'       => t('Parser value: Plain text'),
        'description' => t("A result of conversion of the page's HTML source to plain text"),
        'weight'      => 5,
      ),
      'parser_value_markdown' => array(
        'label'       => t('Parser value: Markdown'),
        'description' => t("A result of conversion of the page's HTML source to Markdown format"),
        'weight'      => 6,
      ),
      'view_link' => array(
        'label'       => t('View link'),
        'description' => t('View link'),
        'weight'      => 100,
      ),
      'edit_link' => array(
        'label'       => t('Edit link'),
        'description' => t('Edit link'),
        'weight'      => 101,
      ),
      'remove_link' => array(
        'label'       => t('Remove link'),
        'description' => t('Remove link'),
        'weight'      => 102,
      ),
    ),
    'display' => array(
      'created' => array(
        'label'       => t('Created'),
        'description' => t('Creation date'),
        'weight'      => 1,
      ),
      'updated' => array(
        'label'       => t('Updated'),
        'description' => t('Last update date'),
        'weight'      => 2,
      ),
      'path' => array(
        'label'       => t('Path to the page'),
        'description' => t('Path to the controlled page'),
        'weight'      => 3,
      ),
      'parser_value_html' => array(
        'label'       => t('Parser value: Original HTML'),
        'description' => t('Original HTML source of the page'),
        'weight'      => 4,
      ),
      'parser_value_plain_text' => array(
        'label'       => t('Parser value: Plain text'),
        'description' => t("A result of conversion of the page's HTML source to plain text"),
        'weight'      => 5,
      ),
      'parser_value_markdown' => array(
        'label'       => t('Parser value: Markdown'),
        'description' => t("A result of conversion of the page's HTML source to Markdown format"),
        'weight'      => 6,
      ),
      'view_link' => array(
        'label'       => t('View link'),
        'description' => t('View link'),
        'weight'      => 100,
      ),
      'edit_link' => array(
        'label'       => t('Edit link'),
        'description' => t('Edit link'),
        'weight'      => 101,
      ),
      'remove_link' => array(
        'label'       => t('Remove link'),
        'description' => t('Remove link'),
        'weight'      => 102,
      ),
    ),
  );
}

/**
 * Implements hook_entity_property_info_alter().
 */
function regression_regression_entry_entity_property_info_alter(&$info) {
  $properties = &$info['regression_entry']['properties'];
  
  $properties['revision'] = array(
    'label' => t('Revision'),
    'type' => 'text',
    'description' => t('ID of the entry revision.'),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer nodes',
    'schema field' => 'created',
  );
  
  $properties['uuid'] = array(
    'label' => t("UUID"),
    'type' => 'text',
    'description' => t('Unique indentifier of regression entry.'),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer nodes',
    'schema field' => 'created',
  );
  
  $properties['created'] = array(
    'label' => t("Date created"),
    'type' => 'date',
    'description' => t("The date the node was posted."),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer nodes',
    'schema field' => 'created',
  );
  
  $properties['updated'] = array(
    'label' => t("Date created"),
    'type' => 'date',
    'description' => t("The date the entry was created."),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer nodes',
    'schema field' => 'updated',
  );
  
  $properties['path'] = array(
    'label' => t("Page path"),
    'type' => 'date',
    'description' => t('Path to the controlled page'),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer nodes',
    'schema field' => 'path',
  );
  
  $properties['parser_value_html'] = array(
    'label' => t('Parser value: Original HTML'),
    'type' => 'text',
    'description' => t('Original HTML source of the page.'),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer nodes',
    'schema field' => 'updated',
  );
            
  $properties['parser_value_plain_text'] = array(
    'label' => t('Parser value: Plain text'),
    'type' => 'text',
    'description' => t("A result of conversion of the page's HTML source to plain text."),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer nodes',
    'schema field' => 'updated',
  );
  
  $properties['parser_value_markdown'] = array(
    'label' => t('Parser value: Markdown'),
    'type' => 'text',
    'description' => t("A result of conversion of the page's HTML source to Markdown format."),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer nodes',
    'schema field' => 'updated',
  );
  
  // Links:
  $properties['view_link'] = array(
    'label' => t('View link'),
    'type' => 'text',
    'description' => t('Provide a simple link to view the entity.'),
    'getter callback' => 'regression_field_regression_entry_link_view',
    'computed' => TRUE,
  );
  
  $properties['edit_link'] = array(
    'label' => t('Edit link'),
    'type' => 'text',
    'description' => t('Provide a simple link to edit the entity.'),
    'getter callback' => 'regression_field_regression_entry_link_edit',
    'computed' => TRUE,
  );
  
  $properties['delete_link'] = array(
    'label' => t('Delete link'),
    'type' => 'text',
    'description' => t('Provide a simple link to delete the entity.'),
    'getter callback' => 'regression_field_regression_entry_link_delete',
    'computed' => TRUE,
  );  
  
}

function regression_field_regression_entry_link_view() {
}

function regression_field_regression_entry_link_edit() {
}

function regression_field_regression_entry_link_delete() {
}

/**
 * Title of the /admin/structure/regression-entry page.
 */
function regression_regression_entry_info() {
  return 'Regression Entries';
}

/**
 * Implements the uri callback.
 */
function regression_regression_entry_uri($entity) {
  return array(
    'path' => 'regression/take-action/' . $entity -> uuid,
  );
}

function regression_regression_entry_page_title($entity) {
  return $entity -> pid;
}

/**
 * Page that displays the entity.
 */
function regression_regression_entry_page_view($entity, $view_mode = 'full') {
  // Our entity type, for convenience.
  $entity_type = 'regression_entry';
  
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

  return $entity -> content;
}
  
/**
 * Form of entity edit.
 */
function regression_regression_entry_form_edit($form, &$form_state, $entity) {
  return $form;
}

/**
 * Form of regression entry deletion.
 */
function regression_regression_entry_form_remove($form, &$form_state, $entity) {
  return $form;
}

function regression_regression_entry_edit_delete($form, &$form_state) {
}

function regression_regression_entry_edit_save($form, &$form_state) {
  return $form;
}
  
/**
 * Form of entity creation.
 */
function regression_regression_entry_form($form, &$form_state, $entity, $input) {
  return $form;
}

/**
 * Validation for the entity creation page.
 */
function regression_regression_entry_form_validate($form, &$form_state) {
  field_attach_form_validate('regression_entry', $entity, $form, $form_state);
}

/**
 * Submission handler for the entity creation page.
 */
function regression_regression_entry_form_submit($form, &$form_state) {
}

function regression_regression_entry_form_add($input) {
  return drupal_get_form('regression_regression_entry_form', $entity, $input);
}

/**
 * Provides a list of existing entities and the ability to add more. Tabs
 * provide field and display management.
 */
function regression_regression_entry_admin_page() {
  $content = array();
  $content[] = array(
    '#type' => 'item',
    '#markup' => t('Administration page for regression entries.')
  );
  
/*
  $content[] = array(
    '#type' => 'item',
    '#markup' => l(t('Add booking'), 'booking/add'),
  );
*/

  $content['table'] = regression_regression_entry_list_entities();

  return $content;
}

function regression_regression_entry_list_entities() {
  return array();
}

/**
 * Entity management pages paths.
 */
function regression_regression_entry_menu(&$items) {
  $items['admin/structure/regression-entries'] = array(
    'title'            => 'Regression Entries',
    'description'      => 'Manage regression entries',
    'page callback'    => 'regression_regression_entry_admin_page',
    'access arguments' => array('regression administration'),
  );
}

/**
 * Access handler for the entity.
 */
function regression_regression_entry_access($op, $task, $account = NULL, $entity_type = NULL) {
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
 * regression_regression_entry_load_multiple().
 *
 * This function gets its name from the menu system's wildcard
 * naming conventions. For example, /path/%wildcard would end
 * up calling wildcard_load(%wildcard value). In our case defining
 * the path: examples/entity_example/basic/%entity_example_basic in
 * hook_menu() tells Drupal to call entity_example_basic_load().
 *
 * @param $basic_id
 *   Integer specifying the basic entity id.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   A fully-loaded $basic object or FALSE if it cannot be loaded.
 *
 * @see entity_example_basic_load_multiple()
 * @see entity_example_menu()
 */
function regression_entry_load($basic_id = NULL, $reset = FALSE) {
  $basic_ids = (isset($basic_id) ? array($basic_id) : array());
  $basic = regression_regression_entry_load_multiple($basic_ids, array(), $reset);
  return $basic ? reset($basic) : FALSE;
}

/**
 * Loads a single regression entry.
 *
 * @param $pid
 *   Integer specifying the entity id.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   A fully-loaded $basic object or FALSE if it cannot be loaded.
 *
 * @see entity_example_basic_load_multiple()
 * @see entity_example_menu()
 */
/*
function regression_regression_entry_load($pid = NULL, $reset = FALSE) {
  $ids = (isset($pid) ? array($pid) : array());
  $res = regression_regression_entry_load_multiple($ids, array(), $reset);
  return $res ? reset($res) : FALSE;
}
*/

/**
 * Loads multiple basic entities.
 *
 * We only need to pass this request along to entity_load(), which
 * will in turn call the load() method of our entity controller class.
 *
 * @see entity_load()
 * @see EntityFieldQuery
 *
 * @param $pids
 *   An array of regression entry IDs.
 * @param $conditions
 *   (deprecated) An associative array of conditions on the {node}
 *   table, where the keys are the database fields and the values are the
 *   values those fields must have. Instead, it is preferable to use
 *   EntityFieldQuery to retrieve a list of entity IDs loadable by
 *   this function.
 * @param $reset
 *   Whether to reset the internal node_load cache.
 *
 * @return
 *   An array of node objects indexed by ids.
 */
function regression_regression_entry_load_multiple($pids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('regression_entry', $pids, $conditions, $reset);
}

/**
* Saves regression entry entity.
*/
function regression_regression_entry_save($entity) {
  entity_save('regression_entry', $entity);
  return $entity;
}

/**
* Deletes a single regression entries.
*/
function regression_regression_entry_delete($id) {
  entity_delete('regression_entry', entity_id('regression_entry' ,$id));
}

/**
* Deletes multiple regression entries.
*/
function regression_regression_entry_delete_multiple($ids) {
  entity_delete_multiple('regression_entry', $ids);
}
