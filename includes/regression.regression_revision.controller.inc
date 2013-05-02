<?php

class RegressionRevision extends Entity {
   
  public
    $pid,
    $entry_id,
    $path,
    $settings,
    $path_args,
    $revision_id,
    $previous_revision_id,
    $previous_revision_pid,
    $created,
    $updated,
    $parser_value_html,
    $parser_value_plain_text,
    $parser_value_markdown;

  public function __construct($values = array()) {
    // Following construction mean that the regression_regression_revision_* handlers will be used to manage this entity
    parent::__construct($values, 'regression_revision'); 
  }
  
  /**
   * Returns related regression entry record.
   * @return RegressionEntry
   */
  public function get_entry() {
    return regression_entry_load($this->entry_id);
  }
  
  /**
   * Returns related regression path configuration record.
   * @return stdClass
   */
  public function get_path_configuration() {
    return (object)db_select('regression_path_configuration', 'RC')
      ->fields('RC', array('settings', 'enabled', 'ignores_regex'))
      ->condition('path', $this->path)
      ->range(0, 1)
      ->execute()
      ->fetchAssoc();    
  }
  
}

class RegressionRevisionController extends EntityAPIControllerExportable  {
  
  public function create(array $values = array()) {
    $values === NULL ?: $values = array();
    $values += array(
      'created' => REQUEST_TIME,
      'updated' => REQUEST_TIME,
    );
    
    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('regression_revision', $entity);
    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
 
  public function load($ids = array(), $conditions = array()) {
    return parent::load($ids, $conditions);
  }

  public function save($entity, DatabaseTransaction $transaction = NULL) {
    return parent::save($entity, $transaction);
  }
  
}

class RegressionRevisionUIController extends EntityDefaultUIController {
}
