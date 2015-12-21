(function ($) {

// @todo Array syntax required; 'comparison_reference' is a predefined token in JavaScript.
Drupal.wysiwyg.plugins['bibliography_reference'] = {

  /**
   * Return whether the passed node belongs to this plugin.
   */
  isNode: function(node) {
    return ($(node).is('.bibliography_reference'));
  },

  /**
   * Execute the button.
   */
  invoke: function(data, settings, instanceId) {
    // Check that we are on a node edit or create page
    var path = window.location.pathname;
    var view_node_path = /node\/[0-9]+/;
    var create_node_path = /node\/add\/\w+\/[0-9]+/;
    var gid = false;
    
    var match = '';
    if (path.match(view_node_path)) {
      match = path.match(view_node_path)['input'];
      gid = Drupal.settings.ogContext.gid;
    }
    else if (path.match(create_node_path)) {
      gid = $('#edit-og-group-ref-und-0-default').val();
    }
    else {
      alert('This button is not eligible for this page.');
    }

    if (!isNaN(parseFloat(gid)) && isFinite(gid)) {
      // this is where we will open the URL
      var url = Drupal.settings.basePath+"bibliography-reference/list/" + gid + "?instanceID=" + instanceId;
      window.open(url, "", "width=400,height=300,location=0,scrollbars=yes");
    }
    else {
      alert("Invalid project. Unable to retrieve project images.");
    }
  },

  /**
   * Do something when the WYSIWYG is attached
   */
  attach: function(content, settings, instanceId) {
    content = content.replace(/<!--break-->/g, "");
    return content;
  },

  /**
   * Do something when the WYSIWYG is detached
   */
  detach: function(content, settings, instanceId) {
    var $content = $('<div>' + content + '</div>');
    return $content.html();
  }
};

})(jQuery);

function ParentFunction(val, content) {
  Drupal.wysiwyg.instances[val].insert(content);
}
