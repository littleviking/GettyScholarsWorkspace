(function ($) {
  var cropzooms = Array();
  var singlecropzoom;
  var basepath;

  var _self = null;
  Drupal.behaviors.lighttable = {
    attach: function () {
      // Get basepath from settings
      basepath = Drupal.settings.cropzoom.basepath;

      // Stuff to do onload. When do we want this to initialize? When they hit a 
      // certain path.
      var path = window.location.pathname;
      var pattern = /project\/\d+\/lighttable/i;

      if (path.match(pattern)) {
        Drupal.lighttable.initLightTable();
      }
      var cropzoom_path_pattern = /lighttable\/cropzoom\/\d+/;
      if (path.match(cropzoom_path_pattern)) {
        var img = $('#cropzoom-image img');
        var fid = path.match(/\d+/);

        singlecropzoom = Drupal.cropzoom.initCropZoom(img, 'cropzoom-f-' + fid);
        Drupal.lighttable.initCropZoomButtons();
      }
    }
  }
  Drupal.lighttable = Drupal.lighttable || {};

  Drupal.lighttable.initLightTable = function() {
    // Need to keep track of these arrays
    if (_self == null) {
      _self = {
        currentImages : [],
        recentImages : [],
        comparisonEnabled: false,
        display: 'grid',
        currentImagesCount: 0
      };
    }

    // Initialize the available images view
    Drupal.lighttable.initAvailableImages();
    Drupal.lighttable.setRecentImagesHeight();
  }

  Drupal.lighttable.initAvailableImages = function() {
    if (_self.display == 'list') {
      $('#lt-available-images .view-display-id-available_images_list_block').show();
      $('#lt-available-images .view-display-id-available_images_block').hide();
    }
    else {
      $('#lt-available-images .view-display-id-available_images_block').show();
      $('#lt-available-images .view-display-id-available_images_list_block').hide();
    }

    Drupal.lighttable.addOverlays();
    Drupal.lighttable.adjustDisplayToggle();

    // Initialize click handlers for exposed form
    $('#views-exposed-form-project-images-available-images-list-block #edit-submit-project-images').click(function(e) {
      if (e.originalEvent !== undefined) {
        // Copy form values
        $('#views-exposed-form-project-images-available-images-block #edit-combine').val($('#views-exposed-form-project-images-available-images-list-block #edit-combine').val());

        $('#views-exposed-form-project-images-available-images-list-block input[type=checkbox]').each(function() {
          if (this.checked) {
            $('#views-exposed-form-project-images-available-images-block #' + this.id).prop('checked', true);
          }
          else {
            $('#views-exposed-form-project-images-available-images-block #' + this.id).prop('checked', false);
          }
        });

        $('#views-exposed-form-project-images-available-images-block #edit-submit-project-images').triggerHandler('click');
      }
    });

    $('#views-exposed-form-project-images-available-images-block #edit-submit-project-images').click(function(e) {
      if (e.originalEvent !== undefined) {
        // Copy form values
        $('#views-exposed-form-project-images-available-images-list-block #edit-combine').val($('#views-exposed-form-project-images-available-images-block #edit-combine').val());

        $('#views-exposed-form-project-images-available-images-block input[type=checkbox]').each(function() {
          if (this.checked) {
            $('#views-exposed-form-project-images-available-images-list-block #' + this.id).prop('checked', true);
          }
          else {
            $('#views-exposed-form-project-images-available-images-list-block #' + this.id).prop('checked', false);
          }
        });

        $('#views-exposed-form-project-images-available-images-list-block #edit-submit-project-images').triggerHandler('click');
      }
    });

    // Initialize click handler for each image in the view
    $('.view-id-project_images .view-content .views-row').click(function() {
      var fid = $(this).find('.lighttable-image-container').attr('fid');

      // Only add to light table if it hasn't already been added
      if (_self.currentImages.indexOf(fid) == -1) {
        Drupal.lighttable.addToLightTable(fid);
      }
    });
    $('.view-id-project_images .view-content .views-row').draggable({
      revert: true,
      revertDuration: 0,
      helper: function(event) {
        var clone = $(this).clone();
        clone.find('.lighttable-image-container').remove();
        return clone;
      }
    });

    $('#lighttable').droppable({
      drop: function(event, ui) {
      console.log(ui.draggable.context);
      $(ui.draggable.context).click();
      }
    });

    // Unbind it first, otherwise it gets called multiple times
    $('#filter-toggle').unbind('click');
    $('#filter-toggle').click(function() {
      if ($(this).css('background-position') == '0px 0px') {
        $(this).css('background-position', '0px -12px');
      }
      else {
        $(this).css('background-position', '0px 0px');
      }

      $('#edit-tid-wrapper .form-type-select').slideToggle();
    });

    // Initialize display links in exposed filter
    $('.views-exposed-form-display-link').click(function() {
      if (_self.display != $(this).attr('display')) {
        // Adjust positioning of background elements
        _self.display = $(this).attr('display');
        Drupal.lighttable.loadDisplay($(this).attr('display'));
        Drupal.lighttable.adjustDisplayToggle();
      }
    });
  }

  Drupal.lighttable.adjustDisplayToggle = function() {
    if (_self.display == 'list') {
      $('.views-exposed-form-display-link').css('background-position-y', '-25px');
    }
    else {
      $('.views-exposed-form-display-link').css('background-position-y', '0px');
    }
  }

  Drupal.lighttable.addToLightTable = function(fid) {
    // Need to add this to the current images array
    var full_img, thumb_img;

    if (_self.currentImages[fid] == null) {
      if (_self.recentImages[fid] != null) {
        full_img = _self.recentImages[fid].full;
        thumb_img = _self.recentImages[fid].thumb;
      }
      else {
        full_img = $('#lt-available-images .view-display-id-available_images_block .lighttable-image-container-' + fid).clone();
        thumb_img = $('#lt-available-images .view-display-id-available_images_block .lighttable-thumb-container-' + fid).clone();
      }

      _self.currentImages[fid] = {full: full_img, thumb: thumb_img};
    }
    else {
      full_img = _self.currentImages[fid].full;
      thumb_img = _self.currentImages[fid].thumb;
    }

    if(_self.recentImages[fid] != null) {
      $('#lt-recent-images .lighttable-thumb-container-' + fid).remove();
      _self.recentImages[fid] = null;
    }

    // Append to light table, make draggable, and initialize in top left corner
    var img = $(full_img);

    $(img).draggable({
      containment: '#lighttable',
      drag: function(event, ui) {
        $('#lighttable .lighttable-image-container').css('z-index', '1');
        $(this).css('z-index', '150000');
      }
    }).resizable({
      aspectRatio: 'true',
      handles: 'all',
      create: function(event, ui) {
        var uiResizable = $(this).data('resizable');
        if (!uiResizable) {
          uiResizable = $(this).data('uiResizable');
        }
        if (uiResizable) {
          var handles = uiResizable.handles;
          for (var i in handles) {
            if (['ne', 'nw', 'sw', 'se'].indexOf(i) !== -1) {
              handles[i]
                .removeClass('ui-icon-gripsmall-diagonal-se')
                .addClass('ui-icon ui-icon-triangle-1-' + i);
            }
          }
        }
      }
    });

    $(img).attr('style', 'position: absolute; left: 0px; top: 0px; z-index: 3');

    // Add click handler for remove link
    $(img).find('.remove-link').click(function() {
      var fid = $(this).parents('.lighttable-image-container').attr('fid');
      Drupal.lighttable.removeFromLightTable(fid);
    });

   // Add click handler for crop link
   $(img).find('.crop-link').click(function() {
      var fid = $(this).parents('.lighttable-image-container').attr('fid');
      var nid = $(this).parents('.lighttable-image-container').attr('nid');
      var imgelement = $(img).find('img');

      var czid = 'cropzoom-f-' + fid;

      // We have to keep track of each of the cropzoom objects that are created
      var cz = Drupal.cropzoom.initCropZoom(imgelement, czid);
      cropzooms[fid] = cz;

      $('.lighttable-crop-links-' + czid).show();
      $('.lighttable-links-' + czid).hide();


      // Switch where bottom border is displayed
      $('.lighttable-full-image-' + fid).css('border-bottom', 'solid 1px #000');
      $('.lighttable-full-image-' + fid + ' img').css('border-bottom', 'none');

      // Attach a handler to the cancel
      $('.lighttable-crop-links-' + czid + ' .crop-cancel-link').click(function() {
        Drupal.lighttable.cancelCrop(fid);
      });

      $('.lighttable-crop-links-' + czid + ' .crop-save-link').click(function() {
        Drupal.lighttable.crop(fid, nid, -1);
      });

      // Disable dragging when cropping tools are enabled in IE8.
      if ($.browser.msie && $.browser.version == '8.0') {
        $(img).draggable('disable');
        $(img).css('opacity', '1');
      }
    });

    $(img).find('.crop-link-modal').click(function() {
      var img_obj = $(img).find('img');
      var fid = $(this).attr('fid');
      var nid = $(this).attr('nid');

      // Account for width of zoom slider and padding
      var width = Math.max(parseInt(img.attr('full-width')) + 30, 630);
      // Account for height of crop buttons
      var height = parseInt(img.attr('full-height')) + 120;

      window.open('http://' + window.location.host + basepath + 'lighttable/cropzoom/' + fid + '/' + nid, '', 'scrollbars=yes,height=' + height + ',width=' + width);
    });

    $('#lighttable').append(img);

    _self.currentImagesCount++;

    // Add overlay to the proper spot
    Drupal.lighttable.addOverlay(fid);
  }

  Drupal.lighttable.addOverlay = function(fid) {
    Drupal.lighttable.addOverlayList(fid);
    Drupal.lighttable.addOverlayGrid(fid);

    // Check if we should enable the comparisons link
    if (!_self.comparisonEnabled && _self.currentImagesCount >= 2) {
      Drupal.lighttable.enableComparison();
    }
  }

  Drupal.lighttable.addOverlayGrid = function(fid) {
    if ($('.view-display-id-available_images_block .removed-image-' + fid).length == 0) {
      // Need it to be visible so we can grab the elements properly
      if ($('#lt-available-images .view-display-id-available_images_block').is(':visible')) {
        wasHidden = false;
      }
      else {
        wasHidden = true;
        $('#lt-available-images .view-display-id-available_images_block').show();
      }

      var container = $('.view-display-id-available_images_block .lighttable-image-container-' + fid).parent();
      var h = $(container).height();
      var w = $(container).width();

      $(container).prepend('<div class="removed-image removed-image-' + fid + '" style="width:' + w + 'px;height:' + h + 'px;"></div>');
      $(container).css('cursor', 'default');

      if (wasHidden) {
        $('#lt-available-images .view-display-id-available_images_block').hide();
      }
    }
  }

  Drupal.lighttable.addOverlayList = function(fid) {
    if ($('.view-display-id-available_images_list_block .removed-image-' + fid).length == 0) {
      // Need it to be visible so we can grab the elements properly
      if ($('#lt-available-images .view-display-id-available_images_list_block').is(':visible')) {
        wasHidden = false;
      }
      else {
        wasHidden = true;
        $('#lt-available-images .view-display-id-available_images_list_block').show();
      }

      var container = $('.view-display-id-available_images_list_block .views-row-' + fid);
      if (container.length > 0) {
        var h = $(container).outerHeight();
        var w = $(container).outerWidth();

        $(container).find('td:first').prepend('<div class="removed-image removed-image-' + fid + '" style="width:' + w + 'px;height:' + h + 'px;left:' + $(container).position().left + 'px;top:' + $(container).position().top + 'px;"></div>');
        $(container).css('cursor', 'default');

        if (wasHidden) {
          $('#lt-available-images .view-display-id-available_images_list_block').hide();
        }
      }
    }
  }

  Drupal.lighttable.removeFromLightTable = function(fid) {
    _self.currentImagesCount--;
    var currentIndex = _self.currentImages.indexOf(fid);

    if (_self.display == 'list') {
      viewDisplay = '.view-display-id-available_images_list_block';
    }
    else {
      viewDisplay = '.view-display-id-available_images_block';
    }

    if (_self.currentImages[fid] != null && _self.recentImages[fid] == null) {
      // Add back the cursor pointer for the container
      $('.removed-image-' + fid).parent().css('cursor', 'pointer');

      // Remove overlay
      $('.removed-image-' + fid).remove();

      // Add thumb to recent. Also make sure it has proper click handler
      $('#lighttable .lighttable-image-container .lighttable-thumb-container-' + fid).show();

      // Get thumb from current images
      var thumb = $(_self.currentImages[fid].thumb).clone();

      thumb.click(function() {
        Drupal.lighttable.addToLightTable(fid);
      });

      $('#lighttable .lighttable-image-container-' + fid).remove();


      // Add it to recent images array
      _self.recentImages[fid] = _self.currentImages[fid];

      // Remove it from current images array
      _self.currentImages[fid] = null;

      $('#lighttable .lighttable-thumb-container-' + fid).hide();

      if (_self.comparisonEnabled && _self.currentImagesCount < 2) {
        Drupal.lighttable.disableComparison();
      }
    }
  }

  Drupal.lighttable.enableComparison = function() {
    _self.comparisonEnabled = true;

    $('#make-comparison').css('background-color', '#fff');
    $('#make-comparison').css('color', '#000');
    $('#make-comparison').css('cursor', 'pointer');

    $('#make-comparison').click(function() {
      var fids_string = JSON.stringify(Drupal.lighttable.getCurrentIds());
      var href = location.pathname.replace(Drupal.settings.basePath, "");
      var gid = href.match(/\d+/);

      $.post(basepath + "lighttable/comparison/" + gid, {'fids': fids_string}, function(nid) {
        if (Drupal.cropzoom.isNumber(nid)) {
          window.location = basepath + 'node/' + nid + '/edit';
        }
      });

    });
  }

  Drupal.lighttable.disableComparison = function() {
    _self.comparisonEnabled = false;

    $('#make-comparison').css('background-color', '#ccc');
    $('#make-comparison').css('color', '#999');
    $('#make-comparison').css('cursor', 'default');

    $('#make-comparison').unbind('click');
  }

  Drupal.lighttable.cancelCrop = function(fid) {
    var czid = 'cropzoom-f-' + fid;
    var imgelement = $('#lighttable .lighttable-full-image-' + fid + ' img');

    Drupal.cropzoom.removeCropZoom(imgelement, czid);
    // Make sure this is draggable
    $('#lighttable .lighttable-image-container-' + fid).draggable('enable');
    $('#zoomslider-' + czid).html('');

    // Hide crop links and show regular links
    $('#lighttable .lighttable-crop-links-cropzoom-f-' + fid).hide();
    $('#lighttable .lighttable-links-cropzoom-f-' + fid).show();

    // Switch where bottom border is displayed
    $('.lighttable-full-image-' + fid).css('border-bottom', 'none');
    $('.lighttable-full-image-' + fid + ' img').css('border-bottom', 'solid 1px #000');
  }

  Drupal.lighttable.crop = function(oldfid, nid, gid) {
    Drupal.cropzoom.showSpinner();

    if (gid == -1) {
      gid = location.href.split('/').pop();
    }

    singlecropzoom.send(basepath + 'cropzoom/crop/' + gid, 'POST', {}, function(parts){
      var partsArray = parts.split('/');
      $.post(basepath + "cropzoom/create/" + gid, {'ts' : partsArray[0], 'ext' : partsArray[1], 'nid' : nid, 'type' : 'image'}, function(ret) {
        if (ret != '0') {
          var ids = jQuery.parseJSON(ret);
          if (ids.nid && Drupal.cropzoom.isNumber(ids.nid)) {
            var imagePath = window.location.protocol + "//" + window.location.host + basepath + 'node/' + ids.nid + '/edit';
            alert('A new image has been created. It can be edited at ' + imagePath);
          }
          if (ids.fid && Drupal.cropzoom.isNumber(ids.fid)) {
            // Load new file in parent window
            window.opener.Drupal.lighttable.loadNewFile(oldfid, ids.fid);
            window.close();
          }

        }
        else {
          Drupal.cropzoom.removeSpinner();
          alert("Unable to crop image. Please try again, or contact an administrator.");
        }
      });
    });
  }

  Drupal.lighttable.loadNewFile = function(oldfid, newfid) {
    // Move old file into recent.
    Drupal.lighttable.removeFromLightTable(oldfid);

    // Reload display
    Drupal.lighttable.reloadDisplay(newfid);
  }

  Drupal.lighttable.loadDisplay = function(display) {
    _self.display = display;
    Drupal.lighttable.reloadDisplay();
  }

  Drupal.lighttable.reloadDisplay = function(newfid) {
    if (Drupal.cropzoom.isNumber(newfid)) {
      var gid = location.href.match(/\d+/);

      $.post(basepath + "lighttable/available-images/" + gid, {}, function(ret) {
        var displays = jQuery.parseJSON(ret);

        var grid = $(displays.grid);
        var list = $(displays.list);

        // just reload content, not the exposed filter
        $('#lt-available-images .view-display-id-available_images_block .view-content').html($(grid).find('.view-content').html());
        $('#lt-available-images .view-display-id-available_images_list_block .view-content').html($(list).find('.view-content').html());

        // clear out the current filter, if there are any
        $('#edit-combine').val('');
        $('input:checkbox').prop('checked', false);

        Drupal.lighttable.addToLightTable(newfid);

        if (_self.display == 'grid') {
          $('#lt-available-images .view-display-id-available_images_list_block').hide();
          $('#lt-available-images .view-display-id-available_images_block').show();
        }
        else {
          $('#lt-available-images .view-display-id-available_images_block').hide();
          $('#lt-available-images .view-display-id-available_images_list_block').show();
        }
        Drupal.lighttable.initLightTable();
      });
    }
    else {
      if (_self.display == 'grid') {
        $('#lt-available-images .view-display-id-available_images_list_block').hide();
        $('#lt-available-images .view-display-id-available_images_block').show();
      }
      else {
        $('#lt-available-images .view-display-id-available_images_block').hide();
        $('#lt-available-images .view-display-id-available_images_list_block').show();
      }
    }
  }

  Drupal.lighttable.setRecentImagesHeight = function() {
    // Set height for recent images
    var ltHeight = $('#lighttable').outerHeight(true);
    var ltWidth = $('#lighttable').outerWidth();
    var ltViewHeight = $('.view-id-project_images').outerHeight();
    var makeComparisonHeight = $('#make-comparison').outerHeight(true);

    $('#lt-recent-images').css('height', ltHeight + ltViewHeight - makeComparisonHeight);
    $('.view-id-project_images').css('width', ltWidth);
  }

  Drupal.lighttable.addOverlays = function() {
    for (i = 0; i < _self.currentImages.length; i++) {
      if (_self.currentImages[i] != null) {
        Drupal.lighttable.addOverlay(i);
      }
    }
  }

  Drupal.lighttable.getCurrentIds = function() {
    var currentIds = [];
    for (var key in _self.currentImages) {
      if (_self.currentImages[key] != null) {
        currentIds.push(key);
      }
    }
    return currentIds;
  }

  Drupal.lighttable.initCropZoomButtons = function() {
    $('.btn-cropzoom-cancel').click(function() {
      window.close();
    });

    $('.btn-cropzoom-crop').click(function() {
      var nid = $(this).attr('nid');
      var gid = $(this).attr('gid');
      var fid = $(this).attr('fid');

      Drupal.lighttable.crop(fid, nid, gid);
    });
  }

})(jQuery);
