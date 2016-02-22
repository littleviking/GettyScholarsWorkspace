# The Getty Scholars’ Workspace Installation Instructions

## System Requirements

* Apache
 * MySQL 5.0.15
 * PHP 5.2.5 or higher (5.4 or higher recommended)

Information about other, less common configurations can be found at
https://www.drupal.org/requirements

## Step 1: Setting up the MySQL database

These instructions are for creating a database on a Linux server
below. For other types of database setups (cPanel, Postgres, Windows,
or other), see instructions at:
https://www.drupal.org/documentation/install/create-database. For
information on installing and configuring MySQL, see:
http://dev.mysql.com/doc/refman/5.7/en/index.html

**Note:** The database should be created with UTF-8 (Unicode) encoding,
for example utf8_general_ci.

In the following examples, 'username' is a sample MySQL user who will
have the CREATE and GRANT privileges and 'databasename' is the name of
the new database.  Use the appropriate names for your system.

**A.** Create a new database for your site (change the username and databasename):

    mysql -u username -p -e "CREATE DATABASE databasename CHARACTER
    SET utf8 COLLATE utf8_general_ci;"

MySQL prompts for the 'username' database password, and creates the initial database
files.

**B.** Log in:

    mysql -u username -p

MySQL will prompt for the 'username' database password.

**C.** At the MySQL prompt, set the permissions using the following command:

    GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, INDEX, ALTER,
    CREATE TEMPORARY TABLES ON databasename.* TO
    'username'@'localhost' IDENTIFIED BY 'password';

In this case:
 * 'databasename' is the name of the database
 * 'username' is the username of the MySQL user account
 * 'localhost' is the host where Drupal is installed
 * 'password' is the password required for that username
 
Be sure to use backticks ( ` ) around the database name if using a
MySQL escape character (_ or %) in the database name. For example,
because the underscore character is a wildcard, drupal_test_account.*
should be `drupal\_test\_account`.* for security. Otherwise the
underscores would match any character and could accidentally give
access to other similarly named databases.

**Note:** Unless the database user/host combination for your Drupal
installation has all of the privileges listed above (except possibly
`CREATE TEMPORARY TABLES`, which is currently only used by Drupal core
automated tests and some contributed modules), you will not be able to
install or run Drupal.

For further information on the GRANT statement, see:
http://dev.mysql.com/doc/refman/5.0/en/grant.html

**D.** If successful, MySQL will reply with:

    Query OK, 0 rows affected

**E.** Now exit the MYSQL prompt by typing:

    exit
	
The server will answer by saying:

    Bye
	
## Step 2: Install Drush

On Debian, just do:

	apt-get install drush

For systems that do not have drush packaged and available for easy
installation, you can install from source:

**A.** Download the latest stable release using the code below or
browse to github.com/drush-ops/drush/releases .

    wget http://files.drush.org/drush.phar
	
**B.** Test the install

    php drush.phar core-status

**C.** Rename to `drush` instead of `php drush.phar`. The destination
can be anywhere on $PATH.

    chmod +x drush.phar
    sudo mv drush.phar /usr/local/bin/drush
	
**D.** Enrich the bash startup file with completion and aliases.

    drush init

## Step 3: Download the Getty Scholars’ Workspace Repo

    git clone https://github.com/GettyScholarsWorkspace/GettyScholarsWorkspace

## Step 4: Fetch Required Modules

    drush make profiles/getty_scholars_workspace/build-gsw.make
	
## Step 5: Prepare Drupal for Installation

The web server needs to be able to write to sites/default/,
sites/default/settings.php, and sites/default/files/ to install. By
default, Drupal will attempt to create and populate the settings.php
file automatically when you use install.php to set up the site. If you
get errors referring to the Settings file during installation, you
will have to manually create the settings.php file and do a few more
tasks before you can run install.php.

**A.** Navigation and Creation

Navigate to sites/default of your root Drupal install. Copy the
default.settings.php file and save the new file as settings.php in the
same directory (see note below about renaming). If you have shell
access (command line), run the following command from the directory
that contains your Drupal installation files:

    cp sites/default/default.settings.php sites/default/settings.php

**Note:** Do not simply rename the file. The Drupal installer needs both
files.

**B.** Check That the Permissions Are Writable:

By default, the sites/default and settings.php files should be
writable. Check that the permissions of sites/default and settings.php
are writable by issuing the following commands:

    ls -l sites/

Permission on sites/default should be 755 [drwxr-xr-x]:

    ls -l sites/default/settings.php
	
Permission on settings.php should be 644 [-rw-r--r--].  If they are
anything but writable, you can issue the following commands:

    chmod 644 sites/default/settings.php

**C.** Try the Install

At this point, attempt the install. See if it is possible to get
through the installation by running http://[yoursite]/install.php. If
you are successful, visit the Reports page at Reports -> Status report
(admin/reports/status). On the Reports page, look for a line that
says: File system. If it says anything other than "Writable," follow
Step 4 in the Help page linked below. Next, look for a line that says:
Configuration file. If it says anything other than "Protected," you
will need to re-secure the configuration files as described in Step 5
in the Help page linked below.

If you're still unable to install, see this Help page for more
options: https://www.drupal.org/documentation/install/settings-file
Drupal 6, 7, and 8 come with a sample configuration file at
sites/default/default.settings.php. Before running the installation
script, copy the configuration file as a new file called settings.php
and change its permissions. After the installation, restrict the
permissions again.

## Step 6: Install Drupal

**A.** Launch site on preferred web browser.

**B.** Follow Drupal Install instructions provided through interface.

## Step 7: Using Scholars’ Workspace

Consult the Getty Scholars’ Workspace User Guide for further guidance.

