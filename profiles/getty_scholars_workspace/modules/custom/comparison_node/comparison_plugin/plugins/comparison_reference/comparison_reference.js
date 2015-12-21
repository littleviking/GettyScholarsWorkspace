(function ($) {

// @todo Array syntax required; 'comparison_reference' is a predefined token in JavaScript.
Drupal.wysiwyg.plugins['comparison_reference'] = {

  /**
   * Return whether the passed node belongs to this plugin.
   */
  isNode: function(node) {
    return ($(node).is('.comparison_reference'));
  },

  /**
   * Execute the button.
   */
  invoke: function(data, settings, instanceId) {
    // Check that we are on a node edit page
    var path = window.location.pathname;
    var view_node_path = /node\/[0-9]+/i;
    var comment_reply_path = /comment\/reply\/[0-9]+/i;
    var create_node_path = /node\/add\/\w+\/[0-9]+/;
    var match = '';
    if (path.match(view_node_path) || path.match(create_node_path)) {
      var nid = $('#edit-og-group-ref-und-0-default').val();
    }
    else if (path.match(comment_reply_path)) {
      var match = path.match(comment_reply_path)['input'];
      var nid = match.replace(Drupal.settings.basePath+"comment/reply/", "");
    }
    // else {
    //   alert('This button is not eligible for this page.');
    // }
    if (typeof nid == 'undefined') {
      var nid = '';
    }

    var url = Drupal.settings.basePath+"comparison/reference/" + nid + "?instanceID=" + instanceId;
    window.open(url, "", "width=400,height=300,location=0");
  },

  /**
   * Do something when the WYSIWYG is attached
   */
  attach: function(content, settings, instanceId) {
    content = content.replace(/<!--break-->/g, "yup");
    return content;
  },

  /**
   * Do something when the WYSIWYG is detached
   */
  detach: function(content, settings, instanceId) {
    var $content = $('<div>' + content + '</div>'); // No .outerHTML() in jQuery :(
    return $content.html();
  }
};

})(jQuery);

function ParentFunction(val, content) {
  Drupal.wysiwyg.instances[val].insert(content);
}
