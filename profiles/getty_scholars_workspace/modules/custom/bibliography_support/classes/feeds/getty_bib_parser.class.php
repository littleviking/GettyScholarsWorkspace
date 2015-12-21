<?php

/**
 *  @class:
 *    Class provides a custom parser for biblio
 */
class getty_bib_parser extends FeedsParser {
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    //grab the raw data from the batch
    $raw_data = $fetcher_result->getRaw();
    $file_path = $fetcher_result->getFilePath();
    
    //parses the extension correctly
    $file_path = pathinfo($file_path);
    $file_type = $file_path['extension'];
    
    //declares new variables
    $parser_result = new FeedsParserResult();
    $items = array();
    
    //switches based on file type. data within the files are then passed over to the handlers
    switch ($file_type) {
      case 'ris':
        $items = $this->_getty_bib_ris_handler($raw_data);
        break;
      case 'rdf';
        $items = $this->_getty_bib_rdf_handler($raw_data);
        break;
    }
    
    $parser_result->items = $items;
    
    return $parser_result;
  }
  
  /**
   *  @method:
   *    this method handles ris to correct data output
   */
  public function _getty_bib_ris_handler($raw_data) {
    //declares the new getty ris
    $bib = new getty_biblio_ris();
    $bib->output = $raw_data;
    $items = $bib->convert_to_array();
    
    //calls and standardizes the data
    $this->_getty_bib_standardized_handler($items, 'ris');
    
    return $items;
  }
  
  /**
   *  @method:
   *    this method handles rdf to correct data output
   */
  public function _getty_bib_rdf_handler($raw_data) {
    $bib = new getty_biblio_rdf();
    $bib->output = $raw_data;
    $items = $bib->convert_to_array();
    
    //calls and standardizes the data
    $this->_getty_bib_standardized_handler($items, 'rdf');
    
    return $items;
  }
  
  /**
   *  @method:
   *    this method is used to standardize the data before returning the items to the processor
   *    allows others to modify the data before saving to ensure that there fields that are filled out
   */
  public function _getty_bib_standardized_handler(&$items, $type = NULL) {
    $required_fields = array(
      'title' => 'Getty - Bib - No Title - @time',
      '_import_type' => $type
    );
    
    //allows other modules to alter this before it comes out
    drupal_alter('getty_bib_required_parser', $required_fields, $type);
    
    //does for each items
    foreach ($items as $key => $values) {
      $diff = array_diff($required_fields, $values);
      
      //only continue if diff is not empty
      if (!empty($diff)) {
        foreach ($diff as $required_field => $field_value) {
          if (empty($items[$key][$required_field])) {
            $items[$key][$required_field] = t($field_value, array('@time' => REQUEST_TIME));
          }
        }
      }
    }
    
    //allows other modules to hook in and alter the items before processor
    drupal_alter('getty_bib_items_parser', $items, $type);
  }
}