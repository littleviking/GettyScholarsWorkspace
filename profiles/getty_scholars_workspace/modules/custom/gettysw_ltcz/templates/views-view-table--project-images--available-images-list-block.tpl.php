<?php

/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $caption: The caption for this table. May be empty.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */
  // These fields from the view are not displayed
  $hidden_fields = array('fid', 'field_image_1');
?>
<table <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
   <?php if (!empty($title) || !empty($caption)) : ?>
     <caption><?php print $caption . $title; ?></caption>
  <?php endif; ?>
  <thead>
    <tr>
      <?php foreach ($header as $field => $label): ?>
        <?php if (!in_array($field, $hidden_fields)): ?>
        <th <?php if ($header_classes[$field]) { print 'class="'. $header_classes[$field] . '" '; } ?>>
          <?php print $label; ?>
        </th>
        <?php endif; ?>
      <?php endforeach; ?>
    </tr>
  </thead>
  <tbody>
    <?php foreach ($rows as $row_count => $row): ?>
      <?php
        $fid = $row['fid'];
        $czid = 'cropzoom-f-' . $fid;
        $full_dimensions = explode('|', strip_tags($row['field_image_2']));
      ?>
      <tr <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .' views-row views-row-' . $fid . '"';  } ?>>
        <?php foreach ($row as $field => $content): ?>
          <?php if (!in_array($field, $hidden_fields)): ?>
          <td <?php if ($field_classes[$field][$row_count]) { print 'class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
            <?php if ($field == 'field_image'): ?>
              <div class="lighttable-image-container lighttable-image-container-<?php print $fid; ?>" fid="<?php print $fid; ?>" full-width="<?php print $full_dimensions[0]; ?>" full-height="<?php print $full_dimensions[1]; ?>">
                <div class="lighttable-full-image lighttable-full-image-<?php print $fid; ?>" class="borderbottom"><?php print $row['field_image_1']; ?></div>
                <div class="lighttable-links lighttable-links-<?php print $czid; ?>">
                  <div class="crop-link-modal">CROP</div>
                  <div class="remove-link">REMOVE</div>
                </div>
              </div>
              <div class="lighttable-thumb-container lighttable-thumb-container-<?php print $fid; ?>" fid="<?php print $fid; ?>">
                <div class="lighttable-thumb lighttable-thumb-<?php print $fid; ?>"><?php print $content; ?></div>
              </div>
            <?php else: ?>
              <?php print $content; ?>
            <?php endif; ?>
          </td>
          <?php endif; ?>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>