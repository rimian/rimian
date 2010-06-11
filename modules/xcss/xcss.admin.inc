<?php

/**
 * @file
 * Provides the xCSS administration settings.
 */

/**
 * The xCSS administration form.
 */
function xcss_settings() {
  $form['xcss_debugmode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug Mode'),
    '#description' => t('When checked, will print out all generated code.'),
    '#default_value' => variable_get('xcss_debugmode', FALSE),
  );
  $form['xcss_minify_output'] = array(
    '#type' => 'checkbox',
    '#title' => t('Minify Output'),
    '#description' => t('When checked, will remove all white space and newlines in the generated CSS files.'),
    '#default_value' => variable_get('xcss_minify_output', FALSE),
  );
  $form['xcss_master_file_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to Master xCSS file'),
    '#description' => t('Create a file master.xcss in this directory.'),
    '#default_value' => xcss_path_to_file('xcss'),
  );

  // Clear the xCSS cache when submitted.
  $form['#submit'][] = 'xcss_flush_caches';

  return system_settings_form($form);
}
