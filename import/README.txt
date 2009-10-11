

A basic API for node importing from a CSV. Other file formats will perhaps
be supported later.

This module doesn't try to do too much. It provides a basic form interface to the end user and
another application interface to extra modules that wish to extend its functionality. It really only
matches a few fields to CSV columns and delegates the loading and editing of nodes to sub modules.

See the sample data file which is an export from osCommerce.

Check all the set variables like: variable_get('import_default_type', 'page'). You'll 
need to set these manually as this module is an early release and only core functionality 
is built in.

There are two hooks for other modules to load nodes and match data rows against nodes.

hook_importapi accepts a node and an array of data to match against. 

hook_node_load attempts to load a node based on a key/value pair in each data row.
Only one module should be responsible for loading a node as selected be the user.

To add keys to the import, alter 'import_form' by setting $form['key']['#options']. To add
node types to the import set $form['type']['#options']. To add columns to the import, alter
form 'import_form_file_fields' by setting $form['fields']['#options'].

See import_product.module for examples.

Also see SAMPLE.txt

This module does not support file handling. 
Use IMCE for this. See variable_get('import_csv_path', 'sites/default/files/csv');






