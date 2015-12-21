
$ = jQuery

class Drupal.ScribeRest
  settings = Drupal.settings.scribe

  # Maps various resources to their RESTful endpoints
  resources:
    attachment: Drupal.settings.basePath + 'scribe_attachment.json'
    annotation: Drupal.settings.basePath + 'scribe_annotation.json'
    taxonomy_term: Drupal.settings.basePath + 'taxonomy_term.json'

  # Maps various reources to their id key
  id_map:
    scribe_attachment: 'attachment_id'
    scribe_annotation: 'annotation_id'
    taxonomy_term: 'tid'

  methods:
    read: 'GET'
    create: 'POST'
    update: 'PUT'
    destroy: 'DELETE'
    list: 'GET'

  constructor: () ->
    @settings = Drupal.settings.scribe

  getAnnotation: (id) ->
    ajaxRequest('annotation')



  ajaxOpts: (method) ->
    http_method = @methods[method]

    # Setup CSRF header required by Rest WS
    headers =
      'X-CSRF-Token': @settings.csrf_token

    # Set up initial options
    opts = {
      type:       http_method,
      headers:    headers,
      dataType:   "json",
    }

    opts

  # Retrieve list of existing tags
  # Give an array of tags as a string
  getExistingTags: (tags) ->
    result = @ResourceList('taxonomy_term', {name: tags})


  # Given a list of tags, create new ones for any
  # that do not currently existing, returning the
  # entire merged list
  createNewTags: (tags, final) ->
    # Get tags that already exist
    response = @ResourceList('taxonomy_term', {name: tags})
    response.done (data) =>
      # Retrieve the old tags
      old_tags = (tag.name for tag in data.list)

      # Get only the new tags
      new_tags = (tag for tag in tags when (tag not in old_tags))

      # Create the new tags via Ajax calls
      done = []
      for tag in new_tags
        result = @createTag(tag)
        done.push result

      # Collalate together all the results
      tag_list = data.list
      $.when.apply(@, done).then((data...) ->
        for tag in data
          tag_list.push tag[0]
      ).then(() ->
        final(tag_list)
      )

  final: (tag_list) ->
    console.dir(tag_list)


    # Go through the list of tags
    # Creating new tags for ones that
    # don't already exist

    # Return the combined list

  # Create a single new taxonomy term
  createTag: (name, machine_name = 'tags', vid = 1) ->
    tag =
      name: name
      machine_name: machine_name
      vocabulary:
        id: vid

    @ResourceRequest('taxonomy_term', 'create', tag)


  # Retrieve a list of resources based
  # on various criteria
  ResourceList: (resource, filters = {}) ->
    list = {}
    response = @ResourceRequest(resource, 'list', filters)
    $.when(response).then((data) ->
      list = data.list
    )

  # Send a request to a resource endpoint
  ResourceRequest: (resource, method, data = {}, id = 0) ->
    if id
      url = @resources[resource] + '/' + id
    else
      url = @resources[resource]


    # We turn the data into JSON
    # unless we're getting a listing
    if method != 'list'
      end_data = JSON.stringify(data)
    else
      end_data = data

    opts = @ajaxOpts(method)
    $.extend(opts, {
      data: end_data
      contentType: "application/json; charset=utf-8"
    })

    # console.dir(opts)

    $.ajax(url, opts)

  RequestProcessResponse: (data) ->
    console.dir 'called'

  # Reutn a list of results that have been processed
  RequestProcessList: (data) ->
    console.log 'called'
    console.dir data.list
    data.list

  RequestError: (data) ->
    console.dir data
