<div id="cropzoom-image"><img src="<?php print $path; ?>" width="<?php print $width; ?>" height="<?php print $height; ?>" /></div>
<div id="cropzoom-f-<?php print $file->fid; ?>"></div>
<div id="zoomslider-cropzoom-f-<?php print $file->fid; ?>"></div>

<?php if (isset($nid)): ?>
<div class="cropzoom-buttons">
  <div class="btn-cropzoom-crop button" gid="<?php print $gid; ?>" nid="<?php print $nid; ?>" fid="<?php print $file->fid; ?>">Crop</div>
  <div class="btn-cropzoom-cancel button">Cancel</div>
</div>
<?php endif; ?>