<?php

/**
 *
 *  @class:
 *    This class will extend the object.class to provide ris support
 * 
 */
class getty_biblio_ris extends getty_biblio {
  /**
   *  method that returns the list of available ris available to use
   */
  public function get_ris_list($action = NULL) {
    //grabs the variable from the ris set in the db
    $variable_name = 'getty_biblio_wrapper_ris';
    $all_value = variable_get($variable_name, '');
    $ris = array();
    
    //only continue if its not empty
    if (!empty($all_value)) {
      //does for each value
      foreach ($all_value as $key => $value) {
        //gets the element
        $first_element = key($value);
        
        switch ($action) {
          //returns the ris and term
          case 'ris_term':
            if (!empty($value[$first_element])) {
              $ris[$value[$first_element]] = $first_element;
            }
            break;
          default:
            $ris[$first_element] = $value[$first_element];
            break;
        }
      }
    }
    
    return $ris;
  }
  
  /**
   *  method that converts the information into the correct format in ris
   */
  public function convert() {
    //variables
    $output = '';
    $available_ris = $this->get_ris_list();
    $ris_term_array = $this->get_ris_list('ris_term');
    $biblio_list = $this->biblio_node;
    
    //ensures that the order ty is always there and set
    $order = array(
      'TY' => 'Standard'
    );
    
    //does for each bibliography within the obj
    foreach ($biblio_list as $nid => $node) {
      foreach ($order as $order_key => $order_value) {
        if (isset($ris_term_array[$order_key]) && isset($node[$ris_term_array[$order_key]])) {
          //sanitize the data before it comes out.
          $value = str_replace(PHP_EOL, '', $node[$ris_term_array[$order_key]]);
          
          //ensures that there is a value if override is on
          if (empty($value)) {
            $value = $order_value;
          }
          
          $output .= $order_key . '  - ' .  $this->field_value_handler($value, $ris_term_array[$order_key]) . "\r\n";
          unset($available_ris[$ris_term_array[$order_key]]);
        }
        else {
          //ensures that there is a value if override is on
          if (empty($value)) {
            $value = $order_value;
          }
          
          $output .= $order_key . '  - ' .  $order_value . "\r\n";
        }
      }
      
      //does for each order for ris
      foreach ($available_ris as $node_term => $ris_term) {
        //breaks the loop if the term is empty or the node field is empty
        if (empty($ris_term) || empty($node[$node_term])) {
          continue;
        }
        
        //ensures that the node field is set
        if (isset($node[$node_term])) {
          //sanitize the data before it comes out.
          $value = str_replace(PHP_EOL, '', $node[$node_term]);
          $output .= $ris_term . '  - ' .  $this->field_value_handler($value, $node_term) . "\r\n";
        }
      }
      
      //always needs to end with ER
      $output .= "ER  - \r\n\r\n";
    }
    
    //adds this to the ris
    $this->output = $output;
  }
  
  /**
   *  @method:
   */
  public function convert_to_array() {
    $ris = new \LibRIS\RISReader();
    $ris->parseString($this->output);
    $ris_rows = $ris->getRecords();
    $array = $items = array();
    $available_ris = $this->get_ris_list('ris_term');

    //does for each of the sections
    foreach ($ris_rows as $key => $values) {
      $item = array();

      //does for each set of rows
      foreach ($values as $data_key => $data_value) {
        //adds the data in if it exist otherwise just add the key
        if (isset($available_ris[$data_key])) {
          $item[$available_ris[$data_key]] = implode('; ', $data_value);
        }
        else {
          $item[$data_key] = implode('; ', $data_value);
        }
      }

      //adds item into the array list
      $array[] = $item;
    }
  
    return $array;
  }
}