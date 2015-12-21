# Scribe
Scribe is a system for annotating documents inside of Drupal.  Utilizing various Javascript library, Scribe is able to store annotations on various types of content.

## Concepts

### Annotated Fields
Using scribe, particular fields are configured to be annotated.  This is done via user configuration.

### Scribe Base
The base scribe module does the following things:

* Creates configuration system allowing fields to be configured as annotatable.
* Stores basic annotation information such as creation date, the field instance the annotation is related to, and annotation text.
* Allows for the creation of new attachers so that annotations can be attached to new types of content.

### Annotator
Scribe is built on the [Annotator Javascript](http://okfnlabs.org/annotator/) library.  While it isn't strictly necessary to build additional annotation features on this, it will allow you to leverage all of the power of Scribe that has been built to work using the annotator library.  This includes easy integration with permissions, conversation threading and more.

### Attacher
An attacher is a collection of javascript, css and some code responsible for storing metadata about an annotation.  In particular, it handles the following things

* Associating Javascript and CSS for any annotation libraries to particular fields.
* Setting up necessary storage for annotation metadata.
* Describing data properties in annotation metadata so they can be accessed through web services.
* Interfacing javascript with web services to load and store annotations.


## Implementing an Attacher
To implement a new attacher the following steps should be followed:

#### Implement hook_schema()

This will describe the database table that your module needs to store annotation metadata.  For instance, for text this will store the text ranges of an annotation, or for an image, this will store the location on the image where an annotation exists.  It can contain any fields necessary to store the annotation information.  The only requirement is that there **must be a field called attachment_id with exactly the definition below:**

```php
'attachment_id' => array(
  'description' => 'The ID of the attachment.',
  'type' => 'int',
  'unsigned' => TRUE,
  'not null' => TRUE,
),
```


Any other data can be stored in the table, here's the schema definition for text storage as an example.

```php
/**
 * Implements hook_schema().
 */
function scribe_text_attacher_schema() {
  $schema['scribe_text_metadata'] = array(
    'description' => 'Stores metadata for text annotations.',
    'fields' => array(
      'attachment_id' => array(
        'description' => 'The ID of the attachment.',
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
      'annotator_schema_version' => array(
        'description' => 'Schema Version of Annotator being used, by default v1.0',
        'type' => 'varchar',
        'length' => 12,
        'default' => 'v1.0',
        'not null' => TRUE,
      ),
      'quote' => array(
        'description' => 'The text that is being annotated.',
        'type' => 'text',
        'size' => 'big',
        'not null' => FALSE,
      ),
      'uri' => array(
        'description' => 'URI of annotated document.',
        'type' => 'varchar',
        'length' => 2048,
        'not null' => FALSE,
        'sortable' => TRUE
      ),
      'ranges' => array(
        'description' => 'Ranges that are covered by the attachment.',
        'type' => 'blob',
        'not null' => TRUE,
        'size' => 'big',
        'serialize' => TRUE,
      ),
    ),
  );
  return $schema;
}

```

#### Implement hook_library()
hook_library() is used to describe Javascript and CSS libraries that can be added to Drupal.  This will be used to describe the necessary Javascript and CSS necessary for your particular annotation library to function.  These libraries will automatically be loaded when annotatable content is loaded onto a page.  An example of hook_library (used in text annotations) is below:

```php
function scribe_text_attacher_library() {
  $module_path = drupal_get_path('module', 'scribe_text_attacher');

  $libraries['annotator'] = array(
    'title' => 'Annotator',
    'website' => 'http://okfnlabs.org/annotator/',
    'version' => '1.2.6',
    'js' => array(
      $module_path . '/annotator/annotator-full.min.js' => array('scope' => 'footer'),
      $module_path . '/js/drupal_store.js' => array('scope' => 'footer'),
      $module_path . '/js/scribe_annotator.js' => array('scope' => 'footer'),
    ),
    'css' => array(
      $module_path . '/annotator/annotator.min.css' => array(
        'type' => 'file',
        'media' => 'screen',
      ),
    ),
  );

  return $libraries;
}
```

#### Implement hook\_scribe\_attacher_info()

This hook describes to scribe what type of fields can be annotated using this attacher, a library (defined by hook_library) that should be loaded, and the database table that contains metadata for storing the annotation.  The hook should return an array keyed with the name of the attacher which contains information describing the attacher.

```php
function scribe_text_attacher_scribe_attacher_info() {
  $attachers['text'] = array(
    'label' => 'Scribe Text Attacher',
    'description' => 'This attacher allows annotations to be attached to text fields.',
    'metadata table' => 'scribe_text_metadata',
    'field types' => array(
      'text',
      'text_long',
      'text_with_summary',
    ),
    'library' => array(
      'module' => 'scribe_text_attacher',
      'name' => 'annotator',
    ),
  );

  return $attachers;
}
```

The following array keys are required:

* metadata table - The name of the table which stores all of the metadata for this type of annotation.
* field types - An array of field types to which the annotation can occur.
* library - An array containing two keys, module which is the name of the module to load the library from, and name which is the name of the library.  This will be used directly to load the necessary javascript and css using [drupal\_add\_library](http://api.drupal.org/api/drupal/includes%21common.inc/function/drupal_add_library/7).

#### Implement hook\_scribe\_metadata_properties()

This hook describes the data properties of the fields in the *metadata table* used for storing info for this type of annotation.  This hook follows the same styles as [hook\_entity\_property_info](http://drupalcontrib.org/api/drupal/contributions!entity!entity.api.php/function/hook_entity_property_info/7).  In particular, for the attacher to work, the *schema field* property must be set, otherwise the entity will not be queryable by the RESTful Web Services Module.  An example of this implementation is below:

```php
/**
 * Implements hook_scribe_metadata_properties().
 */
function scribe_text_attacher_scribe_metadata_properties() {
  $info = array();
  $properties = &$info['text'];

  $properties['id'] = array(
    'label' => t('Attachment ID'),
    'type' => 'integer',
    'description' => t("The unique content ID."),
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'attachment_id',
  );
  $properties['text'] = array(
    'label' => t('Text'),
    'type' => 'text',
    'description' => t('The text of the annotation.'),
    'setter callback' => 'entity_property_verbatim_set',
  );
  $properties['annotator_schema_version'] = array(
    'label' => t('Schema Version'),
    'type' => 'text',
    'description' => t('Schema Version of Annotator being used, by default v1.0'),
    'setter callback' => 'entity_property_verbatim_set',
    'schema' => 'annotator_schema_version',
  );
  $properties['quote'] = array(
    'label' => t('Quoted Text'),
    'type' => 'text',
    'description' => t('The text that is being annotated.'),
    'setter callback' => 'entity_property_verbatim_set',
  );
  $properties['uri'] = array(
    'label' => t('Annotation URI'),
    'type' => 'uri',
    'description' => t('URI of annotated document.'),
    'setter callback' => 'entity_property_verbatim_set',
  );
  $properties['ranges'] = array(
    'label' => t('Annotation Ranges'),
    'type' => 'list<struct>',
    'description' => 'Ranges that are covered by the attachment.',
    'setter callback' => 'entity_property_verbatim_set',
    'property info' => array(
      'end' => array(
        'label' => t('End'),
        'type' => 'text',
        'description' => t('An xpath path to the end element of the annotation.'),
      ),
      'endOffset' => array(
        'label' => t('End Offset'),
        'type' => 'integer',
        'description' => t('The numeric position inside of the element of the end of the annotation.'),
      ),
      'start' => array(
        'label' => t('Start'),
        'type' => 'text',
        'description' => t('An xpath path to the beginning element of the annotation.'),
      ),
      'startOffset' => array(
        'label' => t('Start Offset'),
        'type' => 'integer',
        'description' => t('The numeric position inside of the element of the start of the annotation.'),
      ),
    ),
  );
  $properties['uid'] = array(
    'label' => t('User'),
    'type' => 'user',
    'description' => t('The user that created the attachment'),
    'setter callback' => 'entity_property_verbatim_set',
  );

  return $info;
}
```

#### Adding/Querying Annotations Through RESTful Web Services
Once the hooks have been created for use with scribe, it is then time to integrate any annotation related javascript with [RESTful Web Services](http://dgo.to/restws).
RESTful Web Services works by automatically creating API endpoints for Drupal entities.

It's highly suggested to build off of the storage system that have been included in the Annotator library and in the Scribe Text Attacher module as this will greatly smooth the process integrating with RESTful Web Services.  To see an example of how this can be done you can take a look at drupal_image_store.coffee in the Scribe Image Attacher module.

###### CSRF Token

When working with RESTful Web Services, each request must have a token to prevent Cross Site Request Forgeries attacks.  The scribe module places this in a javascript variable which can be found at:

```
Drupal.settings.scribe.csrf_token
```

When making request this token must be supplied as an HTTP header in the following format:

```
X-CSRF-Token: 5rbhbwagjrspCfSxgLXd2Vnaw1umQXvivsrLAqzelG4
```

###### API Endpoints


The endpoint for annotations can be found at:

```
GET /scribe_attachment.json
```

Going to this URL will return a list of scribe_attachment objects.  While it is possible to query a full list of attachments, they are loaded into the DOM at the beginning of each page load into the DOM.  The can be found in Drupal.settings.scribe.attachments.  These will be loaded into the page if there are any annotated entities on the page.

To get a single object the following URL is used:

```
GET /scribe_attachment/[ID].json
```

Where [ID] is the primary key identifier of the annotation.  Similarly, the same API endpoint is used for creation and updates.

```
Create:  POST /scribe_attachment.json
Update:  PUT  /scribe_attachment/[ID].json
```


###### Data Structure
The following is the data structure used for annotations.  This directly mirros the data structure that would be found in the underlying PHP code.  The following fields will be added automatically:

* created
* updated
* uid

It's the modules concern to ensure that the following fields are set:

* attachment_id (If there is one from an already existing annotation)
* field_name
* entity_type
* bundle
* entity_id
* type - This should correspond to the type of the attachment (and the one declared in hook\_scribe\_attacher_info).
* TYPENAME\_attacher\_info -  This is where all necessary information for storing where the annotation is will exist.  TYPENAME will be the type declared in hook\_scribe\_attacher_info.  There should only be one of these on each given entity.


```
{
    attachment_id: "10",
    type: "text",
    field_name: "body",
    entity_type: 'node',
    bundle: "test",
    entity_id: "1",
    created: "1366040176",
    updated: "1366040176",
    uid: {
        uri: "http://192.168.33.20/user/1",
        id: "1",
        resource: "user"
    },
    text_attachment_info: {
        id: "10",
        text: null,
        annotator_schema_version: "v1.0",
        quote: "技术的充分利用与游戏的而著称",
        uri: null,
        ranges: [
            {
                end: "/div[1]/p[1]",
                endOffset: 167,
                start: "/div[1]/p[1]",
                startOffset: 66
            }
        ]
    }
},
```

When POSTing a new annotation or PUTing an updated annotation, if this structure is not matched RESTful Web Services will produce an error (likely an error 406 for bad data).  It's also possible there is an error in hook\_scribe\_metadata_properties() which must correctly reflect the data being submitted.

Again, it's suggested to extend the DrupalStore class found in drupal_store.coffee as this will help take care of most of these issues.

###### Retrieving annotated entities

A list of annotated entities on every page is stored in the Javascript variable:

```
Drupal.settings.scribe.attachments
```

This list can be used to query for the necessary list of annotations for a given page in the following way:

```
GET /scribe_attachment.json?attachment_id[]=ID1&attachment_id[]=ID2&attachment_id[]=ID3&type=TYPENAME
```
where ID1, ID2 and ID3 are attachment IDs (which will be present in the fields list).
