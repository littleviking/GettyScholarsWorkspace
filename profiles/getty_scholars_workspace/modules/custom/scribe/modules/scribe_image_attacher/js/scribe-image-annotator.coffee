# Scope in jQuery
$ = jQuery

# Add the annotator behavior
Drupal.behaviors.ScribeImageAnnotator =
  attach: (context, settings) ->
    # Set Permission Options
    perm_opts =
      user: Drupal.settings.scribe.username
      showViewPermissionsCheckbox: false
      showEditPermissionsCheckbox: false
      userAuthorize: (op, annotation, user) ->
        return annotation.permissions[op]


    # Initialize annotator
    Drupal.annotator.image = $('.scribe-image-annotation .field-items').annotator()
    annotator = Drupal.annotator.image

    # Add plugins
    annotator.annotator('addPlugin', 'ImageAnnotator')
    annotator.annotator('addPlugin', 'Threading')
    annotator.annotator('addPlugin', 'DrupalStoreImage')
    annotator.annotator('addPlugin','DrupalPermissions', perm_opts)
