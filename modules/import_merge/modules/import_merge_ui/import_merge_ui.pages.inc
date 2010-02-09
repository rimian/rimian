<?php

include('import_merge_ui.file.inc');

/**
 * @file
 * Page callbacks for initializing merge.
 */

/**
 * The first form. Choose a file and work flow options. 
 */
function import_merge_ui_form($form_state) {
  
  $form = array();

  //files
  $file_options = array();
  foreach(import_merge_ui_get_files() as $file_object) {
    $file_options[$file_object->filename] = $file_object->basename;
  }
  if(empty($file_options)) {
    drupal_set_message('No files available to merge. Have you set the file directory and uploaded files?');
  }

  //profiles
  $info = import_merge_ui_get_info();
  //default settings
  $profile = $form_state['profile'];
  
  $form['files'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available Files'),
    '#collapsible' => TRUE,
    '#description' => t('Your import path is: ') . import_merge_ui_get_file_path(),
  );
  $form['files']['file'] = array(
    '#type' => 'radios',
    '#options' => $file_options,
  );
  $form['profiles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Merge profiles'),
    '#collapsible' => TRUE,
  );
  $form['profiles']['profile'] = array(
    '#type' => 'select',
    '#title' => t('Merge Profile'),
    '#description' => t('Choose the merge profile to run.'),
    '#options' => array_combine(array_keys($info), array_keys($info)),
  );
  $form['workflow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Work Flow'),
    '#collapsible' => TRUE,
  );
  $form['workflow']['create'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create new data'),
    '#description' => t('Create new objects, if they don\'t exist from the imported data'),
    '#default_value' => $profile->create,
  );
  $form['workflow']['overwrite'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overwrite existing objects'),
    '#description' => t('Overwrite existing objects loaded with this data'),
    '#default_value' => $profile->overwrite,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );
  return $form;
}

function import_merge_ui_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  if(empty($values['file'])){
    form_set_error('file', 'You must select a file to merge.');
  }
}

/**
 * Update profile then save to form state 
 * @param object $form
 * @param object $form_state
 */
function import_merge_ui_form_submit(&$form, &$form_state) {

  $values = $form_state['values'];
  $profile = $form_state['profile'];
  $info = import_merge_ui_get_info($values['profile']);

  $profile->name = $values['profile'];
  $profile->type = $info['type'];
  $profile->overwrite = $values['overwrite'];
  $profile->create = $values['create'];
  $profile->file = $values['file'];
  
  $form_state['profile'] = $profile;
}

/**
 * The second form. This matches rows with object info 
 */
function import_merge_ui_form_fields($form_state) {
  
  $form = array();
  $profile = $form_state['profile'];

  $info = import_merge_ui_get_info($profile->name);
  
  $form['help'] = array(
    '#type' => 'item',
    '#value' => t('Match the columns loaded from the file with the attributes of the object.'), 
  );
  
  if($profile->overwrite){
    $form['load'] = array(
      '#type' => 'select',
      '#title' => t('Load Key'),
      '#description' => t('Load and overwrite objects that match this column.'),
      //'#default_value' => $profile,
      '#options' => array('<none>') +   $info['load_keys'],
    );  
  }
  
  foreach(import_merge_ui_file_to_array($profile->file, 'header') as $key => $col) {
    if(!empty($col)) {
      $form['field-'.$key] = array(
        '#title' => $col,
        '#type' => 'select',
        '#options' => array('<Ignore>') + $info['merge_fields'],
      );
      $form['field-'.$key]['#title'] = $col;
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Merge'),
  );
  return $form;
}

/**
 * Implement hook_submit()
 */
function import_merge_ui_form_fields_submit($form, &$form_state) {
  
  $profile = $form_state['profile'];

  //get user join selection and make row data array
  $mask = _import_merge_ui_get_form_field_keys_value($profile, $form_state['values']);
  $file_data = import_merge_ui_file_to_array($profile->file, 'skip-header', variable_get('import_merge_row_limit', 0), $mask);
  
  //bind to profile
  foreach($file_data as $data){
    $profile->rows[] = array_combine($mask, $data);
  }
  
  //execute
  import_merge_execute($profile);
  drupal_set_message('Imported!', 'status', FALSE);
}

/**
 * Filter the form for joins between object and file
 * @param array $profile.  
 * @param array $values. Form values from form_state 
 * @return array $keys
 */
function _import_merge_ui_get_form_field_keys_value($profile, $values) {
  $keys = array();
  for($i = 0; $i < count(import_merge_ui_file_to_array($profile->file, 'header')); $i++) {
    $field = $values['field-'. $i];
    if(!empty($field)) {
      $keys[$i] = $field;
    }
  }
  return $keys;
}






