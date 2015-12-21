(function ($) {
  Drupal.behaviors.project_dashboard = {
    attach: function () {
      if (typeof $.expander != 'undefined') {
        $('#dashboard-description').expander({
          slicePoint: 50000,
          expandEffect: 'show',
          expandSpeed: 0,
          collapseEffect: 'hide',
          collapseSpeed: 0
        });

        $('#dashboard-description').show();
      }
      

      $('.flexslider').flexslider({
        animation: "slide",
        animationLoop: true,
        itemWidth: 115,
        itemMargin: 15,
        slideshow: false,
        smoothHeight: false
      });

  
/*      $('#my-projects-link').mouseenter(function() {
        $('#my-projects-submenu').slideDown();
      });

      $('#my-projects-submenu').mouseleave(function() {
         $('#my-projects-submenu').slideUp();
      });*/

        //Better Hover and mouseleave for the project menu
        var timer;

        if ($("#my-projects").length > 0) {
          $("#my-projects").bind("mouseover", function() {
              clearTimeout(timer);
              openSubmenu();
          }).bind("mouseleave", function() {
              timer = setTimeout(
                  closeSubmenu
                  , 500);
          });
        }

        function openSubmenu() {
            $("#my-projects-submenu").addClass("open");
        }
        function closeSubmenu() {
            $("#my-projects-submenu").removeClass("open");
        }

      $('#create-content-link').mouseenter(function() {
        $('#create-content-submenu').slideDown();
      });

      $('#create-content-submenu').mouseleave(function() {
         $('#create-content-submenu').slideUp();
      });
    }
  }

})(jQuery);
