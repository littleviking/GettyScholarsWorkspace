# Overrides options necessary for storing image data. See drupal_store.js for parent
#
#

# Scope in jQuery
$ = jQuery
Scribe = Drupal.settings.scribe
Range = Annotator.Range

# This header will now be sent with every request.
class Annotator.Plugin.DrupalStoreImage extends Annotator.Plugin.DrupalStore

  constructor: () ->
    super

    # Setup the field types for image attachments
    @fields['image_attachment_info'] = ['shapes', 'src', 'shape_type']

    @options.annotationType = 'image'

  # Add entity data to an annotation before it's submitted.
  # This allows the annotation to be associated with the given
  # entity.
  scribeEntityData: (annotation) ->
    field = $(@element).parents('.field')
    field.data()

  setupAnnotation: (annotation, fireEvents=true) ->
    # Make sure that the annotation is be attached
    # to the correct text field, if it isn't then
    # return the annotation for chaining
    if annotation.attachment_id
      $field = $(@element).parents('.field')
      correct_entity = true
      entity_id = (Number) $field.data('entity_id')
      annotation_entity_id = (Number) annotation.entity_id
      if $field.data('entity_type') != annotation.entity_type then  correct_entity = false
      if $field.data('bundle') != annotation.bundle then correct_entity = false
      if $field.data('field_name') != annotation.field_name then correct_entity = false
      if entity_id != annotation_entity_id then correct_entity = false
      if not correct_entity then return annotation

    # Load up an image annotation directly to the image itself
    # img = $(@element).find('img')[0]

    # If the annotation has shapes add it to the image editor

    if annotation.shapes? and annotation.src?
      @plugins.ImageAnnotator.addImageAnnotation annotation

    # required by annotator but empty since we're working on a canvas
    annotation.highlights = []
    annotation.ranges     = []

    # Fire annotationCreated events so that plugins can react to them.
    # This is suppressed when annotations are being loaded
    if fireEvents
      this.publish('annotationCreated', [annotation])

    annotation


  # Checks the loadFromSearch option and if present loads annotations using
  # the Store#loadAnnotationsFromSearch method rather than Store#loadAnnotations.
  #
  # Returns nothing.
  _getAnnotations: =>
    annotations = []
    $.each Scribe.attachments, (index) ->
      if @.type is 'image'
        # Move all of the text attachment info into
        # the base object
        $.extend @, @.image_attachment_info
        delete @.image_attachment_info

        # Move all of the annotation info into the base object
        # This will also move the children key directly into
        # the base object as well
        $.extend @, @.annotation
        delete @.annotation

        annotations.push @

    @annotations = @annotations.concat(annotations)
    @annotator.loadAnnotations(annotations)
