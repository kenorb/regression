<?php

/**
 * @file
 * Drush commands for backup and migrate.
 */
 
/**
 * Implementation of hook_drush_command().
 */
function regression_drush_command() {
  $items = array();
  
  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function regression_drush_help($section) {
  /*
  switch ($section) {
    case 'drush:regression-add-set':
      return t("Example");
  }
  */
}

