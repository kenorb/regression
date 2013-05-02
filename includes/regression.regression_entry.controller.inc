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
    $created,
    $description,
    $related_module_name,
    $related_bug_tracker_url,
    $assignee,
    $priority,
    $ignores_regex;

  public function __construct($values = array()) {
    // Following construction mean that the regression_regression_entry_* handlers will be used to manage this entity
    parent::__construct($values, 'regression_entry'); 
  }
  
  /**
   * Returns related regression path configuration record.
   * @return stdClass
   */
  public function get_path_configuration() {
    return (object)db_select('regression_path_configuration', 'RC')
      ->fields('RC', array('pid', 'settings', 'enabled', 'ignores_regex'))
      ->condition('path', $this->path)
      ->range(0, 1)
      ->execute()
      ->fetchAssoc();    
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
