(function ($) {
  Drupal.behaviors.project_image_reference = {
    attach: function () {
      // Add image to WYSIWYG box when image is clicked
      $('.project-image').click(function () {
        var uri = $(this).attr('uri');
        var alt = $(this).find('img').attr('alt');
        var caption = $(this).parents('.views-row').find('.views-field-caption .field-content').html();
        Drupal.project_image_reference.addImage(uri, alt, caption);

      });
    }
  }
  Drupal.project_image_reference = Drupal.project_image_reference || {};

  Drupal.project_image_reference.QueryString = function () {
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
  
  Drupal.project_image_reference.addImage = function(uri, alt, caption) {
    var instanceId = Drupal.project_image_reference.QueryString().instanceID;
    caption = $('<div/>').html(caption).text();
    // Default to float left and have 10px margin.
    var html = '<div style="float:left;margin:10px;"><img src="' + uri + '" alt="' + alt + '" title="' + alt + '" />' + caption + '</div>';

    window.opener.ParentFunction(instanceId, html);
    window.close();
  }

})(jQuery);