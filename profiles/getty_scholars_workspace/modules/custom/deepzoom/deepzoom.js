(function($) {
  Drupal.behaviors.deepzoom = {
    attach: function(context, settings) {
      $('.deepzoom').once('deepzoom', function() {
      	OpenSeadragon({
	        id: this.id,
	        prefixUrl: settings.openseadragon.image_path,
	        tileSources: $(this).data('deepzoom-dzi')
	    });
      });
    }
  };
})(jQuery);
