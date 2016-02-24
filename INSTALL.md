Getty Scholars' Workspace Installation
======================================

This document outlines methods to run the application locally on your personal computer or to do a full installation on a web server.

Test Drive with Docker
----------------------

Getty Scholars' Workspace is a multi-tenant web application, so it is intended to be run on a web server. However, if you'd like to run it on your personal computer just to give it a test drive, you can use Docker to create a virtual server environment and run the Workspace locally. Follow the steps below to give it a spin. Scroll further for real deployment instructions.

1. Install Docker on your machine. Follow instruction on the Docker website: https://www.docker.com/

2. If you are using docker-machine (Mac or Windows) be sure to start it using Docker Quickstart Terminal and take note of the IP address assigned to Docker. Docker is configured to use the default machine with IP 192.168.99.100.

3. At the command line, pull the Getty Scholars' Workspace image.

        $ docker pull thegetty/scholarsworkspace

4. Run the container.

        $ docker run -d -p 8080:80 --name=wkspc thegetty/scholarsworkspace supervisord -n

5. Point your browser to `<ip address>:8080/GettyScholarsWorkspace`. Use the IP address noted in Step 2.

6. The Drupal administrator login is `scholar` and the password is `workspace`. Be sure to change these in the Drupal admin interface.

7. To shut it down, stop the container:

        $ docker stop wkspc



Web Server Installation
-----------------------
These installation instructions assume you are installing Getty Scholars' Workspace on a server (virtual or physical) with a clean new instance of Ubuntu 14.04 as the operating system.

**Method 1: Using Docker**

1. Install Docker on your machine. See instructions here: https://docs.docker.com/engine/installation/linux/ubuntulinux/

2. At the command line, pull the Getty Scholars' Workspace image.

        $ docker pull thegetty/scholarsworkspace:latest

4. Run the container. Set the port to your own preference. The example uses `8080` to avoid clashing with other applications. But if you have no other web apps running, feel free to use `80`.

        $ docker run -d -p 8080:80 --name=wkspc thegetty/scholarsworkspace supervisord -n

5. Point your browser to `<ip address>:8080/GettyScholarsWorkspace`. If you are using a browser directly on the server, use `localhost` for the IP address. If you are using a browser on your local machine, then use the IP address of the target server.

6. The Drupal administrator login is `scholar` and the password is `workspace`. Be sure to change these in the Drupal admin interface.

7. To shut it down, simply stop the container:

        $ docker stop wkspc

8. For production deployment, you should change the MySQL passwords and set up Apache to use https.

**Method 2: Full installtion**

1. Update the package repositories.

        $ sudo apt-get update

2. Install Apache 2 and PHP5.

        $ sudo apt-get install apache2 php5 libapache2-mod-php5 php5-gd vim wget

3. Edit the Apache config file to allow .htaccess overrides.

        $ sudo vim /etc/apache2/apache2.conf

    Find the following section and change `AllowOverride` to `All`
        <Directory /var/www/>
                Options Indexes FollowSymLinks
                AllowOverride All
                Require all granted
        </Directory>

        :wq

4. Enable the rewrite module and start Apache.

        $ sudo a2enmod rewrite
        $ sudo /etc/init.d/apache2 start

5. Install MySQL. When prompted, set the MySQL password for the `root` user.

        $ sudo apt-get install mysql-server libapache2-mod-auth-mysql php5-mysql

6. Start MySQL and login as root user.

        $ sudo /etc/init.d/mysql start
        $ mysql -u root -p

7. Create the database and account permissions for Getty Scholars' Workspace by entering the following commands. Pick your own `<password>` and remember it.

        CREATE DATABASE scholarsworkspace CHARACTER SET utf8 COLLATE utf8_general_ci;

        GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, INDEX, ALTER, CREATE TEMPORARY TABLES ON scholarsworkspace.* TO 'scholar'@'localhost' IDENTIFIED BY '<password>';

        exit;

8. Install Drush (Drupal shell tool).

        $ wget http://files.drush.org/drush.phar
        $ php drush.phar core-status
        $ chmod +x drush.phar
        $ mv drush.phar /usr/local/bin/drush
        $ drush init
        Append the above code to <user home>/.bashrc? (y/n): y
        $ source ~/.bashrc

9. Install Git and clone the Getty Scholars' Workspace repository.

        $ sudo apt-get install git
        $ cd /var/www/html
        $ git clone https://github.com/GettyScholarsWorkspace/GettyScholarsWorkspace
        $ cd GettyScholarsWorkspace

10. Install unzip and build the site.

        $ sudo apt-get install unzip
        $ sudo drush make profiles/getty_scholars_workspace/build-gsw.make
        Make new site in the current directory? (y/n): y
        $ sudo mkdir sites/default/files
        $ sudo chmod 777 sites/default/files
        $ sudo cp sites/default/default.settings.php sites/default/settings.php
        $ sudo chmod 666 sites/default/settings.php

11. Install sendmail for administrator notifications.

        $ sudo apt-get install sendmail

12. Now open the site in your browser and follow the instructions: `http://<your URL or IP address>/install.php`

13. Change the permissions back.

        $ sudo chmod 644 sites/default/settings.php

14. For production deployment, you should set up Apache to use https.
