# An image canvas overlay which allows images
# to be annotated.

$ = jQuery

class Annotator.ImageAnnotator extends Annotator.Widget
  events:
    '.annotator-image-canvas mouseover': "onEditorMouseOver"
    '.annotator-image-canvas mouseout': "onEditorMouseOut"
    '.annotator-image-edit mousedown': "onEditorMouseDown"
    '.annotator-image-edit mouseup': "onEditorMouseUp"
    '.annotator-image-edit mousemove': "onEditorMouseMove"

  html:
    imageWrapper:"""
      <div class="annotator-image-wrapper"></div>
      """
    editCanvas: """
      <canvas class="annotator-image-edit"></canvas>
      """

  # Used to see if a selection is currently being made
  selecting = false

  options:
    # If this image canvas is read only
    # and annotations can only be viewed
    # but not created or edited
    readOnly: false

    # The color of the outer rectangle
    # used when making a selection or
    # viewing annotations.
    outerRectColor: '#000000'

    # The color of the inner rectangle
    # used when making a selection or
    # viewing annotations.
    innerRectColor: '#FFFFFF'

    # The color used for highlighted rectangles
    # so that they can be highlighted when being
    # hovered or for other focused actions
    innerRectColorHighlight: '#C1FAC4'

  # Store the positions of mouse click events
  # on top of the canvas
  positions:
    original: null
    current: null

  constructor: (el, options) ->
    # Run the parent constructor to delegate events
    super $(@html.imageWrapper)[0], options

    # Grab the image
    @img = $(el)

    # Initialize all of the editor and viewer components
    @_initImageWrapper()._initEditor()

    # Initialize a set of annotations that
    # we're managing for this image
    @annotations = []

  # Initialize the image wrapper so that
  # we can place the editing canvas over
  # the image
  _initImageWrapper: () ->
    # Set the properties of the wrapper
    props =
      height: @img.height()
      position: 'relative'
      width: @img.width()

    @element.css(props)

    # Wrap the image in our image wrapper
    @img.wrap(@element)

    # Return this for chaining
    @

  # Initialize the editing component of
  # the image annotator so that annotations
  # can be added
  _initEditor: ()->
    # Create the editor
    @canvas = $(@html.editCanvas)[0]

    # Set the properties of the editor
    props =
      cursor: 'crosshair'
      height: @img.height()
      position: 'absolute'
      width: @img.width()
      zIndex: 10
    $(@canvas).css(props)

    # Set the width and height of the editor
    attr =
      height: @img.height()
      width: @img.width()
    $(@canvas).attr(attr)

    # Add the editor into the DOM
    @img.before(@canvas)

    # Retrieve a 2d editing context for the canvas
    # so that we can draw shapes on it
    @context = @canvas.getContext '2d'

    # Return this for chaining
    @

  ###
  Section - Annotation API
  ###

  # Add an annotation
  addAnnotation: (annotation) ->
    @annotations.push annotation
    @redrawAnnotations()

  # Update annotations
  updateAnnotation: (annotation) ->
    index = @annotations.indexOf(annotation)
    @annotations[index] = annotation
    redrawAnnotations()

  # Remove annotation from the editor
  removeAnnotation: (annotation) ->
    @annotations.splice(@annotations.indexOf(annotation), 1)
    @redrawAnnotations()

  ###
  Section - Editor API
  ###

  # Causes the editor to be disabled
  disable: () ->
    # Remove the wrapping element
    $(@img).unwrap()

    # Hide the editing canvas
    $(@canvas).remove()

  # Causes the editor to be enabled
  enable: () ->
    # Rewrap the image with our container
    $(@img).wrap(@element)

    # Re-insert the editing canvas
    $(@img).before(@canvas)

  ###
  Section - Event Callbacks
  ###

  # Publish event for when we get a mouse in
  onEditorMouseOver: (e) ->
    @publish('imageAnnotatorMouseOver', e)

  # Publish event for when we get a mouseout
  onEditorMouseOut: (e) ->
    @publish('imageAnnotatorMouseOut', e)

  # Begin selecting an area to be annotated
  onEditorMouseDown: (e) ->
    if not @options.readOnly
      e.preventDefault()

      # Indicate that a selection is being made
      @selecting = true

      # Determine the start position of the mouse click
      @positions.original  = @eventMousePosition(e)

      # Fire an event for the start of the selection
      @publish('imageAnnotatorSelectStart', {editor: @, position: @positions.original})

  # When mouse up occrus stop selecting and fire the event
  # with the positional information of the rectangle selected
  # (top left and bottom right corners) so the the edito can be
  # presented
  onEditorMouseUp: (e) =>
    @selecting = false

    # Fire new event indicating that the selection was finished
    if @positions.current? and not @options.readOnly
      if Math.abs(@positions.current.x - @positions.original.x) > 3
        if Math.abs(@positions.current.y - @positions.original.y) > 3
          @publish('imageAnnotatorSelectFinish', {editor: @, positions: @normalizeCoordinates()})

  # If we're selecting an area then update
  # the rectangle for the area being selected
  onEditorMouseMove: (e) ->
    # Get the current mouse position
    @positions.current = @eventMousePosition(e)

    # If selection is occurring then redraw the box
    if @selecting
      @redrawAnnotations()
      @drawRect @positions.original, @positions.current
    else
      # See if any annotations are being hovered over if they
      # are then we're going to need to show the
      hoveredAnnotations = @annotationsWithPoint(@positions.current)
      if hoveredAnnotations.length
        ev =
          editor: @
          annotations: hoveredAnnotations
          highestAnnotation: @highestAnnotation(hoveredAnnotations)
        @publish('imageAnnotatorAnnotationHovered', ev)

  ###
  Section - Canvas Operations
  ###

  # Redraw all of the annotations onto the canvas
  redrawAnnotations: () ->
    @clearCanvas()

    for annotation in @annotations
      highlight = if annotation.highlight? then highlight else false
      @drawRect(annotation.shapes.topleft, annotation.shapes.bottomright, highlight)

  # Draw a rectangle on the canvas for the area
  # that we're selecting
  drawRect: (originalPos, currentPos, highlight=false) ->
    # Grab the x and y coordinates from the original position
    x = originalPos.x
    y = originalPos.y

    # Calculate the width and height of the resulting rectangle
    width =  currentPos.x - originalPos.x
    height = currentPos.y - originalPos.y

    # Draw the outer rectangle
    @context.strokeStyle = @options.outerRectColor
    @context.strokeRect(x + 0.5, y + 0.5, width, height)

    # Set the positioning and size of the inner rectangle
    if width > 0 and height > 0
      x += 1.5
      y += 1.5
      width -= 2
      height -= 2
    else if width > 0 and height < 0
      x += 1.5
      y -= 0.5
      width -= 2
      height += 2
    else if width < 0 and height < 0
      x -= 0.5
      y += 0.5
      width += 2
      height += 2
    else
      x += 0.5
      y += 1.5
      width += 2
      height -= 2

    # Draw the inner rectangle
    innerColor = if highlight then @options.innerRectColorHighlight else @options.innerRectColor
    @context.strokeStyle = innerColor
    @context.strokeRect(x, y, width, height)

  # Clear the canvas so that it can be redrawn
  clearCanvas: () ->
    @context.save
    @context.setTransform 1, 0, 0, 1, 0, 0
    @context.clearRect(0, 0, @canvas.width, @canvas.height)
    @context.restore

  ###
  Section - Mouse handling and point related utilities
  ###

  # At the end of our selection we must determine the
  # top left and the bottom right of the rectangle.
  #
  # Depending on which direction the selection occurs
  # the coordinates can be different corners of the resulting
  # rectangle
  normalizeCoordinates: () ->
    topleft =
      x: 0
      y: 0

    bottomright =
      x: 0
      y: 0

    # Get the top left and bottom right y-coordinates
    if @positions.current.y < @positions.original.y
      topleft.y = @positions.current.y
      bottomright.y = @positions.original.y
    else
      topleft.y = @positions.original.y
      bottomright.y = @positions.current.y

    # Get the top left and bottom right x-coordinates
    if @positions.current.x < @positions.original.x
      topleft.x = @positions.current.x
      bottomright.x = @positions.original.x
    else
      topleft.x = @positions.original.x
      bottomright.x = @positions.current.x

    {topleft: topleft, bottomright: bottomright}

  # Returns a set of all annotatition that
  # contain the given point.
  annotationsWithPoint: (point) ->
    annotation for annotation in @annotations when @pointInBox(point, annotation.shapes)

  # Determines if a point lies inside of a bounding
  # box.
  pointInBox: (point, box) ->
    if point.x >= box.topleft.x and point.y >= box.topleft.y
      if point.x <= box.bottomright.x and point.y <= box.bottomright.y
        return true

    false

  # Determine which box out of a set of boxes has the lowest
  # (and therefore highest on the screen) y value.  This is
  # useful in setting location for viewer display
  highestAnnotation: (annotations) ->
    [highest, rest...] = annotations

    for box in rest
      if box.shapes.topleft.y < highest.shapes.topleft.y
        highest = box

    highest

  # Determine the position on the mouse on top
  # of the editor
  eventMousePosition: (e) ->
    # Retrieve the offset of the canvas element
    offset = $(@canvas).offset()

    # Construct an object for the position
    # We use Mat.round since jQuery's .offset()
    # can return non-integer numbers
    pos =
      x: e.pageX - Math.round(offset.left)
      y: e.pageY - Math.round(offset.top)

