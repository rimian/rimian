<?php

/**
 * @param string $file. The full path of the file from web root. 
 * @param string $op. Operation performed for this request: header, skip-header, list  
 * @param int $limit. How many rows. Zero for all.
 * @param array $filter. If an array of keys are supplied the other columns are discarded.
 * @return array $rows. A nested array of rows and colums.
 */
function import_merge_file_to_array($file, $op = 'list', $limit = 0, $mask = array()) {
  set_time_limit(0);
  $rows = array();
  if(file_exists($file) && !is_dir($file)){
    drupal_set_message('Opened file: '. $file, 'status', FALSE);
    $handle = fopen($file, "r");
    while (($data = fgetcsv($handle)) !== FALSE) {
      
      if(!empty($mask)) {
        $data = array_intersect_key($data, $mask);
      }
      
      array_walk($data, 'trim');
      
      if($op == 'header'){
        $rows = $data;
        break;
      }
      elseif($op == 'skip-header') {
        $op = 'list';
      }
      else{
        if(!empty($data)){
          $rows[] = $data;
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

/**
 * Get files for merge
 * @param string $mask [optional]. Filter files with this suffix
 * @return array $files 
 */
function import_merge_get_files($mask = 'csv') {
  $files = array();
  foreach(file_scan_directory(import_merge_ui_get_file_path(), $mask) as $file){
    $files[] = $file;
  }
  return $files; 
}

/**
 * Get path for a file.
 * @param string $basename [optional] Add the base name if required
 * @return string $file 
 */
function import_merge_get_file_path($basename = FALSE) {
  $path = variable_get('import_csv_path', 'sites/default/files/csv');
  $file = !$basename ? $path : $path . '/'. $basename;
  if(!is_dir($path) || ($basename && !file_exists($file))) {
    return false;
  }
  return $file;
}
