# A storage plugin for annotator designed to be used with scribe.  This
# is designed to overcome a number of limitations, the largest being is the ability
# to annotate multiple pieces of content that might appear on the same page.
#
# Public: The Store plugin can be used to persist annotations to a database
# running on your server. It has a simple customisable interface that can be
# implemented with any web framework. It works by listening to events published
# by the Annotator and making appropriate requests to the server depending on
# the event.
#
# The store handles five distinct actions "read", "search", "create", "update"
# and "destory". The requests made can be customised with options when the
# plugin is added to the Annotator. Custom headers can also be sent with every
# request by setting a $.data key on the Annotation#element containing headers
# to send. e.g:
#
#   annotator.element.data('annotation:headers', {
#     'X-My-Custom-Header': 'MyCustomValue'
#   })
#
#

# Scope in jQuery
$ = jQuery
Scribe = Drupal.settings.scribe
Range = Annotator.Range

# This header will now be sent with every request.
class Annotator.Plugin.DrupalStore extends Annotator.Plugin
  # The store listens for the following events published by the Annotator.
  # - annotationCreated: A new annotation has been created.
  # - annotationUpdated: An annotation has been updated.
  # - annotationDeleted: An annotation has been deleted.
  events:
    'annotationCreated': 'annotationCreated'
    'annotationDeleted': 'annotationDeleted'
    'annotationUpdated': 'annotationUpdated'

  # In Scribe there is a split of storage between the metadata
  # that is being stored (the annotation, typically just some text)
  # and the location within the document where it is stored (the attachment).
  #
  # This means we must take a given annotation object and prepare the correct
  # fields to be sent. This contains arrays with the correct properties to be mapped.
  fields:
    annotation: ['text', 'annotation_id', 'type', 'parent_id', 'field_parent_ref']
    attachment: ['attachment_id', 'entity_id', 'entity_type', 'bundle', 'field_name']
    text_attachment_info: ['quote', 'ranges', 'annotator_schema_version']

  # User customisable options available.
  options:

    annotationType: 'text'

    # Custom meta data that will be attached to every annotation that is sent
    # to the server. This _will_ override previous values.
    annotationData: {}

    # The server URLs for each available action. These URLs can be anything but
    # must respond to the appropraite HTTP method. The token ":id" can be used
    # anywhere in the URL and will be replaced with the annotation id.
    #
    # read:    GET
    # create:  POST
    # update:  PUT
    # destroy: DELETE
    # search:  GET
    urls:
      create:  Drupal.settings.basePath + 'scribe_annotation.json'
      create_attachment: Drupal.settings.basePath + 'scribe_attachment.json'
      read:    Drupal.settings.basePath + 'scribe_annotation.json/:id'
      update:  Drupal.settings.basePath + 'scribe_annotation.json/:id'
      update_attachment: Drupal.settings.basePath + 'scribe_attachment.json/:id'
      destroy: Drupal.settings.basePath + 'scribe_annotation.json/:id'
      destroy_attachment: Drupal.settings.basePath + 'scribe_attachment.json/:id'
      search:  Drupal.settings.basePath + 'scribe_attachment.json'

  # Public: The contsructor initailases the Store instance. It requires the
  # Annotator#element and an Object of options.
  #
  # element - This must be the Annotator#element in order to listen for events.
  # options - An Object of key/value user options.
  #
  # Examples
  #
  #   store = new Annotator.Plugin.Store(Annotator.element, {
  #     prefix: 'http://annotateit.org',
  #     annotationData: {
  #       uri: window.location.href
  #     }
  #   })
  #
  # Returns a new instance of Store.
  constructor: (element, options) ->
    super
    @annotations = []

  # Public: Initialises the plugin and loads the latest annotations. If the
  # Auth plugin is also present it will request an auth token before loading
  # any annotations.
  #
  # Examples
  #
  #   store.pluginInit()
  #
  # Returns nothing.
  pluginInit: ->
    return unless Annotator.supported()
    @annotator.setupAnnotation = @setupAnnotation
    this._getAnnotations()

    # Monkey patch onEditorSubmit
    @annotator.onEditorSubmit = @onEditorSubmit

  onEditorSubmit: (annotation) ->
    this.publish('annotationEditorSubmit', [@editor, annotation])

    if not annotation.annotation_id?
      this.setupAnnotation(annotation)
    else
      this.updateAnnotation(annotation)

  setupAnnotation: (annotation, fireEvents=true) ->
    root = @wrapper[0]
    annotation.ranges or= @selectedRanges

    # Make sure that the annotation is be attached
    # to the correct text field, if it isn't then
    # return the annotation for chaining

    if annotation.attachment_id
      $field = $(@wrapper.context).parent()

      # See if the entity type, bundle, and field_name
      # all match for the annotation and the field
      entity_data = ['entity_type', 'bundle', 'field_name']
      for data in entity_data
        if $field.data(data) != annotation[data]
          return annotation

      # See if the entity ID matches
      entity_id = (Number) $field.data('entity_id')
      annotation_entity_id = (Number) annotation.entity_id
      if entity_id != annotation_entity_id
        return annotation


    normedRanges = []
    for r in annotation.ranges
      try
        normedRanges.push(Range.sniff(r).normalize(root))
      catch e
        if e instanceof Range.RangeError
          this.publish('rangeNormalizeFail', [annotation, r, e])
        else
          # Oh Javascript, why you so crap? This will lose the traceback.
          throw e

    annotation.quote      = []
    annotation.ranges     = []
    annotation.highlights = []

    for normed in normedRanges
      annotation.quote.push      $.trim(normed.text())
      annotation.ranges.push     normed.serialize(@wrapper[0], '.annotator-hl')
      $.merge annotation.highlights, this.highlightRange(normed)

    # Join all the quotes into one string.
    annotation.quote = annotation.quote.join(' / ')

    # Save the annotation data on each highlighter element.
    $(annotation.highlights).data('annotation', annotation)

    # Fire annotationCreated events so that plugins can react to them.
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
      if @.type is 'text'
        # Move all of the text attachment info into
        # the base object
        $.extend @, @.text_attachment_info
        delete @.text_attachment_info

        # Move all of the annotation info into the base object
        # This will also move the children key directly into
        # the base object as well
        $.extend @, @.annotation
        delete @.annotation

        annotations.push @

    @annotations = @annotations.concat(annotations)
    @annotator.loadAnnotations(annotations)


  # Prepare an annotation to be sent to scribe.
  # This reads from the fields object to determine
  # which fields should be sent to the server for a given
  # type.
  scribePrepareData: (type, annotation) =>
    attachmentKey = @options.annotationType + '_attachment_info'

    # Copy over the necessary fields
    new_obj = {}
    for field in @.fields[type]
      if annotation[field]?
        new_obj[field] = annotation[field]

    # Add entity data to attachments
    # Add in attachment info into the proper
    # key.
    if type is 'attachment'
      $.extend new_obj, @scribeEntityData(annotation)
      new_obj[attachmentKey] = @scribePrepareData attachmentKey, annotation

    # Delete permission data as it's not necessary to submit
    if new_obj.annotation_create?
      delete new_obj.annotation_create

    # For all of our objects their type is "text"
    new_obj.type = @options.annotationType

    # Return the new object
    new_obj

  # Add entity data to an annotation before it's submitted.
  # This allows the annotation to be associated with the given
  # entity.
  scribeEntityData: (annotation) ->
    field = $(annotation.highlights[0]).parents('.field')
    field.data()

  # Public: Callback method for annotationCreated event. Receives an annotation
  # and sends a POST request to the sever using the URI for the "create" action.
  #
  # annotation - An annotation Object that was created.
  #
  # Examples
  #
  #   store.annotationCreated({text: "my new annotation comment"})
  #   # => Results in an HTTP POST request to the server containing the
  #   #    annotation as serialised JSON.
  #
  # Returns nothing.
  annotationCreated: (annotation) ->
    # Pre-register the annotation so as to save the list of highlight
    # elements.
    if annotation not in @annotations
      # Register annotation, at this point
      # we haven't formatted any data, and things
      # are in the basic annotation format.
      if not annotation.parent_id?
        this.registerAnnotation(annotation)

      # Format the annotation for usage with the scribe
      # module, move attachment data to the text_attachment_info
      # subarray
      annotation_data = @scribePrepareData 'annotation', annotation
      attachment_data = @scribePrepareData 'attachment', annotation

      # Save the attachment data
      if !annotation_data.parent_id
        this._apiRequest 'create_attachment', attachment_data, (attach_data) =>

          # Add the reference information into the annotation object
          annotation_data.field_parent_ref = attach_data

          # Update the in memory annotation
          # this.updateAnnotation annotation, attach_data

          # Create the annotation on the server
          @_apiRequest 'create', annotation_data, (data) =>
            # Update the annotation with returned data
            this.updateAnnotation annotation, data

            # Update with (e.g.) ID from server.
            if not data.id?
              console.warn Annotator._t("Warning: No ID returned from server for annotation "), annotation
      else
        @_apiRequest 'create', annotation_data, (data) =>
          # Update the annotation with returned data
          this.updateAnnotation annotation, data
    else
      # This is called to update annotations created at load time with
      # the highlight elements created by Annotator.
      this.updateAnnotation annotation, {}

  # Public: Callback method for annotationUpdated event. Receives an annotation
  # and sends a PUT request to the sever using the URI for the "update" action.
  #
  # annotation - An annotation Object that was updated.
  #
  # Examples
  #
  #   store.annotationUpdated({id: "blah", text: "updated annotation comment"})
  #   # => Results in an HTTP PUT request to the server containing the
  #   #    annotation as serialised JSON.
  #
  # Returns nothing.
  annotationUpdated: (annotation) ->
    if annotation in this.annotations or annotation.parent_id?
      updated_annotation = @scribePrepareData 'annotation', annotation
      this._apiRequest 'update', updated_annotation, ((data) => this.updateAnnotation(annotation, data))

  # Public: Callback method for annotationDeleted event. Receives an annotation
  # and sends a DELETE request to the server using the URI for the destroy
  # action.
  #
  # annotation - An annotation Object that was deleted.
  #
  # Examples
  #
  #   store.annotationDeleted({text: "my new annotation comment"})
  #   # => Results in an HTTP DELETE request to the server.
  #
  # Returns nothing.
  annotationDeleted: (annotation) ->
    if annotation.parent_id? and (parseInt(annotation.parent_id, 10) != 0)
      annotation_data = @scribePrepareData 'annotation', annotation
      this._apiRequest 'destroy', annotation_data
    else if annotation in this.annotations
      attachment_data = @scribePrepareData 'attachment', annotation
      this._apiRequest 'destroy_attachment', attachment_data, (() => this.unregisterAnnotation(annotation))

  # Public: Registers an annotation with the Store. Used to check whether an
  # annotation has already been created when using Store#annotationCreated().
  #
  # NB: registerAnnotation and unregisterAnnotation do no error-checking/
  # duplication avoidance of their own. Use with care.
  #
  # annotation - An annotation Object to resister.
  #
  # Examples
  #
  #   store.registerAnnotation({id: "annotation"})
  #
  # Returns registed annotations.
  registerAnnotation: (annotation) ->
    @annotations.push(annotation)

  # Public: Unregisters an annotation with the Store.
  #
  # NB: registerAnnotation and unregisterAnnotation do no error-checking/
  # duplication avoidance of their own. Use with care.
  #
  # annotation - An annotation Object to unresister.
  #
  # Examples
  #
  #   store.unregisterAnnotation({id: "annotation"})
  #
  # Returns remaining registed annotations.
  unregisterAnnotation: (annotation) ->
    @annotations.splice(@annotations.indexOf(annotation), 1)

  # Public: Extends the provided annotation with the contents of the data
  # Object. Will only extend annotations that have been registered with the
  # store. Also updates the annotation object stored in the 'annotation' data
  # store.
  #
  # annotation - An annotation Object to extend.
  # data       - An Object containing properties to add to the annotation.
  #
  # Examples
  #
  #   annotation = $('.annotation-hl:first').data('annotation')
  #   store.updateAnnotation(annotation, {extraProperty: "bacon sarnie"})
  #   console.log($('.annotation-hl:first').data('annotation').extraProperty)
  #   # => Outputs "bacon sarnie"
  #
  # Returns nothing.
  updateAnnotation: (annotation, data) ->
    if not annotation.parent_id?
      # If there isn't a Parent ID then we simply update the annotation object
      if annotation not in this.annotations
        console.error Annotator._t("Trying to update unregistered annotation!")
      else
        if data.resource == 'scribe_annotation'
          data.annotation_id = data.id
        else if data.resource == 'scribe_attachment'
          data.attachment_id = data.id
        delete data.id
        $.extend(annotation, data)

      # If there is no type then add it to the object
      if not annotation.type?
        annotation.type = @options.annotationType
    else
      # Otherwise we need to correctly update the reply
      # with any returned Data ID
      data.annotation_id = data.id
      delete data.id

      $.extend(annotation, data)

    # A dirty hack, add tags into the annotation immediately
    if annotation.field_annotation_tags?
      annotation.tags = []
      for tag in annotation.field_annotation_tags
        annotation.tags.push tag.name

    # Update the elements with our copies of the annotation objects (e.g.
    # with ids from the server).
    @updateAnnotationData(annotation)

  # Update the annotation data in the DOM
  updateAnnotationData: (annotation) ->
    $(annotation.highlights).data('annotation', annotation)

  # Insert a new reply into the set of annotations on the page
  #
  # This will return the root annotaiton where the reply is
  # contained so that the data being contained with the assoicated
  # DOM element can be updated
  # insertNewReply: (reply, annotations) ->
  #   for annotation in annotations

  #     # See if this is the parent
  #     if annotation.annotation_id == reply.parent_id
  #       annotation.children.push reply
  #       return annotation

  #     # Recursively call on children
  #     if annotation.children?
  #       if @insertNewReply(reply, annotation.children)
  #         return annotation

  #   false


  # Public: Makes a request to the server for all annotations.
  #
  # Examples
  #
  #   store.loadAnnotations()
  #
  # Returns nothing.
  loadAnnotations: () ->
    this._apiRequest 'read', null, this._onLoadAnnotations

  # Callback method for Store#loadAnnotations(). Processes the data
  # returned from the server (a JSON array of annotation Objects) and updates
  # the registry as well as loading them into the Annotator.
  #
  # data - An Array of annotation Objects
  #
  # Examples
  #
  #   console.log @annotation # => []
  #   store._onLoadAnnotations([{}, {}, {}])
  #   console.log @annotation # => [{}, {}, {}]
  #
  # Returns nothing.
  _onLoadAnnotations: (data=[]) =>
    @annotations = @annotations.concat(data)
    @annotator.loadAnnotations(data.list) # Clone array

  # Public: Performs the same task as Store.#loadAnnotations() but calls the
  # 'search' URI with an optional query string.
  #
  # searchOptions - Object literal of query string parameters.
  #
  # Examples
  #
  #   store.loadAnnotationsFromSearch({
  #     limit: 100,
  #     uri: window.location.href
  #   })
  #
  # Returns nothing.
  loadAnnotationsFromSearch: (searchOptions) ->
    this._apiRequest 'search', searchOptions, this._onLoadAnnotationsFromSearch

  # Callback method for Store#loadAnnotationsFromSearch(). Processes the data
  # returned from the server (a JSON array of annotation Objects) and updates
  # the registry as well as loading them into the Annotator.
  #
  # data - An Array of annotation Objects
  #
  # Returns nothing.
  _onLoadAnnotationsFromSearch: (data={}) =>
    this._onLoadAnnotations(data.rows || [])

  # Public: Dump an array of serialized annotations
  #
  # param - comment
  #
  # Examples
  #
  #   example
  #
  # Returns
  dumpAnnotations: ->
    (JSON.parse(this._dataFor(ann)) for ann in @annotations)

  # Callback method for Store#loadAnnotationsFromSearch(). Processes the data
  # returned from the server (a JSON array of annotation Objects) and updates
  # the registry as well as loading them into the Annotator.
  # Returns the jQuery XMLHttpRequest wrapper enabling additional callbacks to
  # be applied as well as custom error handling.
  #
  # action    - The action String eg. "read", "search", "create", "update"
  #             or "destory".
  # obj       - The data to be sent, either annotation object or query string.
  # onSuccess - A callback Function to call on successful request.
  #
  # Examples:
  #
  #   store._apiRequest('read', {id: 4}, (data) -> console.log(data))
  #   # => Outputs the annotation returned from the server.
  #
  # Returns jXMLHttpRequest object.
  _apiRequest: (action, obj, onSuccess) ->
    if obj.attachment_id
      id = obj.attachment_id
    else if obj.annotation_id
      id = obj.annotation_id
    else
      id  = obj && obj.id

    url = this._urlFor(action, id)
    options = this._apiRequestOptions(action, obj, onSuccess)

    request = $.ajax(url, options)

    # Append the id and action to the request object
    # for use in the error callback.
    request._id = id
    request._action = action
    request

  # Builds an options object suitable for use in a jQuery.ajax() call.
  #
  # action    - The action String eg. "read", "search", "create", "update"
  #             or "destory".
  # obj       - The data to be sent, either annotation object or query string.
  # onSuccess - A callback Function to call on successful request.
  #
  # Also extracts any custom headers from data stored on the Annotator#element
  # under the 'annotator:headers' key. These headers should be stored as key/
  # value pairs and will be sent with every request.
  #
  # Examples
  #
  #   annotator.element.data('annotator:headers', {
  #     'X-My-Custom-Header': 'CustomValue',
  #     'X-Auth-User-Id': 'bill'
  #   })
  #
  # Returns Object literal of $.ajax() options.
  _apiRequestOptions: (action, obj, onSuccess) ->
    method = this._methodFor(action)

    # Setup CSRF header required by Rest WS
    headers =
      'X-CSRF-Token': Drupal.settings.scribe.csrf_token

    opts = {
      type:       method,
      headers:    headers,
      dataType:   "json",
      success:    (onSuccess or ->),
      error:      this._onError
    }

    # If emulateHTTP is enabled, we send a POST and put the real method in an
    # HTTP request header.
    if @options.emulateHTTP and method in ['PUT', 'DELETE']
      opts.headers = $.extend(opts.headers, {'X-HTTP-Method-Override': method})
      opts.type = 'POST'

    # Don't JSONify obj if making search request.
    if action is "search"
      opts = $.extend(opts, data: obj)
      return opts

    data = obj && this._dataFor(obj)

    # If emulateJSON is enabled, we send a form request (the correct
    # contentType will be set automatically by jQuery), and put the
    # JSON-encoded payload in the "json" key.
    if @options.emulateJSON
      opts.data = {json: data}
      if @options.emulateHTTP
        opts.data._method = method
      return opts

    opts = $.extend(opts, {
      data: data
      contentType: "application/json; charset=utf-8"
    })
    return opts

  # Builds the appropriate URL from the options for the action provided.
  #
  # action - The action String.
  # id     - The annotation id as a String or Number.
  #
  # Examples
  #
  #   store._urlFor('update', 34)
  #   # => Returns "/store/annotations/34"
  #
  #   store._urlFor('search')
  #   # => Returns "/store/search"
  #
  # Returns URL String.
  _urlFor: (action, id) ->
    url = if @options.prefix? then @options.prefix else ''
    url += @options.urls[action]
    # If there's a '/:id' in the URL, either fill in the ID or remove the
    # slash:
    url = url.replace(/\/:id/, if id? then '/' + id else '')
    # If there's a bare ':id' in the URL, then substitute directly:
    url = url.replace(/:id/, if id? then id else '')

    url

  # Maps an action to an HTTP method.
  #
  # action - The action String.
  #
  # Examples
  #
  #   store._methodFor('read')    # => "GET"
  #   store._methodFor('update')  # => "PUT"
  #   store._methodFor('destroy') # => "DELETE"
  #
  # Returns HTTP method String.
  _methodFor: (action) ->
    table =
      'create':  'POST'
      'create_attachment': 'POST'
      'read':    'GET'
      'update':  'PUT'
      'update_attachment': 'PUT'
      'destroy': 'DELETE'
      'destroy_attachment': 'DELETE'
      'search':  'GET'

    table[action]

  # Creates a JSON serialisation of an annotation.
  #
  # annotation - An annotation Object to serialise.
  #
  # Examples
  #
  #   store._dataFor({id: 32, text: 'my annotation comment'})
  #   # => Returns '{"id": 32, "text":"my annotation comment"}'
  #
  # Returns
  _dataFor: (annotation) ->
    # Store a reference to the highlights array. We can't serialize
    # a list of HTMLElement objects.
    highlights = annotation.highlights

    delete annotation.highlights

    # Preload with extra data.
    $.extend(annotation, @options.annotationData)
    data = JSON.stringify(annotation)

    # Restore the highlights array.
    annotation.highlights = highlights if highlights

    data

  # jQuery.ajax() callback. Displays an error notification to the user if
  # the request failed.
  #
  # xhr - The jXMLHttpRequest object.
  #
  # Returns nothing.
  _onError: (xhr) =>
    action  = xhr._action
    message = Annotator._t("Sorry we could not ") + action + Annotator._t(" this annotation")

    if xhr._action == 'search'
      message = Annotator._t("Sorry we could not search the store for annotations")
    # else if xhr._action == 'read' && !xhr._id
    #   message = Annotator._t("Sorry we could not ") + action + Annotator._t(" the annotations from the store")

    switch xhr.status
      when 401 then message = Annotator._t("Sorry you are not allowed to ") + action + Annotator._t(" this annotation")
      #when 404 then message = Annotator._t("Sorry we could not connect to the annotations store")
      when 500 then message = Annotator._t("Sorry something went wrong with the annotation store")

    if xhr.status != 404
      Annotator.showNotification message, Annotator.Notification.ERROR
      console.error Annotator._t("API request failed:") + " '#{xhr.status}'"
    else
      console.log Annotator._t("No annotations were found on this page.")



