<?php

/**
 *  @interface:
 *    This defines the interface for the getty biblio
 */
interface getty_biblio_interface {
  public function add_biblio_nid($nid);
  public function remove_biblio_nid($nid);
  public function get_biblio();
  public function get_output();
  public function field_value_handler($field, $field_name);
}

/**
 *
 *  @class:
 *    This class will provide the parent object support for bibliography
 * 
 */
class getty_biblio implements getty_biblio_interface {
  public $biblio_nid = array();
  public $biblio_node = array();
  public $output;
  
  /**
   *  @method:
   *    This constructor is defined but not in used
   */
  public function __construct() {}
  
  /**
   *  @method:
   *    This method is used to add an nid into the object
   */
  public function add_biblio_nid($nid) {
    $this->biblio_nid[$nid] = $nid;
  }
  
  /**
   *  @method:
   *    This method is used to remove an nid
   */
  public function remove_biblio_nid($nid) {
    unset($this->biblio_nid[$nid]);
  }
  
  /**
   *  @method:
   *    This method is used to retrieve the actually bibliography from the provided nid
   */
  public function get_biblio() {
    //allows for multiple listing in ris
    foreach ($this->biblio_nid as $key => $nid) {
      //ensures that the nid is numeric
      if (is_numeric($nid)) {
        $node = node_load($nid);
        
        //only add if this object is a node
        if (is_object($node) && $node->type = 'bibliography') {
          $this->biblio_node[$nid] = $node; //should adjust to limit whats available into the class to save memory        
        }
        //sanitizes the object so that only bib are set other nids will be removed
        else {
          $this->remove_biblio_nid($nid);
        }
      }
    }
    
    //sanitize data into just the fields we want
    $this->get_biblio_fields();
  }
  
  /**
   *  @method:
   *    This method is used to retrieve the bibliography fields
   *    This will keep the data uniform when the class is extended
   */
  public function get_biblio_fields() {
    //default variables
    $fields_available = _getty_bibliography_support_available_fields();
    $fields = array();
    //$field_prefix = 'field_';
    
    if (!empty($this->biblio_node)) {
      //this does it for each of the node.
      foreach ($this->biblio_node as $nid => $node) {
        //$cached_version = cache_get('biblio_ris_' . $nid);
        
        //only does it if the node is an object otherwise we assume we already added it in
        if (is_object($node)) {
          foreach ($fields_available as $key => $field) {
            if ($field == 'title') {
              $field_raw = $node->title;  
            }
            else {
              $field_raw = field_get_items('node', $node, $field);
            }
    
            //adds data into the fields using the safe value
            if (isset($field_raw[0]['safe_value'])) {
              $fields[$field] = $field_raw[0]['safe_value'];  
            }
            else {
              $fields[$field] = (empty($field_raw)) ? '' : $field_raw;
            }
            
            //@dev: TODO: implement alter to allow devs to insert other types of fields
          }
          
          //removes the object and sets the fields in
          $this->biblio_node[$nid] = $fields;
        }
        
        //remove from the list as we go
        $this->remove_biblio_nid($nid);
      }
    }
  }
  
  /**
   *  @method:
   *    This method is used to return the output
   */
  public function get_output() {
    return $this->output;
  }
  
  /**
   *  @method:
   *    Provides a function to the class to clean up based on the different types
   *    such as taxonomy or date field
   */
  public function field_value_handler($field, $field_name) {
    $value = $field;
    
    //only alter the value if its not a string
    if (!is_string($value)) {
      $field_info = field_info_field($field_name);
    
      switch ($field_info['module']) {
        case 'text':
        case 'date':
          $value = reset($field);
          $value = $value['value'];
          break;
        case 'taxonomy':
          $value = reset($field);
          $tid = $value['tid'];
          
          //ensures that we load a tid
          if (is_numeric($tid)) {
            $taxonomy = taxonomy_term_load($tid);
            if (is_object($taxonomy)) {
              $value = trim($taxonomy->name);
            }
            else {
              $value = '';
            }
          }
          else {
            $value = '';
          }
          break;
        default:
          $value = '';
          break;
      }
    }
    
    //TODO: create alter to allow other modules to alter the data
    
    //return value if one is found
    return trim(strip_tags($value));
  }
}
