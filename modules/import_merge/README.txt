

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

hook_merge($type, &$object, $data, $meta) 

*type
The merge type can be something like a node, taxonomy term, user or anything

*object
The object to be merged (a type)

*data
An array to merge with the object

*meta 
Information about the merge, such as user input

================================

Callback arguments

Your callbacks should expect the arguments supplied by the import_merge engine

*get_callback
array(key => value), meta

*set_callback
$profile->create_callback, $row, $profile->meta

*create_callback
$profile->type, $object, $row, $profile->meta

================================

Check all the set variables like: variable_get('import_default_type', 'page'). You'll 
need to set these manually as this module is an early release and only core functionality 
is built in.

See SAMPLE.csv

This module does not support file handling. 
Use IMCE or something else for this. 
See variable_get('import_csv_path', 'sites/default/files/csv');

Line break issues
================================
You may have trouble with MS Windows linebreaks. The best solution is not to use Microsoft 
at all but for most people this will be impractical. 

If you're using Open Office you'll probably be OK. 

If you can't use Open Office, this simple perl command will replace the ^M chgaracters 
with proper line breaks:

perl -pi -e "s/\x0D/\n/g" myfile.csv 

TODOs
=============================

Validation
-----------------------------


Transaction Support
-----------------------------
If validation fails don't import.


