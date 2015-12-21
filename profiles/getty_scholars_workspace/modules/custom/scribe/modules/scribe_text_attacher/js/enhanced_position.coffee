# A plugin for annotator that helps enhance the positioning
# of elements by placing them on fixed position on the page.
# This means that they will not get cut off by the overflow
# property that can be applied to certain elements.

$ = jQuery

class Annotator.Plugin.EnhancedPosition extends Annotator.Plugin
  constructor: (element, options) ->
    super

  # Public: Initializes the plugin and registers fields with the
  pluginInit: ->
    return unless Annotator.supported()

    # Override various methods
    @annotator.showEditor = @showEditor
    @annotator.showViewer = @showViewer
    @annotator.calculateViewportPosition = @calculateViewportPosition

  showEditor: (annotation, location) ->
    location.position = 'fixed'

    scrollTop = $(window).scrollTop()
    scrollLeft = $(window).scrollLeft()

    location.top = location.top - scrollTop
    location.left = location.left - scrollLeft


    @editor.element.css(location)
    @editor.load(annotation)
    this.publish('annotationEditorShown', [@editor, annotation])
    this

  showViewer: (annotations, location) ->
    @viewer.element.css(@calculateViewportPosition(location))
    @viewer.load(annotations)
    this.publish('annotationViewerShown', [@viewer, annotations])

  # Calculate the position where an annotation
  # UI widget should be shown relative to the viewport
  # for fixed positioning
  calculateViewportPosition: (location) ->
    # Get window scroll position
    scrollTop = $(window).scrollTop()
    scrollLeft = $(window).scrollLeft()

    # Get offset of wrapper element relative to page
    offset = @wrapper.offset()

    # Calculate new locations
    topPos = location.top + offset.top - scrollTop
    leftPos = location.left + offset.left - scrollLeft

    newLocation = {
      position: 'fixed',
      top: topPos,
      left: leftPos
    }
