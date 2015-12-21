<?php

/**
 *
 *  @class:
 *    This class will extend the object.class to provide rdf support
 * 
 */
class getty_biblio_rdf extends getty_biblio {
  /**
   *  method that returns the list of available rdf available to use
   */
  public function get_rdf_list($action = NULL) {
    //grabs the variable from the rdf set in the db
    $variable_name = 'getty_biblio_wrapper_rdf';
    $all_value = variable_get($variable_name, '');
    $rdf = array();
    
    //only continue if its not empty
    if (!empty($all_value)) {
      //does for each value
      foreach ($all_value as $key => $value) {
        //gets the element
        $first_element = key($value);
        
        switch ($action) {
          //returns the rdf and term
          case 'rdf_term':
            if (!empty($value[$first_element])) {
              $rdf[$value[$first_element]] = $first_element;
            }
            break;
          default:
            $rdf[$first_element] = $value[$first_element];
            break;
        } 
      }
    }
    
    return $rdf;
  }
  
  /**
   *  method that converts the information into the correct format in rdf
   *
   *  currently only does single export
   *
   *  @dev:
   *    data structure is
   *    array(
   *      array(
   *        url => array(
   *          property => array(
   *            'value' => value,
   *            'type' => 'literal'
   *          )
   *          property_2 => array(
   *            'value' => value,
   *            'type' => 'literal'
   *          )
   *        )
   *      )
   *    );
   *
   *  @see
   *    http://web.archive.org/web/20100801084904/http://n2.talis.com/wiki/RDF_PHP_Specification
   */
  public function convert() {
    //variables
    global $base_url;
    $rdf_term_array = $this->get_rdf_list('rdf_term');
    $output = '';
    $available_rdf = $this->get_rdf_list();
    $biblio_list = $this->biblio_node;
    $rdf = array();
    
    //allow the rdf to use these namespaces
    $ns = $this->_get_namespaces(); 
    
    //does for each bibliography within the obj
    foreach ($biblio_list as $nid => $node) {
      $path = url('node/' . $nid);

      foreach ($available_rdf as $node_term => $rdf_term) {
        //breaks the loop if the term is empty or the node field is empty
        if (empty($rdf_term) || empty($node[$node_term])) {
          continue;
        }
        
        //ensures that the node field is set
        if (isset($node[$node_term])) {
          //sanitize the data before it comes out.
          $value = str_replace(PHP_EOL, '', $node[$node_term]);
          $processed_value = $this->field_value_handler($value, $node_term);
          
          //only continue if the value is processed and not empty
          if (!empty($processed_value)) {
            $rdf[$path][$rdf_term] = array(
              array(
                'value' => $processed_value,
                'type' => 'literal'
              )
            );
          }
        }
      }
    }
    
    $conf = array('ns' => $ns);
    $ser = ARC2::getRDFXMLSerializer($conf);
    $doc = $ser->getSerializedIndex($rdf);
    $this->output .= $doc;
  }

  /**
   *  @method:
   *    method used to convert output version into an array
   */
  public function convert_to_array() {
    $doc = QueryPath::withXML($this->output);
    $available_rdf = $this->get_rdf_list('rdf_term');
    $processed_data = array();

    $fields = array_keys($available_rdf);

    $items = $doc->children('bib|*');
    foreach ($items as $i => $item) {
      $processed_data[$i] = array();
      foreach ($fields as $field) {
        $processed_data[$i][$available_rdf[$field]] = $item->find(str_replace(':', '|', $field))->textImplode(', ');
      }
    }
    
    return $processed_data;
  }

  /**
   *  @method:
   *    private method that returns the available name spaces
   */
  private function _get_namespaces() {
    $ns = array(
      'foaf' => 'http://xmlns.com/foaf/0.1/',
      'dc' => 'http://purl.org/dc/elements/1.1/',
      'z' => "http://www.zotero.org/namespaces/export",
      'bib' => "http://purl.org/net/biblio",
      'foaf' => "http://xmlns.com/foaf/0.1/",
      'dcterms' => "http://purl.org/dc/terms/",
      'vcard' => "http://nwalsh.com/rdf/vCard#",
      'link' => "http://purl.org/rss/1.0/modules/link/",
      'prism' => 'http://prismstandard.org/namespaces/1.2/basic/',
      // Core RDF namespaces which don't need to be redefined in modules.
      'content' => 'http://purl.org/rss/1.0/modules/content/',
      'og' => 'http://ogp.me/ns#',
      'rdfs' => 'http://www.w3.org/2000/01/rdf-schema#',
      'sioc' => 'http://rdfs.org/sioc/ns#',
      'sioct' => 'http://rdfs.org/sioc/types#',
      'skos' => 'http://www.w3.org/2004/02/skos/core#',
      'xsd' => 'http://www.w3.org/2001/XMLSchema#',
      'schema' => 'http://schema.org/',
      'rnews' => 'http://iptc.org/std/rNews/2011-10-07',
      'dbp' => 'http://dbpedia.org/property/',
      'grddl' => 'http://www.w3.org/2003/g/data-view#',
      'ma' => 'http://www.w3.org/ns/ma-ont#',
      'owl' => 'http://www.w3.org/2002/07/owl#',
      'prov' => 'http://www.w3.org/ns/prov#',
      'rdf' => 'http://www.w3.org/1999/02/22-rdf-syntax-ns#',
      'rdfa' => 'http://www.w3.org/ns/rdfa#',
      'rif' => 'http://www.w3.org/2007/rif#',
      'rr' => 'http://www.w3.org/ns/r2rml#',
      'sd' => 'http://www.w3.org/ns/sparql-service-description#',
      'skosxl' => 'http://www.w3.org/2008/05/skos-xl#',
      'wdr' => 'http://www.w3.org/2007/05/powder#',
      'void' => 'http://rdfs.org/ns/void#',
      'wdrs' => 'http://www.w3.org/2007/05/powder-s#',
      'xhv' => 'http://www.w3.org/1999/xhtml/vocab#',
      'xml' => 'http://www.w3.org/XML/1998/namespace',
      'org' => 'http://www.w3.org/ns/org#',
      'gldp' => 'http://www.w3.org/ns/people#',
      'cnt' => 'http://www.w3.org/2008/content#',
      'dcat' => 'http://www.w3.org/ns/dcat#',
      'earl' => 'http://www.w3.org/ns/earl#',
      'ht' => 'http://www.w3.org/2006/http#',
      'ptr' => 'http://www.w3.org/2009/pointers#',
      'cc' => 'http://creativecommons.org/ns#',
      'ctag' => 'http://commontag.org/ns#',
      'dcterms' => 'http://purl.org/dc/terms/',
      'gr' => 'http://purl.org/goodrelations/v1#',
      'ical' => 'http://www.w3.org/2002/12/cal/icaltzd#',
      'rev' => 'http://purl.org/stuff/rev#',
      'v' => 'http://rdf.data-vocabulary.org/#',
      'vcard' => 'http://www.w3.org/2006/vcard/ns#',
      'adms' => 'http://www.w3.org/ns/adms#',
      'doap' => 'http://usefulinc.com/ns/doap#',
    );
    
    return $ns;
  }
}
