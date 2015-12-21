(function ($) {
  Drupal.behaviors.bibliography_reference = {
    attach: function () {
      // Add image to WYSIWYG box when image is clicked
      $('.views-row').click(function () {
        var html = $(this).text();
        Drupal.bibliography_reference.addReference(html);
      });
    }
  }
  Drupal.bibliography_reference = Drupal.bibliography_reference || {};

  Drupal.bibliography_reference.QueryString = function () {
    // This function is anonymous, is executed immediately and 
    // the return value is assigned to QueryString!
    var query_string = {};
    var query = window.location.search.substring(1);
    var vars = query.split("&");
 
    for (var i = 0; i < vars.length; i++) {
      var pair = vars[i].split("=");
        // If first entry with this name
      if (typeof query_string[pair[0]] === "undefined") {
        query_string[pair[0]] = pair[1];
        // If second entry with this name
      } else if (typeof query_string[pair[0]] === "string") {
        var arr = [ query_string[pair[0]], pair[1] ];
        query_string[pair[0]] = arr;
        // If third or later entry with this name
      } else {
        query_string[pair[0]].push(pair[1]);
      }
    } 
    return query_string;
  }
  
  Drupal.bibliography_reference.addReference = function(html) {
    var instanceId = Drupal.bibliography_reference.QueryString().instanceID;

    window.opener.ParentFunction(instanceId, html);
    window.close();
  }

})(jQuery);
