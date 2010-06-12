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
    '#title' => t('Path to xCSS files'),
    '#description' => t('xCSS will scan this directory recursively and save the xCSS files in your files/xcss directory.'),
    '#default_value' => xcss_fileapi('xcss', 'dir'),
  );

  // Clear the xCSS cache when submitted.
  $form['#submit'][] = 'xcss_flush_caches';

  return system_settings_form($form);
}
