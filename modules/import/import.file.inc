<?php

/**
 * @param string $file. The full path of the file from web root. 
 * @param string $op. Operation performed for this request: header, skip-header, list  
 * @param int $limit. How many rows. Zero for all.
 * @param array $filter. If an array of keys are supplied the other columns are discarded.
 * @return array $rows. A nested array of rows and colums.
 */
function import_file_to_array($file, $op = 'list', $limit = 0, $filter = array()) {
  set_time_limit(0);
  $rows = array();
  if(file_exists($file) && !is_dir($file)){
    drupal_set_message('Opened file: '. $file, 'status', FALSE);
    $handle = fopen($file, "r");
    while (($data = fgetcsv($handle)) !== FALSE) {
      if(!empty($filter)) {
        $data = array_intersect_key($data, $filter);
      }
      if($op == 'header'){
        $rows = _import_tidy_data($data);
        break;
      }
      elseif($op == 'skip-header') {
        $op = 'list';
      }
      else{
        if(!empty($data)){
          $rows[] = _import_tidy_data($data);
          if($limit > 0 && count($rows) == $limit) {
            break;
          }
        }
      }
    }
    fclose($handle);
  }
  else{
    drupal_set_message('File does not exist.', 'error');
    return FALSE;
  }
  return $rows;
}

function import_get_files($mask = 'csv') {
  foreach(file_scan_directory(import_get_file_path(), $mask) as $file){
    $files[] = $file;
  }
  return $files; 
}

function import_get_file_path($basename = FALSE) {
  $path = variable_get('import_csv_path', 'sites/default/files/csv');
  $file = !$basename ? $path : $path . '/'. $basename;
  if(!is_dir($path) || ($basename && !file_exists($file))) {
    return false;
  }
  return $file;
}