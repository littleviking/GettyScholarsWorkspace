/**
 * @file
 * Integration with cropzoom library, and provide functionality for displayed
 * buttons.
 */

(function ($) {
  var cropzoom;
  var basepath;
  Drupal.behaviors.cropzoom = {
    attach: function () {
      // Get basepath from settings
      basepath = Drupal.settings.cropzoom.basepath;

      // set the height for each cropzoom container based on its image
      $('.cropzoom-container').each(function (index) {
        var img = $(this).find('.cropzoom-image');
        $(this).height(img.height() + 140);
      });

      $('.btn-cropzoom').click(function() {
        if (!$(this).hasClass('button-disabled')) {
          $(this).addClass('button-disabled');
          $(this).siblings('.zoomslider').show();

          // Initialize the cropzoom tool
          var img = $(this).siblings('.cropzoom-image-container').find('.cropzoom-image');

          // If annotations are enabled on the image then disable it
          try {
            Drupal.annotator.image.data('annotator').plugins.ImageAnnotator.disableAnnotator(img);
          }
          catch (e) {
            // We do nothing here, if image annotator isn't there it's fine
          }

          var fid = $(this).attr('fid');
          Drupal.cropzoom.initCropZoom(img, 'cropzoom-f-' + fid);
        }
      });

      $('.btn-cropzoom-copy').click(function() {
        if (!$(this).hasClass('button-disabled')) {
          $(this).addClass('button-disabled');
          $(this).siblings('.btn-cropzoom-cancel').addClass('button-disabled');

          // Create copy of this node
          var nid = $(this).attr('nid');
          var gid = $(this).attr('gid');
          var fid = $(this).attr('fid');
          Drupal.cropzoom.createNode(nid, gid, fid);
        }
      });

      $('.btn-cropzoom-cancel').click(function() {
        if (!$(this).hasClass('button-disabled')) {
          $(this).removeClass('button-disabled');
          $(this).siblings('.btn-cropzoom-cancel').removeClass('button-disabled');
          $(this).parentsUntil('cropzoom-image-container').siblings('.zoomslider').hide();

          // Remove the cropzoom
          var img = $(this).parentsUntil('cropzoom-image-container').siblings('.cropzoom-image-container').find('.cropzoom-image');
          var czid = 'cropzoom-f-' + $(this).attr("fid");

          Drupal.cropzoom.removeCropZoom(img, czid);

          // If the image annotator is there then re-enable it
          try {
            Drupal.annotator.image.data('annotator').plugins.ImageAnnotator.enableAnnotator(img);
          }
          catch (e) {
            // Again, nothing to do here if it isn't enabled
          }
        }
      });
    }
  }

  Drupal.cropzoom = Drupal.cropzoom || {};
  Drupal.cropzoom.initCropZoom = function(img, czid) {
    var imgsrc = img.attr('src');

    cropzoom = $('#' + czid).cropzoom({
      width:img.attr('width'),
      height:img.attr('height'),
      bgColor: '#CCC',
      enableRotation:false,
      enableZoom:true,
      zoomSteps:10,
      expose:{
        slidersOrientation: 'horizontal',
        zoomElement: '#zoomslider-' + czid,
      },
      selector:{
        centered:true,
        borderColor:'red',
        borderColorHover:'red',
        w:10,
        h:10,
        showDimetionsOnDrag:false,
        showPositionsOnDrag:false
      },
      image:{
        source:imgsrc,
        width:img.attr('width'),
        height:img.attr('height'),
        maxZoom:500,
        minZoom:100,
        startZoom:100,
        useStartZoomAsMinZoom:true,
        snapToContainer:true
      }
    });

    // Initialize the selector to be in the middle and half the size of the original image
    cropzoom.setSelector((img.attr('width') / 4), (img.attr('height') / 4), (img.attr('width') / 2), (img.attr('height') / 2), false);

    // This is so that the selector renders properly in IE
    $('#' + czid + '_selector').css('background', 'url(/' + Drupal.settings.cropzoom.path + '/images/pixel.png) repeat');

    // Hide the original image
    $(img).hide();

    // Adjust display of buttons
    $(img).parentsUntil('cropzoom-image-container').siblings('.cropzoom-buttons').show();
    
    // Add clearing to the next div after this one
    $(img).parentsUntil('field').next().css('clear', 'both');

    $('.cropholder image').mousedown(function() {
      $(this).addClass('cursordown');
    });
    $('.cropholder image').mouseup(function() {
      $(this).removeClass('cursordown');
    });

    return cropzoom;
  }

  Drupal.cropzoom.removeCropZoom = function(img, czid) {
    $(img).show();

    $('#' + czid).html('');
    $('#' + czid).attr('style', '');

    // Adjust display of buttons
    $('#' + czid).siblings('.cropzoom-buttons').find('.button').removeClass('button-disabled');
    $('#' + czid).siblings('.cropzoom-buttons').hide();
    $('#' + czid).siblings('.btn-cropzoom').removeClass('button-disabled');
  }

  Drupal.cropzoom.createNode = function(nid, gid, fid) {
    Drupal.cropzoom.showSpinner();
    cropzoom.send(basepath + 'cropzoom/crop/' + gid, 'POST', {}, function(parts){
      if (parts == "0") {
        alert('Unable to crop image. Please try again, or contact an administrator.');
      }
      else {
        var partsArray = parts.split('/');
        $.post(basepath + "cropzoom/create/" + gid, {'nid': nid, 'ts' : partsArray[0], 'ext' : partsArray[1]}, function(ret) {
          var ids = jQuery.parseJSON(ret);

          if (ids.nid && Drupal.cropzoom.isNumber(ids.nid)) {
            window.location = basepath + 'node/' + ids.nid + '/edit';
          }
          else {
            Drupal.cropzoom.removeSpinner();
            
            var img = $('.cropzoom-image-container-' + fid).find('.cropzoom-image');
            var czid = 'cropzoom-f-' + fid;
            Drupal.cropzoom.removeCropZoom(img, czid);

            alert("Unable to crop image. Please try again, or contact an administrator.");
          }
        });
      }
    });
  }

  Drupal.cropzoom.showSpinner = function() {
    // Add spinner div to body
    $('body').prepend('<div id="spinner"></div>');
    // Add overlay to body
    $('body').addClass('cropzoom-overlay');

    // Set height and width of spinner
    $('#spinner').height($('body').height());
    $('#spinner').width($('body').width());

    // Add spinner
    var opts = {
      lines: 12, // The number of lines to draw
      length: 7, // The length of each line
      width: 4, // The line thickness
      radius: 10, // The radius of the inner circle
      color: '#000', // #rbg or #rrggbb
      speed: 1, // Rounds per second
      trail: 60, // Afterglow percentage
      shadow: false // Whether to render a shadow
    };
    var target = document.getElementById('spinner');
    var spinner = new Spinner(opts).spin();
    target.appendChild(spinner.el);

    // Position the div that holds the spinner
    var spinner_top = $('body').height() / 2;
    var spinner_left = $('body').width() / 2;
    $('#spinner div').first().attr('style', 'position:fixed;top:' + spinner_top + 'px;left:' + spinner_left + 'px;');
  }

  Drupal.cropzoom.removeSpinner = function() {
    $('#spinner').remove();
    $('body').removeClass('cropzoom-overlay');
  }

  Drupal.cropzoom.isNumber = function(n) {
    return !isNaN(parseFloat(n)) && isFinite(n);
  }

})(jQuery);
