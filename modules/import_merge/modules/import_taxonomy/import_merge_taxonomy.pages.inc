<?php


function import_merge_taxonomy_form($form_state) {
  $form = array();
  $form['keys'] = array(
    '#type' => 'select',
    '#title' => t('Load key'), 
    '#description' => t('Load objects with this key'),
    '#options' => array(
      'tid' => 'Term Id',
      'name' => 'Term Name',
    ),
  );
  $form['fields'] = array(
    '#type' => 'select',
    '#title' => t('Fields'), 
    '#options' => array(
      'tid' => 'Term Id',
      'name' => 'Term Name',
    ),
  );
  return $form;
}

