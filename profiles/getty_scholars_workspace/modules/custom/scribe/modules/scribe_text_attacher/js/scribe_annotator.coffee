# Scope in jQuery
$ = jQuery

# Add the annotator behavior
Drupal.behaviors.ScribeAnnotator =
  attach: (context, settings) ->
    # Set Permission Options
    perm_opts =
      user: Drupal.settings.scribe.username
      showViewPermissionsCheckbox: false
      showEditPermissionsCheckbox: false
      userAuthorize: (op, annotation, user) ->
        return annotation.permissions[op]

    # Initialize annotator
    Drupal.annotator = {}
    Drupal.annotator.text = $(context).find('.scribe-text-annotation .field-items').annotator()
    annotator = Drupal.annotator.text

    # Add Annotator Plugins
    plugins =
      EnhancedPosition: {}
      Threading: {}
      DrupalStore: {}
      DrupalPermissions: perm_opts


    for plugin, opts of plugins
      annotator.annotator('addPlugin', plugin, opts)
    # annotator.annotator('')
    # annotator.annotator('addPlugin', 'Threading')
    # annotator.annotator('addPlugin', 'DrupalStore')
    # annotator.annotator('addPlugin','DrupalPermissions', perm_opts)
