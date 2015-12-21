GettySW LTCZ Module
-------------------
The custom LTCZ module provides CropZoom features for the LightTable module. 
There are a few points to make regarding the structure of this module:

* The module has a weight of -5. This is so that its views templates will be the
ones used, instead of the views templates from the LightTable module. These 
template files are found in the /templates directory.

* Because the module has a weight of -5, we can't override just pertinent 
functions, because LightTable's js file will get used instead of ours. This is 
why hook_js_alter() is implemented to remove the existing lighttable.js file and 
the module has its own js file which includes all LightTable and CropZoom 
features.