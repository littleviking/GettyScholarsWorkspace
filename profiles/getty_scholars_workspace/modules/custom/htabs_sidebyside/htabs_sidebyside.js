(function($) {
  Drupal.behaviors.htabsSelectSecondTab = {
    attach: function(context, settings) {
      $clone = $('.side-by-side-row .clone', context);
      $('.horizontal-tabs-list').height($('.horizontal-tabs-list').height());
      $('.side-by-side-row').find('input, textarea, select').change(function() {
        $('[name="' + $(this).attr('name') + '"]').val($(this).val());
      });
    }
  };
})(jQuery);
