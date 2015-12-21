; getty_scholars_workspace make file for d.o. usage
core = "7.x"
api = "2"

; +++++ Modules +++++

projects[admin_menu][version] = "3.0-rc4"
projects[admin_menu][subdir] = "contrib"

projects[ctools][version] = "1.9"
projects[ctools][subdir] = "contrib"

projects[context][version] = "3.6"
projects[context][subdir] = "contrib"

projects[date][version] = "2.9"
projects[date][subdir] = "contrib"

projects[profiler_builder][version] = "1.2"
projects[profiler_builder][subdir] = "contrib"

projects[features][version] = "2.2"
projects[features][subdir] = "contrib"

projects[feeds][version] = "2.0-beta1"
projects[feeds][subdir] = "contrib"

projects[entityreference][version] = "1.1"
projects[entityreference][subdir] = "contrib"

projects[field_collection][version] = "1.0-beta8"
projects[field_collection][subdir] = "contrib"

projects[field_collection_fieldset][version] = "2.5"
projects[field_collection_fieldset][subdir] = "contrib"

projects[field_formatter_class][version] = "1.1"
projects[field_formatter_class][subdir] = "contrib"

projects[field_group][version] = "1.4"
projects[field_group][subdir] = "contrib"

projects[link][version] = "1.2"
projects[link][subdir] = "contrib"

projects[flexslider][version] = "2.0-alpha1"
projects[flexslider][subdir] = "contrib"

projects[file_entity][version] = "2.0-unstable7"
projects[file_entity][subdir] = "contrib"

projects[comment_og][version] = "1.0"
projects[comment_og][subdir] = "contrib"
projects[comment_og][patch][] = "https://www.drupal.org/files/comment_og-OG7.x-2.x-compatibility-1833006-36_0.patch"

projects[og][version] = "2.7"
projects[og][subdir] = "contrib"

projects[administerusersbyrole][version] = "1.0-beta1"
projects[administerusersbyrole][subdir] = "contrib"
projects[administerusersbyrole][patch][] = "https://www.drupal.org/files/multiple_cancel-1680156-23.patch"
projects[administerusersbyrole][patch][] = "https://www.drupal.org/files/923882-administerusersbyrole-install-issue-D7.patch"

projects[backup_migrate][version] = "2.4"
projects[backup_migrate][subdir] = "contrib"

projects[colorbox][version] = "2.10"
projects[colorbox][subdir] = "contrib"

projects[diff][version] = "3.2"
projects[diff][subdir] = "contrib"

projects[entity][version] = "1.6"
projects[entity][subdir] = "contrib"

projects[field_formatter_settings][version] = "1.1"
projects[field_formatter_settings][subdir] = "contrib"

projects[footnotes][version] = "2.5"
projects[footnotes][subdir] = "contrib"

projects[image_field_caption][version] = "2.x-dev"
projects[image_field_caption][subdir] = "contrib"

projects[job_scheduler][version] = "2.0-alpha3"
projects[job_scheduler][subdir] = "contrib"

projects[libraries][version] = "2.1"
projects[libraries][subdir] = "contrib"

projects[module_filter][version] = "2.0"
projects[module_filter][subdir] = "contrib"

projects[restws][version] = "2.4"
projects[restws][subdir] = "contrib"

projects[role_delegation][version] = "1.1"
projects[role_delegation][subdir] = "contrib"

projects[strongarm][version] = "2.0"
projects[strongarm][subdir] = "contrib"

projects[facetapi][version] = "1.3"
projects[facetapi][subdir] = "contrib"

projects[footnotes][version] = "2.5"
projects[footnotes][subdir] = "contrib"

projects[jquery_update][version] = "2.7"
projects[jquery_update][subdir] = "contrib"

projects[popup][version] = "1.3"
projects[popup][subdir] = "contrib"

projects[wysiwyg][version] = "2.2"
projects[wysiwyg][subdir] = "contrib"

projects[better_exposed_filters][version] = "3.0-beta3"
projects[better_exposed_filters][subdir] = "contrib"

projects[views][version] = "3.13"
projects[views][subdir] = "contrib"

projects[views_bulk_operations][version] = "3.3"
projects[views_bulk_operations][subdir] = "contrib"

projects[views_fluid_grid][version] = "3.0"
projects[views_fluid_grid][subdir] = "contrib"

projects[views_timelinejs][version] = "1.0-alpha1"
projects[views_timelinejs][subdir] = "contrib"

; +++++ Themes +++++

; omega
projects[omega][type] = "theme"
projects[omega][version] = "3.1"
projects[omega][subdir] = "contrib"

; rubik
projects[rubik][type] = "theme"
projects[rubik][version] = "4.0-beta8"
projects[rubik][subdir] = "contrib"

; tao
projects[tao][type] = "theme"
projects[tao][version] = "3.0-beta4"
projects[tao][subdir] = "contrib"

; +++++ Libraries +++++

; Annotorious
libraries[annotorious][directory_name] = "annotorious"
libraries[annotorious][type] = "library"
libraries[annotorious][destination] = "libraries"
libraries[annotorious][download][type] = "get"
libraries[annotorious][download][url] = "https://github.com/annotorious/annotorious/archive/v0.4.zip"

; CKEditor
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][type] = "library"
libraries[ckeditor][destination] = "libraries"
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.6.1/ckeditor_3.6.6.1.tar.gz"

; CKEditor Footnotes
libraries[ckeditor_footnotes][directory_name] = "footnotes"
libraries[ckeditor_footnotes][type] = "library"
libraries[ckeditor_footnotes][destination] = "libraries/ckeditor/plugins"
libraries[ckeditor_footnotes][download][type] = "copy"
libraries[ckeditor_footnotes][download][url] = "profiles/getty_scholars_workspace/utilities/ckeditor_footnotes"

; ColorBox
libraries[colorbox][directory_name] = "colorbox"
libraries[colorbox][type] = "library"
libraries[colorbox][destination] = "libraries"
libraries[colorbox][download][type] = "get"
libraries[colorbox][download][url] = "https://github.com/jackmoore/colorbox/archive/1.4.15.zip"

; Flexslider
libraries[flexslider][directory_name] = "flexslider"
libraries[flexslider][type] = "library"
libraries[flexslider][destination] = "libraries"
libraries[flexslider][download][type] = "get"
libraries[flexslider][download][url] = "https://github.com/woothemes/FlexSlider/archive/version/2.1.zip"

; OpenSeadragon
libraries[openseadragon][directory_name] = "openseadragon"
libraries[openseadragon][type] = "library"
libraries[openseadragon][destination] = "libraries"
libraries[openseadragon][download][type] = "get"
libraries[openseadragon][download][url] = "https://github.com/openseadragon/openseadragon/releases/download/v2.1.0/openseadragon-bin-2.1.0.zip"

; Views TimelineJS
libraries[timeline][directory_name] = "timeline"
libraries[timeline][type] = "library"
libraries[timeline][destination] = "libraries"
libraries[timeline][download][type] = "get"
libraries[timeline][download][url] = "https://github.com/NUKnightLab/TimelineJS/archive/v2.17.zip"

