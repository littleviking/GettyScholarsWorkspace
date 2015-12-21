<div class="cropzoom-image-container cropzoom-image-container-<?php print $fid; ?>">
  <?php print $image_output; ?>
</div>
<div id="<?php print $czid; ?>" class="cropholder cropholder-<?php print $czid; ?>"></div>
<div id="zoomslider-<?php print $czid; ?>" class="zoomslider"></div>
<?php if (isset($nid)): ?>
<div class="cropzoom-buttons">
  <div class="btn-cropzoom-copy button" gid="<?php print $gid; ?>" nid="<?php print $nid; ?>" fid="<?php print $fid; ?>">Crop</div>
  <div class="btn-cropzoom-cancel button" nid="<?php print $nid ?>" fid="<?php print $fid; ?>">Cancel</div>
</div>
<?php endif; ?>