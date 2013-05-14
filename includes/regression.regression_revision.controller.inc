<?php

/**
 * @file
 * RegressionRevision entity controller.
 */

class RegressionRevision extends Entity {

  public $pid;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $entry_id;
  public $pat;
  public $settings;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $path_args;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $revision_id;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $previous_revision_id;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $previous_revision_pid;
  public $created;
  public $updated;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $parser_value_html;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $parser_value_plain_text;

  // @ignore sniffer_namingconventions_validvariablename_lowercamelname
  public $parser_value_markdown;

  /**
   * Constructor.
   */
  public function __construct($values = array()) {
    // Following construction mean that the regression_regression_revision_*
    // handlers will be used to manage this entity.
    parent::__construct($values, 'regression_revision');
  }

  /**
   * Returns related regression entry record.
   *
   * @return RegressionEntry
   *   Related regression entry record.
   */
  public function get_entry() {
    return regression_entry_load($this->entry_id);
  }

  /**
   * Returns related regression path configuration record.
   *
   * @return stdClass
   *   Related regression path configuration object.
   */
  public function get_path_configuration() {
    return (object) db_select('regression_path_configuration', 'RC')
      ->fields('RC', array('settings', 'enabled', 'ignores_regex'))
      ->condition('path', $this->path)
      ->range(0, 1)
      ->execute()
      ->fetchAssoc();
  }

}

class RegressionRevisionController extends EntityAPIControllerExportable  {

  /**
   * Creates regression revision entity.
   */
  public function create(array $values = array()) {
    $values === NULL ?: $values = array();
    $values += array(
      'created' => REQUEST_TIME,
      'updated' => REQUEST_TIME,
    );

    return parent::create($values);
  }

  /**
   * Builds (renders) entity content.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('regression_revision', $entity);
    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }

  /**
   * Loads entities of the specified IDs.
   */
  public function load($ids = array(), $conditions = array()) {
    return parent::load($ids, $conditions);
  }

  /**
   * Saves the entity.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    return parent::save($entity, $transaction);
  }

}

class RegressionRevisionUIController extends EntityDefaultUIController {
}
