<?php


function import_merge_node_form($form_state) {
  $form = array();
  $form['keys'] = array(
    '#type' => 'select',
    '#title' => t('Load key'), 
    '#description' => t('Load objects with this key'),
    '#options' => array(
      'nid' => 'Node Id',
      'title' => 'Title',
    ),
  );
  $form['fields'] = array(
    '#type' => 'select',
    '#title' => t('Fields'), 
    //'#description' => t('Match'),
    '#options' => array(
        'nid' => 'Node Id',
        'title' => 'Node Title',
        'body' => 'Body',
        'created' => 'Created',
        'published' => 'Published',
        'sticky' => 'Sticky',
        'promote' => 'Promoted',
      ),
  );
  return $form;
}

function import_merge_node_form_validate($form, &$form_state) {
  
}

function import_merge_node_form_submit($form, &$form_state) {
  
}
