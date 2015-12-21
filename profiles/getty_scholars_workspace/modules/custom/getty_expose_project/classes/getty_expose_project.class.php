<?php

/**
 *  @class:
 *    This class provides getty projects with a complete xml request from the server
 */
class getty_project {
  public $project_nid;
  public $format;
  public $nodes = array();
  public $project_node;
  public $references = array();
  private $include_images = array();
  
  /**
   *  @method:
   *    constructor for class
   */
  function __construct($nid, $format = 'json') {
    $this->project_nid = $nid;
    $this->format = $format;
  }
  
  /**
   *  @method:
   *    Public method that is used to get the output based on the request
   */
  public function get_output() {
    $break_cache = (isset($_GET['break_cache'])) ? $_GET['break_cache'] : FALSE;
    //only cache if break_cache is not set
    if (!$break_cache) {
      $cached = $this->_cache();
    }

    //default variables
    $this->_load_project_node();
    $contents = $this->_load_project_contents();
    $this->nodes = $contents;
    $this->_parse_nodes($this->nodes);
    $this->nodes = $contents;

    //switches based on the format requested
    switch ($this->format) {
      case 'xml':
        drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
        if (empty($cached)) {
          $data = $this->_array_to_xml($this);
        }
        else {
          $data = $cached;
        }
        break;
      default:
        drupal_add_http_header('Content-Type', 'application/json');
        if (empty($cached)) {
          $data = $this->_array_to_json($this);
        }
        else {
          $data = $cached;
        }
        break;
    }
    
    //adds data into the cache
    if (empty($cached)) {
      $data = json_decode(json_encode($data), true);
      $this->_cache('set', $data);
    }
    
    //download the files once the parameter is set
    if (isset($_GET['download']) && $_GET['download']) {
      //generates the download portion once download is required
      $file_path = $this->_download_project($data);
      $filename = explode('/', $file_path);
      $filename = $filename[count($filename) - 1];

      //sets all the headers for the download to work
      header("Pragma: public");
      header("Expires: 0");
      header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
      header("Cache-Control: private",false); // required for certain browsers 
      header('Content-Disposition: attachment; filename="' . $filename . '"');
      header("Content-Transfer-Encoding: binary");
      header("Content-Length: " . filesize($file_path));
      readfile("$file_path");

    }

    $output = $data;
    return $output;
  }
  
  /**
   *  @method:
   *    This method is used to download the project
   */
  public function _download_project($output = '') {
    //default variables
    $zip = new ZipArchive();
    $nid = $this->project_nid;
    $DelFilePath = "project_" . $nid . "_" . $this->format . ".zip";
    $public = variable_get('file_public_path', 'sites/default/files');
    $path = DRUPAL_ROOT . '/' . $public . '/';
    
    //ensures that we delete the old file
    if(file_exists($path . $DelFilePath)) {
      unlink ($path . $DelFilePath); 
    }

    //creates the zip file and starts to append
    if ($zip->open($path . $DelFilePath, ZIPARCHIVE::CREATE) != TRUE) {
      watchdog('getty project', "Could not open archive at " . print_r($path . $DelFilePath, 1));
    }

    //appends the format requested
    $zip->addFromString('project_' . $nid . '.' . $this->format, $output);
    
    //does for each image included to download
    foreach ($this->include_images as $key => $images) {
      $site_path = explode($public, $images);
      $image_path = explode('/', $site_path[1]);
      $file_name = $image_path[count($image_path) - 1];
      //ensures that the file exists on the server before adding
      if (file_exists($images)) {
        $zip->addFile($images, $public . $site_path[1]);
      }
    }
    
    // close and save archive
    $zip->close();
    
    //returns the path of the zip
    return $path . $DelFilePath;
  }
  
  /**
   *  @method:
   *    This method is used to retrive a cache from drupal if one is available
   */
  private function _cache($action = 'get', $data = array()) {
    $nid = $this->project_nid;
    $width = '';
    
    //sets a cache version
    if (empty($nid)) {
      $cache_cid = 'no_project_cache';
    }
    else {
      $cache_cid = 'getty_project_cache_' . $nid . '_' . $this->format;
    }

    //calls the cache time
    $cache_time = variable_get('getty_expose_project_cache_time', 10);
    
    //switch based on action
    switch ($action) {
      //sets the cached and cache for x minutes
      case 'set':
        $cached = cache_set($cache_cid, $data, 'cache', REQUEST_TIME + ($cache_time * 60));
        break;
      //returns cache if available
      default:
        $cached = cache_get($cache_cid, 'cache');

        if (isset($cached->data)) {
          return $cached->data;
        }
        return $cached;
        break;
    }
  }
  
  /**
   *  @method:
   *    Private method that is used to load the project node
   */
  private function _load_project_node() {
    $project_nid = $this->project_nid;
    if (is_numeric($project_nid)) {
      $project_node = node_load($project_nid);
      
      if (is_object($project_node) && isset($project_node->type) && $project_node->type == 'project') {
        $this->project_node = $project_node;
      }
      else {
        $this->project_node = 'NID Provided is not a project';
      }
    }
    else {
      $this->project_node = 'No Project NID Provided';
    }
  }
  
  /**
   *  @method:
   *    this private method is used to load all content related to a project
   */
  private function _load_project_contents() {
    $contents = array();
    $nids = array();
    
    $db_result = db_select('og_membership', 'og_content')
      ->fields('og_content', array('etid'));
    $db_result->leftJoin('node', 'n', 'n.nid = og_content.etid');
    $db_result->fields('n', array('type'));
    $db_result->condition('entity_type', 'node', '=');
    $db_result->condition('og_content.gid', $this->project_nid, '=');
    $result = $db_result->execute()->fetchAll();
    
    //maps the to the correct type
    foreach ($result as $key => $value) {
      $nids[$value->type][] = $value->etid;
    }
    
    //loads all the nodes
    foreach ($nids as $type => $values) {
      $nids[$type] = $this->_load_referenced_nodes($values);
    }
    
    $db_result = $nids;
    
    return $db_result;
  }
  
  /**
   *  @method:
   *    This is used to load all referenced node given the node ids
   */
  private function _load_referenced_nodes($node_ids = array()) {
    $nodes = node_load_multiple($node_ids);
    
    return $nodes;
  }
  
  /**
   *  @method:
   *    Process all list of nodes.
   *
   *    This is where all the fields are handled
   */
  private function _parse_nodes(&$nodes = array()) {
    global $base_url;
    
    //does for each for each of the node types
    foreach ($nodes as $type => $values) {
      $fields = field_info_instances("node", $type);

      //does for each of the nodes
      foreach ($values as $node => $node_values) {
        //loads all scribe attachment
        $scribe = entity_load('scribe_attachment', FALSE, array('entity_id' => $node_values->nid));
        $nodes[$type][$node]->scribe = $scribe;
        
        //does for each of the field
        foreach ($fields as $field_name => $field_value) {
          $field_items = field_get_items('node', $node_values, $field_name);

          if (!empty($field_items)) {
            //does for each of them.
            foreach ($field_items as $item => $item_value) {
              switch ($field_value['field_name']) {
                case 'og_group_ref':
                  break;
                //makes the images relative to the node
                case 'field_image':
                case 'field_timeline_media_image':
                  if (!isset($item_value['fid'])) {
                    break;
                  }
                  
                  //changes over to allow the image refence to use the same formatting
                  $item_value['target_id'] = $item_value['fid'];
                case 'field_image_references':
               
                  //conversion to relative path for images
                  if (isset($item_value['target_id'])) {
                    $fid = (int)$item_value['target_id'];
                    $file = file_load($fid);
                    
                    //only does this for the file if its not empty
                    if (!empty($file)) {
                      $file->server_path = drupal_realpath($file->uri);
                      $file->relative_path = str_replace('public:/', variable_get('file_public_path', 'sites/default/files'), $file->uri);
                      $field_items[$item] = (array)$file;
                      $this->include_images[] = $file->server_path;
                    }
                  }
                  break;
                case 'field_reference':
                  break;
                //handler for the body section
                case 'body':
                  //variables 
                  $body_value = $item_value['value'];
                  
                  //does for the following attribtes
                  $this->_add_images_regex('href', $body_value);
                  $this->_add_images_regex('src', $body_value);
                  
                  //does a simple replacement from the domain
                  $field_items[$item]['value'] = str_replace($base_url, '', $field_items[$item]['value']);
                  $field_items[$item]['safe_value'] = str_replace($base_url, '', $field_items[$item]['safe_value']);
                  
                  break;
              }
 
              $nodes[$type][$node]->$field_name = $field_items;
            }
          }
        }
      }
    }
  }
  
  /**
   *  @method:
   *    This method is used to add the following attr into the images
   */
  private function _add_images_regex($attr = 'href', $haystack) {
    $public_path = variable_get('file_public_path', 'sites/default/files');
    
    //a attr processing
    $pattern = '/' . $attr . '=["\']?([^"\'>]+)["\']?/';
    preg_match($pattern, $haystack, $matches);
    if (isset($matches[1]) && !empty($matches[1])) {
      $info = parse_url($matches[1]);
      
      //only need to do on one of the values and not both
      if (!empty($info['path']) && stripos($info['path'], $public_path) !== FALSE && preg_match('/(\.jpg|\.png|\.bmp)$/', $info['path'])) {
        $schema_path = str_replace($public_path, 'public:/', $info['path']);
        $image_path = drupal_realpath(substr($schema_path, 1)); //use substr to remove first /
        $this->include_images[] = $image_path; //adds the image into the included images
      }
    }
  }
  
  /**
   *  @method:
   *    Simple functionality to convert array to json
   */
  private function _array_to_json($array) {
    return json_encode($array);
  }
  
  /**
   *  @method:
   *    Simple functionality that uses another library to convert array to xml
   */
  private function _array_to_xml($array) {
    $array = json_decode(json_encode($array), true);
    $xml = Array2XML::createXML('project', $array);
    return $xml->saveXML();
  }
}