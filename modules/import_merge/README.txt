

A basic API for importing various objects from a CSV. Other file formats will perhaps
be supported later. But probably not. This module assumes you can get your CSV into a manageable
format with Open Office or something. 

This module doesn't try to do too much. It provides a basic form interface to the end user and
another application interface to extra modules that wish to extend its functionality. It really only
matches a few fields to CSV columns and delegates the loading and editing of objects to sub modules.

The merge object
==============================
*type
The type object your module imports (a node, user etc)

*load
The field that's used to load an object you wish to merge

*overwrite
True or False. Overwrite existing content in your site

*create
True or False. Create new content if it doesn't load

*rows
An array of rows to merge. Each row is an array with field names as keys and values from the file.
array('field' => 'some value')

*meta
Meta information about the merge. This can contain form values etc.

See: import_merge_merge_object()

Hooks:
==============================

hook_im()
------------------------------
This hook tells import about your module. It should return an array with the keys:

* type
The type object your module imports (a node, user etc)

* keys
If you want to load a module against a certain attribute or key for updating or ignoring, then 
return the keys here

*fields
The use fields to modify your object with the data in the columns. 

See import_merge_node.module

hook_im_init($object_type, $data, $op)
-----------------------------
$object_type matches against 'type' provided by your info hook
$data is the row from your CSV
$op is the operation being performed. Values are 'create' and 'load'. See import_merge_node.module

hook_im_merge($object_type, &$object, $data)
-----------------------------
Merge the row with the object. The object is passed by reference and modified by they array $data
This function should not return anything

hook_im_save($object_type, &$object)
-----------------------------
Save the object. 
This function should not return anything


================================

Check all the set variables like: variable_get('import_default_type', 'page'). You'll 
need to set these manually as this module is an early release and only core functionality 
is built in.

See SAMPLE.csv

This module does not support file handling. 
Use IMCE or something else for this. See variable_get('import_csv_path', 'sites/default/files/csv');


TODOs
=============================

Validation
-----------------------------


Transaction Support
-----------------------------
If validation fails don't import.


