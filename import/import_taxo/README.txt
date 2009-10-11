

This module looks at category information in imported data and matches it to a
vocabulary. Only 3 levels are supported in a hierarchy at this stage.

This module does not do any node loading. 

This module won't check for duplicate tree branches. The first level of your taxo tree should be unique.

To create a taxonomy tree using a CSV file install taxonomy_csv.

See variable_get('import_taxo_vocabs', array()) to choose the vocabulary ID to import into.
If your vocab ID is 1 then run variable_set('import_taxo_vocabs', array(1))


