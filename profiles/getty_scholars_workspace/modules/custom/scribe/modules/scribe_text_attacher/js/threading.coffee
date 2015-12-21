# A plugin that allows for threading of annotaitons so that annotations
# can be replied to.

$ = jQuery

class Annotator.Plugin.Threading extends Annotator.Plugin
  html:
    reply:"""
          <button title="Reply" class="annotator-reply">Reply</button>
          """
    list:"""
         <ul class="annotator-listing"></ul>
         """
    editor:"""
           <form class="annotator-editor annotator-reply-form">
             <textarea placeholder="Reply..."></textarea>
             <div>
               <a href="#cancel" class="annotator-cancel annotator-reply-cancel">Cancel</a>
               <a href="#save" class="annotator-save annotator-reply-save annotator-focus">Save</a>
             </div>
           </form>
           """


  # If a reply is being edited
  editReply: false

  # These events maintain the awareness of annotations between the two
  # communicating annotators.
  events:
    #"form.annotator-editor submit":   "submit"
    ".annotator-reply-cancel click":  "cancel"
    ".annotator-reply-save click":    "submit"
    "button.annotator-reply click":   "onReplyClick"

  options:
    readOnly: false

  pluginInit: ->
    @viewer = @annotator.viewer
    @viewer.on('load', @onViewerLoad)

    # Monkey patch annotator to use our startViewerHideTimer function
    @annotator.startViewerHideTimer = @startViewerHideTimer

    # We must unbind the mouseout event of the viewer element
    # and then rebind it to out startViewerHideTimer function
    $(@viewer.element).unbind('mouseout').bind({
      'mouseout': @startViewerHideTimer
    })

    # We also need to unbind the save event of the editor
    # element and then rebind it to our version
    @annotator.editor.unsubscribe('save', @annotator.onEditorSubmit)
    @annotator.editor.on('save', @annotatorOnEditorSubmit)

    # Retrive the viewer item
    @item = @viewer.item

    # Monkey patch the delete annotation since on replies
    # there will be no highlights element.
    @annotator.deleteAnnotation = @annotatorDeleteAnnotation

    # Monkey patch onEditorSubmit in annotator since replies
    # won't have any ranges elements on them. Instead we can
    # check for an ID


  # Monkey patched deleteAnnotation method in annotator.
  # We check for annotation highlights since replies don't
  # have highlights
  annotatorDeleteAnnotation: (annotation) ->
    if annotation.highlights?
      for h in annotation.highlights
        $(h).replaceWith(h.childNodes)

    this.publish('annotationDeleted', [annotation])
    annotation

  # Callback method called when the @editor fires the "save" event. Itself
  # publishes the 'annotationEditorSubmit' event and creates/updates the
  # edited annotation.
  #
  # Returns nothing.
  annotatorOnEditorSubmit: (annotation) =>
    @annotator.publish('annotationEditorSubmit', [@annotator.editor, annotation])

    if not annotation.annotation_id?
      @annotator.setupAnnotation(annotation)
    else
      @annotator.updateAnnotation(annotation)

  startViewerHideTimer: =>
    # Don't do this if timer has already been set by another annotation.
    if not @annotator.viewerHideTimer and not @editReply
      @annotator.viewerHideTimer = setTimeout @annotator.viewer.hide, 250

  # Callback for when the viewer is loaded
  # For all of the annotations being viewed
  # load in all annotations in the the thread
  onViewerLoad: (annotations) =>
    list = $(@viewer.element).find('.annotator-listing > .annotator-item')

    # Load the thread of all annotations
    for annotation, index in annotations
      if annotation.children?
        # Create submit and load annotations
        sublist = $(@html.list).clone()
        @loadThread(sublist, annotation.children)

        # Add the replies into each list item and add the correct controls
        controls = $(list[index]).append(sublist).find('.annotator-controls')
        @addReplyButton(controls)

  # Load a full thread of annotations
  loadThread: (list, annotations) =>
    for child in annotations
      # Load all of the direct replies
      # Add the item into the list
      item = $(@item).clone().append('<div>' + child.text + '</div>')
      item.data({annotation: child})
      list.append(item)

      # Add the reply control into its controls
      controls = item.find('.annotator-controls')
      #@addReplyButton(controls)

      # From annotator, need to be able  place the controller methods
      # on the various elements for permissions to work
      controls.find('.annotator-link').remove()
      edit = controls.find('.annotator-edit')
      del  = controls.find('.annotator-delete')

      if @options.readOnly
        edit.remove()
        del.remove()
      else
        controller = {
          showEdit: -> edit.removeAttr('disabled')
          hideEdit: -> edit.attr('disabled', 'disabled')
          showDelete: -> del.removeAttr('disabled')
          hideDelete: -> del.attr('disabled', 'disabled')
        }

      # Update the controls on this annotation
      if @annotator.plugins.DrupalPermissions?

        # Add in a div for the username
        userDiv = $('<div />')[0]
        item.append(userDiv)

        # Update control view
        @annotator.plugins.DrupalPermissions.updateViewer(userDiv, child, controller)

      # Load all the replies to this particular child recursively
      if child.children? and child.children.length > 0
        sublist = $(@html.list).clone()
        item.append(sublist)
        @loadThread(sublist, child.children)

  # Add a reply button into the annotator controls
  addReplyButton: (element) ->
    reply_button = $(@html.reply).clone()
    element.prepend(reply_button)

  onReplyClick: (event) =>
    # Close any open editors
    $(event.target).parents('.annotator-annotation').find('.annotator-reply-form').remove()

    # Get a copy of the editor
    editor = $(@html.editor).clone()

    # Grab the annotation item
    annotation_item = $(event.target).parents('.annotator-annotation')[0]

    # Append the editor
    $(annotation_item).append(editor)

    # Set that we are editing a reply
    @editReply = true

  cancel: (event) ->
    event?.preventDefault?()
    $(event.target).parents('.annotator-reply-form').remove()
    @editReply = false

  # Hook into onEditorSubmit in annotator
  # so that when we submit our form save
  # functions in the storage plugin will be called
  submit: (event) ->
    event?.preventDefault?()

    # Retrieve the reply text
    form = $(event.target).parents('.annotator-reply-form')
    val = form.find('textarea').val()

    # Retrive the direct parent annotation
    annotation_item = $(event.target).parents('.annotator-annotation')
    annotation = annotation_item.data().annotation

    # Retrieve the elements for the direct parent annotation
    # and also for the root annotation
    annotation_parent = $(annotation_item).first();
    annotation_root = $(annotation_item).last();

    # Retrieve the data from these elements
    parent_data = annotation_parent.data();
    root_data = annotation_root.data();
    attachment = root_data.annotation

    # Create the new item to insert
    new_item = $(@item).clone().append('<div>' + val + '</div>')
    controls = new_item.find('.annotator-controls')
    @addReplyButton(controls)

    # Add the new comment into the document
    # We may need to add a new UL if this is
    # the first reply at this level
    list = annotation_item.children('ul:first')
    if list.length > 0
      list.append(new_item)
    else
      new_list = $(@html.list).clone()
      new_list.append(new_item)
      annotation_item.append(new_list)

    # Create a new annotation
    new_annotation = @annotator.createAnnotation()
    new_annotation.text = val
    new_annotation.field_parent_ref = {
      id: attachment.attachment_id
    }

    if annotation.annotation_id?
      new_annotation.parent_id = annotation.annotation_id
    else
      new_annotation.parent_id = annotation.annotation.annotation_id

    console.log 'stuff'
    console.log new_annotation

    # Save the annotation
    @annotator.onEditorSubmit(new_annotation)

    # Update the data entry with the child
    if annotation.children
      annotation.children.push new_annotation
    else
      annotation.children = [new_annotation]

    ###
    The full annotation data is stored in the highlight.
    So we need to go back and update the annotation there, regardless
    of where we are in the thread.
    ###
    $(annotation.highlights).data({annotation: annotation});

    # Hide the form
    form.hide()

    # We are no longer editing so if we mouseout we
    # can hide the viewer.
    @editReply = false
