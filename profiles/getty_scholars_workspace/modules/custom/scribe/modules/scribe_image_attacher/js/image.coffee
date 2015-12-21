# An image annotator plugin for the annotator library.
# Allows rectangular areas of images to be annotated.

$ = jQuery

class Annotator.Plugin.ImageAnnotator extends Annotator.Plugin
  # Pick up the annotation deleted event
  'events':
    'annotationDeleted': 'annotationDeleted'

  # Set the active editor, this allows
  # us to close and clear annotations as necessary
  activeEditor = null

  # Allow for new image annotations to be created by default
  options:
    readOnly: false

  # Construction Junction
  constructor: (element, options) ->
    super
    @editors = {}

  # Initialize the plugin
  pluginInit: ()->
      return unless Annotator.supported()

      # Intialize all of the images within
      # the annotator wrapper
      @_initMatchingImages()._initEditingBehaviors()

  # Creates an image annotator for every
  # image within the annotator wrapper
  _initMatchingImages: () =>
    $(@element).find('img').each (index, el) =>
      editor = new Annotator.ImageAnnotator(el, @options)
      editor.on('imageAnnotatorMouseOver', @imageAnnotatorMouseOver)
      editor.on('imageAnnotatorMouseOut', @imageAnnotatorMouseOut)
      editor.on('imageAnnotatorSelectStart', @imageAnnotatorSelectStart)
      editor.on('imageAnnotatorSelectFinish', @imageAnnotatorSelectFinish)
      editor.on('imageAnnotatorAnnotationHovered', @imageAnnotatorAnnotationHovered)

      src = $(el).attr('src')
      pathname = @parseURI(src).pathname
      @editors[pathname] = editor

    # Return for chaining
    @

  # Initialize any behaviors for the editor so that
  # we can interface with the image annotation editor
  _initEditingBehaviors: () =>
    @annotator.editor.on('hide', @onAnnotatorEditorHide)

    # Return for chaining
    @

  # Hide the annotation editor if we're beginning another selection
  imageAnnotatorSelectStart: (e) =>
    if @annotator.editor? and $(@annotator.editor.element).is(':visible')
      @annotator.editor.hide()

  # When a selection is finished show the annotation
  imageAnnotatorSelectFinish: (e) =>
    # Retrieve event properties
    editor = e.editor
    positions = e.positions

    # Set the active editor
    @activeEditor = editor

    src = $(editor.img).attr('src')
    pathname = @parseURI(src).pathname

    # Create the annotation and add image attachment data as well
    annotation = @annotator.createAnnotation()
    annotation.shapes = positions
    annotation.shape_type = 'rectangle'
    annotation.annotorious_schema_version = 'v0.1'
    annotation.type = 'image'
    annotation.src = pathname

    # Get the position for the editor and show it
    editorPos = @getElementPosition(positions, @annotator.element, editor.img)
    @annotator.showEditor(annotation, editorPos)

  # Activated when an annotation is being hovered over
  imageAnnotatorAnnotationHovered: (e) =>
    editor = e.editor
    annotations = e.annotations
    highest = e.highestAnnotation

    # Set the viewer position
    viewerPos = @getElementPosition highest.shapes, @annotator.element, editor.img
    @annotator.showViewer(annotations, viewerPos)

  # Disable the image annotation editor on
  # the given image
  disableAnnotator: (img) =>
    uri = @parseURI $(img).attr('src')
    @editors[uri.pathname].disable()

  # Enable the image annotation editor on
  # the given image.
  enableAnnotator: (img) =>
    uri = @parseURI $(img).attr('src')
    @editors[uri.pathname].enable()

  # When we mouse over the image editor we reset
  # the viewer hide timer so that the viewer
  # can be hidden again
  imageAnnotatorMouseOver: (e) =>
    @annotator.clearViewerHideTimer()

  # Make sure to remove the annotation
  annotationDeleted: (annotation) =>
    if annotation.src?
      @editors[annotation.src].removeAnnotation(annotation)

  # When the image annotation editor is no longer being hovered over
  # then we start the time to hide the annotation viewer
  imageAnnotatorMouseOut: (e) =>
    @annotator.startViewerHideTimer()

  # Cleanup the image annotation editor when the
  # editing element is hidden
  onAnnotatorEditorHide: () =>
    if @activeEditor?
      @activeEditor.redrawAnnotations()
      @activeEditor = null

  # Add an annotation into a particular editor for an
  # image.  We map the image onto to editor by matching the source
  addImageAnnotation: (annotation) ->
    # Get the editor for the annotation
    if @editors[annotation.src]?
      @editors[annotation.src].addAnnotation annotation
    else
      console.log('The image annotator for the image %s could not be found.', annotation.src)

  # Update the annotation with data from the server
  updateImageAnnotation: (annotation) ->
    @editors[annotation.src].updateAnnotation(annotation)

  # Set the readOnly value of all editors
  setReadOnly: (value) =>
    for src, editor of @editors
      editor.options.readOnly = value

  # Calculate where the viewer or editor should be shown.
  # Calculates where the top left of the image is relative
  # to the wrapping element, and then positions the element
  # on the top left of the annotation box
  getElementPosition: (shapes, wrapper, img) ->
    wrapperPos = $(wrapper).offset()
    imgPos = $(img).offset()

    offsetPos =
      top: Math.round(imgPos.top) - Math.round(wrapperPos.top)
      left: Math.round(imgPos.left) - Math.round(wrapperPos.left)

    return {
      top: shapes.topleft.y + offsetPos.top + 5
      left: shapes.topleft.x + offsetPos.left
    }

  # Parse a URI
  parseURI: (uri) ->
    parser = document.createElement 'a'
    parser.href = uri
    parser
