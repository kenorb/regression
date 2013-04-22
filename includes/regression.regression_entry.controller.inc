<?php

class RegressionEntry extends Entity {
   
  public
    $pid,
    $key_hash,
    $path,
    $state,
    $host,
    $current_revision_id,
    $current_working_revision_id,
    $created;

  public function __construct($values = array()) {
    // Following construction mean that the regression_regression_entry_* handlers will be used to manage this entity
    parent::__construct($values, 'regression_entry'); 
  }
  
}

class RegressionEntryController extends EntityAPIControllerExportable  {
  
  public function create(array $values = array()) {
    $values === NULL ?: $values = array();
    $values += array(
      'created' => REQUEST_TIME,
    );
    
    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('regression_entry', $entity);
    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
 
  public function load($ids = array(), $conditions = array()) {
    return parent::load($ids, $conditions);
  }

  public function save($entity, DatabaseTransaction $transaction = NULL) {
    return parent::save($entity, $transaction);
  }
  
}

class RegressionEntryUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage regression entries.';
    return $items;
  }

}
