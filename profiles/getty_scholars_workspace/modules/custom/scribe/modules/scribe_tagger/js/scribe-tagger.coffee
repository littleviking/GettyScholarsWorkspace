# Scope in jQuery
$ = jQuery
Settings = Drupal.settings.scribe_tagger

# Add the annotator behavior
Drupal.behaviors.ScribeAnnotatorTags =
  attach: (context, settings) ->
    opts =
      minLength: 0
      source: @source
      multiple: true
      focus: @focus
      select: @select
      open: @open

    # Retrieve annotator and add the default tags plugin
    for name, annotator of Drupal.annotator
      if annotator.data('annotator')? and Drupal.settings.scribe_tagger?
        annotator.annotator('addPlugin', 'DrupalTags')
        annotator.data('annotator').plugins.DrupalTags.input.autocomplete(opts)

        # Update the Drupal store to add the annotation tag field
        # TODO: Remove the dirty hack relying on the key name to select the storage
        # plugin
        if name is 'image'
          annotator.data('annotator').plugins.DrupalStoreImage.fields.annotation.push('field_annotation_tags')
        else
          annotator.data('annotator').plugins.DrupalStore.fields.annotation.push('field_annotation_tags')

  source: (request, response) ->
    response($.ui.autocomplete.filter(Settings.term_autocomplete, Drupal.behaviors.ScribeAnnotatorTags.extractLast(request.term)))

  focus: () ->
    false

  select: (event, ui) ->
    terms = Drupal.behaviors.ScribeAnnotatorTags.split(@value)
    # remove the current input
    terms.pop()
    # add the selected item
    terms.push(ui.item.value)
    # add placeholder to get the comma-and-space at the end
    terms.push("")
    @value = terms.join(", ")
    return false

  split: (val) ->
    val.split( /,\s*/ )

  extractLast: (term) ->
    @split(term).pop()

  open: () ->
    $(@).autocomplete('widget').css('z-index', 20000)
    false
