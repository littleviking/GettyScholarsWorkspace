# Public: Plugin for setting permissions on newly created annotations as well as
# managing user permissions such as viewing/editing/deleting annotions.
#
# element - A DOM Element upon which events are bound. When initialised by
#           the Annotator it is the Annotator element.
# options - An Object literal containing custom options.
#
# Examples
#
#   new Annotator.plugin.Permissions(annotator.element, {
#     user: 'Alice'
#   })
#
# Returns a new instance of the Permissions Object.
$ = jQuery
CreatePerm = Drupal.settings.scribe.permissions.text.create
ImageCreatePerm = Drupal.settings.scribe.permissions.image.create
Range = Annotator.Range


util =
  uuid: (-> counter = 0; -> counter++)()

  getGlobal: -> (-> this)()

  # Return the maximum z-index of any element in $elements (a jQuery collection).
  maxZIndex: ($elements) ->
    all = for el in $elements
            if $(el).css('position') == 'static'
              -1
            else
              parseInt($(el).css('z-index'), 10) or -1
    Math.max.apply(Math, all)

  mousePosition: (e, offsetEl) ->
    offset = $(offsetEl).offset()
    {
      top:  e.pageY - offset.top,
      left: e.pageX - offset.left
    }

  # Checks to see if an event parameter is provided and contains the prevent
  # default method. If it does it calls it.
  #
  # This is useful for methods that can be optionally used as callbacks
  # where the existance of the parameter must be checked before calling.
  preventEventDefault: (event) ->
    event?.preventDefault?()


class Annotator.Plugin.DrupalPermissions extends Annotator.Plugin

  # A Object literal consisting of event/method pairs to be bound to
  # @element. See Delegator#addEvents() for details.
  events:
    'beforeAnnotationCreated': 'addFieldsToAnnotation'

  # A Object literal of default options for the class.
  options:

    # Displays an "Anyone can view this annotation" checkbox in the Editor.
    showViewPermissionsCheckbox: true

    # Displays an "Anyone can edit this annotation" checkbox in the Editor.
    showEditPermissionsCheckbox: true

    # Public: Used by the plugin to determine a unique id for the @user property.
    # By default this accepts and returns the user String but can be over-
    # ridden in the @options object passed into the constructor.
    #
    # user - A String username or null if no user is set.
    #
    # Returns the String provided as user object.
    userId: (user) -> user

    # Public: Used by the plugin to determine a display name for the @user
    # property. By default this accepts and returns the user String but can be
    # over-ridden in the @options object passed into the constructor.
    #
    # user - A String username or null if no user is set.
    #
    # Returns the String provided as user object
    userString: (user) -> user

    # Public: Used by Permissions#authorize to determine whether a user can
    # perform an action on an annotation. Overriding this function allows
    # a far more complex permissions sysyem.
    #
    # By default this authorizes the action if any of three scenarios are true:
    #
    #     1) the annotation has a 'permissions' object, and either the field for
    #        the specified action is missing, empty, or contains the userId of the
    #        current user, i.e. @options.userId(@user)
    #
    #     2) the annotation has a 'user' property, and @options.userId(@user) matches
    #        'annotation.user'
    #
    #     3) the annotation has no 'permissions' or 'user' properties
    #
    # annotation - The annotation on which the action is being requested.
    # action - The action being requested: e.g. 'update', 'delete'.
    # user - The user object (or string) requesting the action. This is usually
    #        automatically passed by Permissions#authorize as the current user (@user)
    #
    #   permissions.setUser(null)
    #   permissions.authorize('update', {})
    #   # => true
    #
    #   permissions.setUser('alice')
    #   permissions.authorize('update', {user: 'alice'})
    #   # => true
    #   permissions.authorize('update', {user: 'bob'})
    #   # => false
    #
    #   permissions.setUser('alice')
    #   permissions.authorize('update', {
    #     user: 'bob',
    #     permissions: ['update': ['alice', 'bob']]
    #   })
    #   # => true
    #   permissions.authorize('destroy', {
    #     user: 'bob',
    #     permissions: [
    #       'update': ['alice', 'bob']
    #       'destroy': ['bob']
    #     ]
    #   })
    #   # => false
    #
    # Returns a Boolean, true if the user is authorised for the token provided.
    userAuthorize: (action, annotation, user) ->
      # Fine-grained custom authorization
      if annotation.permissions
        tokens = annotation.permissions[action] || []

        if tokens.length == 0
          # Empty or missing tokens array: anyone can perform action.
          return true

        for token in tokens
          if this.userId(user) == token
            return true

        # No tokens matched: action should not be performed.
        return false

      # Coarse-grained authorization
      else if annotation.user
        return user and this.userId(user) == this.userId(annotation.user)

      # No authorization info on annotation: free-for-all!
      true

    # Default user object.
    user: ''

    # Default permissions for all annotations. Anyone can do anything
    # (assuming default userAuthorize function).
    permissions: {
      'read':   []
      'update': []
      'delete': []
      'admin':  []
    }

  # The constructor called when a new instance of the Permissions
  # plugin is created. See class documentation for usage.
  #
  # element - A DOM Element upon which events are bound..
  # options - An Object literal containing custom options.
  #
  # Returns an instance of the Permissions object.
  constructor: (element, options) ->
    super

    if @options.user
      this.setUser(@options.user)
      delete @options.user

  # Public: Initializes the plugin and registers fields with the
  # Annotator.Editor and Annotator.Viewer.
  #
  # Returns nothing.
  pluginInit: ->
    return unless Annotator.supported()

    self = this
    createCallback = (method, type) ->
      (field, annotation) -> self[method].call(self, type, field, annotation)

    # Set up user and default permissions from auth token if none currently given
    if !@user and @annotator.plugins.Auth
      @annotator.plugins.Auth.withToken(this._setAuthFromToken)

    if @options.showViewPermissionsCheckbox == true
      @annotator.editor.addField({
        type:   'checkbox'
        label:  Annotator._t('Allow anyone to <strong>view</strong> this annotation')
        load:   createCallback('updatePermissionsField', 'read')
        submit: createCallback('updateAnnotationPermissions', 'read')
      })

    if @options.showEditPermissionsCheckbox == true
      @annotator.editor.addField({
        type:   'checkbox'
        label:  Annotator._t('Allow anyone to <strong>edit</strong> this annotation')
        load:   createCallback('updatePermissionsField', 'update')
        submit: createCallback('updateAnnotationPermissions', 'update')
      })

    # Setup the display of annotations in the Viewer.
    @annotator.viewer.addField({
      load: this.updateViewer
    })

    # Add a filter to the Filter plugin if loaded.
    if @annotator.plugins.Filter
      @annotator.plugins.Filter.addFilter({
        label: Annotator._t('User')
        property: 'user'
        isFiltered: (input, user) =>
          user = @options.userString(user)

          return false unless input and user
          for keyword in (input.split /\s*/)
            return false if user.indexOf(keyword) == -1

          return true
      })

    $(document).unbind('mouseup', @annotator.checkForEndSelection).bind({
      'mouseup': @checkForEndSelection
    })

    @annotator.viewer.onDeleteClick = @onDeleteClick

  onDeleteClick: (event) ->
    deleteConfirmed = confirm(Annotator._t('Are you sure you want to delete this annotation?'))
    if deleteConfirmed
      this.onButtonClick(event, 'delete')

  # Disables creation of an annotation of the user does not have permission to
  # do it
  # checkCreatePerm: () =>
  #   # Set the annotations to be read only
  #   if not CreatePerm
  #     @annotator.ignoreMouseup = true

  #   if @annotator.plugins.ImageAnnotator? and not ImageCreatePerm
  #     @annotator.plugins.ImageAnnotator.setReadOnly(true)

  # Annotator#element callback. Checks to see if a selection has been made
  # on mouseup and if so displays the Annotator#adder. If @ignoreMouseup is
  # set will do nothing. Also resets the @mouseIsDown property.
  #
  # event - A mouseup Event object.
  #
  # Returns nothing.
  checkForEndSelection: (event) =>
    @annotator.mouseIsDown = false

    # This prevents the note image from jumping away on the mouseup
    # of a click on icon.
    if @annotator.ignoreMouseup
      return

    # Get the currently selected ranges.
    @annotator.selectedRanges = @annotator.getSelectedRanges()

    # Check for the create permission on the field content
    # If the user doesn't have it then do nothing
    if not @checkCreatePerm()
      return

    for range in @annotator.selectedRanges
      container = range.commonAncestor
      if $(container).hasClass('annotator-hl')
        container = $(container).parents('[class^=annotator-hl]')[0]
      return if @annotator.isAnnotator(container)

    if event and @annotator.selectedRanges.length
      pos = util.mousePosition(event, @annotator.wrapper[0])
      newPos = @annotator.calculateViewportPosition(pos)
      @annotator.adder
        .css(newPos)
        .show()
    else
      @annotator.adder.hide()

  # Check to see if the user has access to the create
  # permission for a given piece of content
  checkCreatePerm: () ->
    if @annotator.selectedRanges.length > 0
      parentContainer = $(@annotator.selectedRanges[0].commonAncestor).parents('.field')
      createPerm = parentContainer.data('annotation_create')
      return parseInt(createPerm, 10) is 1

    # If nothing has been selected than nothing can be created
    false


  # Public: Sets the Permissions#user property.
  #
  # user - A String or Object to represent the current user.
  #
  # Examples
  #
  #   permissions.setUser('Alice')
  #
  #   permissions.setUser({id: 35, name: 'Alice'})
  #
  # Returns nothing.
  setUser: (user) ->
    @user = user

  # Event callback: Appends the @user and @options.permissions objects to the
  # provided annotation object. Only appends the user if one has been set.
  #
  # annotation - An annotation object.
  #
  # Examples
  #
  #   annotation = {text: 'My comment'}
  #   permissions.addFieldsToAnnotation(annotation)
  #   console.log(annotation)
  #   # => {text: 'My comment', permissions: {...}}
  #
  # Returns nothing.
  addFieldsToAnnotation: (annotation) =>
    if annotation
      annotation.permissions = @options.permissions
      if @user
        annotation.user = @user

  # Public: Determines whether the provided action can be performed on the
  # annotation. This uses the user-configurable 'userAuthorize' method to
  # determine if an annotation is annotatable. See the default method for
  # documentation on its behaviour.
  #
  # Returns a Boolean, true if the action can be performed on the annotation.
  authorize: (action, annotation, user) ->
    user = @user if user == undefined

    if @options.userAuthorize
      return @options.userAuthorize.call(@options, action, annotation, user)

    else # userAuthorize nulled out: free-for-all!
      return true

  # Field callback: Updates the state of the "anyone can…" checkboxes
  #
  # action     - The action String, either "view" or "update"
  # field      - A DOM Element containing a form input.
  # annotation - An annotation Object.
  #
  # Returns nothing.
  updatePermissionsField: (action, field, annotation) =>
    field = $(field).show()
    input = field.find('input').removeAttr('disabled')

    # Do not show field if current user is not admin.
    field.hide() unless this.authorize('admin', annotation)

    # See if we can authorise without a user.
    if this.authorize(action, annotation || {}, null)
      input.attr('checked', 'checked')
    else
      input.removeAttr('checked')


  # Field callback: updates the annotation.permissions object based on the state
  # of the field checkbox. If it is checked then permissions are set to world
  # writable otherwise they use the original settings.
  #
  # action     - The action String, either "view" or "update"
  # field      - A DOM Element representing the annotation editor.
  # annotation - An annotation Object.
  #
  # Returns nothing.
  updateAnnotationPermissions: (type, field, annotation) =>
    annotation.permissions = @options.permissions unless annotation.permissions

    dataKey = type + '-permissions'

    if $(field).find('input').is(':checked')
      annotation.permissions[type] = []
    else
      # Clearly, the permissions model allows for more complex entries than this,
      # but our UI presents a checkbox, so we can only interpret "prevent others
      # from viewing" as meaning "allow only me to view". This may want changing
      # in the future.
      annotation.permissions[type] = [@user]

  # Field callback: updates the annotation viewer to inlude the display name
  # for the user obtained through Permissions#options.userString().
  #
  # field      - A DIV Element representing the annotation field.
  # annotation - An annotation Object to display.
  # controls   - A control Object to toggle the display of annotation controls.
  #
  # Returns nothing.
  updateViewer: (field, annotation, controls) =>
    field = $(field)

    # The annotation may have just been created
    # if it was then we just use the time for now
    # There might be a little drift but that's OK
    if annotation.updated?
      date = new Date(annotation.updated * 1000)
    else
      date = new Date()

    dateString = date.format('shortDate') + ' ' + date.format('shortTime')

    username = @options.userString annotation.user
    if annotation.user and username and typeof username == 'string'
      user = @options.userString(annotation.user)
      field.html(user + ' - ' + dateString).addClass('annotator-user')
    else
      field.remove()

    if controls
      controls.hideEdit()   unless this.authorize('update', annotation)
      controls.hideDelete() unless this.authorize('delete', annotation)

  # Sets the Permissions#user property on the basis of a received authToken.
  #
  # token - the authToken received by the Auth plugin
  #
  # Returns nothing.
  _setAuthFromToken: (token) =>
    this.setUser(token.userId)
