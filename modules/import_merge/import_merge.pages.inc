<?php

include('import_merge.file.inc');


/**
 * @file
 * Page callbacks for initializing merge.
 */

/**
 * The first form. Choose a file and work flow options. 
 */
function import_merge_form($form_state) {
  $file = $form_state['post']['file'];
  $form = array();
  
  $info = import_merge_get_info();

  $file_options = array();
  foreach(import_merge_get_files() as $file_object) {
    $file_options[$file_object->filename] = $file_object->basename;
  }

  $form['files'] = array(
    '#type' => 'fieldset',
    '#title' => t('Files'),
    '#collapsible' => TRUE,
    '#description' => t('Your import path is: ') . import_merge_get_file_path(),
  );
  $form['files']['file'] = array(
    '#type' => 'radios',
    '#options' => $file_options,
  );
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Object Type'),
    '#description' => t('This is the type of object that gets loaded or created with the import data'),
    '#options' => !empty($info['types']) ? array_combine($info['types'], $info['types']) : array(),
  );
  $form['load'] = array(
    '#type' => 'select',
    '#title' => t('Load Key'),
    '#description' => t('Load and update objects matching this column.'),
    '#default_value' => variable_get('import_default_key', ''),
    '#options' => array('<none>') + $info['keys'],
  );
  $form['workflow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Work Flow'),
    '#collapsible' => TRUE,
  );
  $form['workflow']['create-new'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create new data'),
    '#description' => t('Create new objects, if they don\'t exist from the imported data'),
    '#default_value' => variable_get('import_default_create_new', 1),
  );
  $form['workflow']['overwrite'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overwrite existing objects'),
    '#description' => t('Overwrite existing objects loaded with this data'),
    '#default_value' => variable_get('import_default_skip_existing', 0),
  );
  $form['preview'] = array(
    '#type' => 'button',
    '#value' => t('Preview File'),
    '#submit' => 'import_merge_preview_rows',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
    '#attributes' => array('onclick' => '
      var form = document.getElementById(\'import-merge-form\');
      form.action = \'import/fields\';
      '),
  );
  if(!empty($file)) {
    $form['rows'] = array(
      '#type' => 'item',
      '#value' => import_merge_preview_rows($file, 20),
    );
  }
  return $form;
}

function import_merge_preview_rows($file, $limit) {
  $header = import_merge_file_to_array($file, 'header');
  $rows = import_merge_file_to_array($file, 'list', $limit);
  return theme('table', $header, $rows, array('style' => 'font-size: 0.8em;'));
}

/**
 * The second form. This matches rows with object info 
 */
function import_merge_form_fields($form_state) {
  
  $form = array();
  if(empty($form_state['post']['file'])){
    return $form;
  }
  foreach(array('file', 'load', 'create-new', 'overwrite', 'type', 'new-published') as $hidden) {
    $form[$hidden] = array('#type' => 'hidden', '#value' => $form_state['post'][$hidden]);
  }

  $info = import_merge_get_info($form_state['post']['type']);

  foreach(import_merge_file_to_array($form_state['post']['file'], 'header') as $key => $col) {
    if(!empty($col)) {
      $do_it = TRUE;
      $form['field-'.$key] = array(
        '#title' => $col,
        '#type' => 'select',
        '#options' => array('Ignore') + $info['fields'],
      );
      $form['field-'.$key]['#title'] = $col;
    }
  }
  if($do_it) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Do it'),
    );
  }
  return $form;
}

/**
 * Implement hook_submit()
 */
function import_merge_form_fields_submit($form, &$form_state) {
  
  //get user join selection and make row data array
  $fields = _import_merge_get_form_field_keys_value($form_state['values']);
  $file_data = import_merge_file_to_array($form_state['values']['file'], 'skip-header', variable_get('import_row_limit', 0), $fields);
  $rows = array();
  foreach($file_data as $data){
    $rows[] = array_combine($fields, $data);
  }

  //get info about contributes module form values
  $merge_data = array('form_values' => $form_state['values']);
  
  //create merge object
  $merge_settings = array(
    'type' => $form_state['values']['type'],
    'load' => $form_state['values']['load'],
    'overwrite' => $form_state['values']['overwrite'],
    'create' => $form_state['values']['create-new'],
    'rows' => $rows,
    'meta' => $merge_data,
  );
  $merge = import_merge_merge_object($merge_settings);
  
  //execute
  import_merge_execute($merge);
  drupal_set_message('Imported!', 'status', FALSE);
}

/**
 * Get the user values for each info key  
 */
function _import_merge_get_form_field_keys_value($values) {
  $keys = array();
  for($i = 0; $i < count(import_merge_file_to_array($values['file'], 'header')); $i++) {
    $field = $values['field-'. $i];
    if(!empty($field)) {
      $keys[$i] = $field;
    }
  }
  return $keys;
}

