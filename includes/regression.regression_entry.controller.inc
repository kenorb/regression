<?php

/**
 * @file
 * RegressionEntry entity.
 */

class RegressionEntry extends Entity {

  public $pid;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $key_hash;
  public $path;
  public $state;
  public $host;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $current_revision_id;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $current_working_revision_id;
  public $created;
  public $description;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $related_module_name;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $related_bug_tracker_url;
  public $assignee;
  public $priority;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $ignores_regex;

  /**
   * Constructor.
   */
  public function __construct($values = array()) {
    // Following construction mean that the regression_regression_entry_*
    // handlers will be used to manage this entity.
    parent::__construct($values, 'regression_entry');
  }

  /**
   * Returns related regression path configuration record.
   *
   * @return stdClass
   *   regression_path_configuration object.
   */
  public function get_path_configuration() {
    return (object) db_select('regression_path_configuration', 'RC')
      ->fields('RC', array('pid', 'settings', 'enabled', 'ignores_regex'))
      ->condition('path', $this->path)
      ->range(0, 1)
      ->execute()
      ->fetchAssoc();
  }

}

class RegressionEntryController extends EntityAPIControllerExportable  {

  /**
   * Creates new entity.
   */
  public function create(array $values = array()) {
    $values === NULL ?: $values = array();
    $values += array(
      'created' => REQUEST_TIME,
    );

    return parent::create($values);
  }

  /**
   * Builds(renders) entity content.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('regression_entry', $entity);
    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }

  /**
   * Loads entities from the specified IDs.
   */
  public function load($ids = array(), $conditions = array()) {
    return parent::load($ids, $conditions);
  }

  /**
   * Saves entity.
   */
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
