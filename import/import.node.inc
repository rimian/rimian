<?php

function import_importapi(&$node, $data) {
  $fields = array_keys(_import_get_fields());
  foreach($fields as $field) {
    if(!empty($data[$field])) {
      $node->$field = $data[$field];
    }
  }
}

/**
 * After the node has been loaded, pass it to all the modules for 
 * altering against the data from the Import file 
 */
function import_invoke_importapi(&$node, $data) {
  $hook = 'importapi';
  foreach (module_implements($hook) as $name) {
    $function = $name .'_'. $hook;
    $function(&$node, $data);
  }
}

/**
 * Give modules opportunity to load a node based on a key and value.
 * Only one module can do this of course but keys are unique anyway
 */
function import_invoke_node_load($key, $value) {
  $hook = 'import_node_load';
  foreach (module_implements($hook) as $name) {
    $function = $name .'_'. $hook;
    $node = $function($key, $value);
    if(is_object($node)) {
      return $node;
    }
  }
  return FALSE;
}

function import_create_node() {
  global $user;
  $language = language_default();
  $node = new stdClass;
  $node->language = $language->language;
  $node->uid = $user->uid;
  $node->name = $user->name;
  return $node;
}

function _import_get_fields() {
  return array('title' => 'Title', 'body' => 'Body');
}

