<?php

class RegressionRevision extends Entity {
   
  public
    $pid,
    $path,
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
