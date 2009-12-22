

A basic API for node importing from a CSV. Other file formats will perhaps
be supported later. But probably not.

This module doesn't try to do too much. It provides a basic form interface to the end user and
another application interface to extra modules that wish to extend its functionality. It really only
matches a few fields to CSV columns and delegates the loading and editing of objects to sub modules.

Check all the set variables like: variable_get('import_default_type', 'page'). You'll 
need to set these manually as this module is an early release and only core functionality 
is built in.

See SAMPLE.txt

This module does not support file handling. 
Use IMCE or something else for this. See variable_get('import_csv_path', 'sites/default/files/csv');


TODOs
=============================

hook workflow
-----------------------------

Abstract forms 
-----------------------------
Currently, the controller that merges CSV with objects is the hook_submit()
This means other modules can't execute this code without pretending to be a form.


Validation
-----------------------------


Transaction Support
-----------------------------
If validation fails don't import.


