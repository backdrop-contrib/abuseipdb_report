AbuseIPDB report
================

> making the internet safer, one IP at a time  
> **Report abusive IPs** engaging in hacking attempts or other malicious behavior and help fellow sysadmins!

This module provides reporting ability to the [AbuseIPDB](https://www.abuseipdb.com/) database.
You can report an IP directly to AbuseIPDB from module admin UI or 
automate the reporting process using pluggable modules such as [Antiscan](https://backdropcms.org/project/antiscan).

Installation
------------
Install this module using the official Backdrop CMS instructions at https://backdropcms.org/guide/modules  
**Please note:** [PHP cURL](http://php.net/manual/en/curl.setup.php) library must be installed on your server. 

Configuration and usage
-----------------------
Administration page is available via menu *Administration > Configuration > Web services > AbuseIPDB report* (admin/config/services/abuseipdb_report). 

You need your own free [API key](https://www.abuseipdb.com/register).  
Right after saving this key you can report abusive IP and enable automated reporting in the Antiscan module (version 1.x-1.0.4 or above).

Credit
------
Some inspiration comes from the Drupal "AbuseIPDB" module.

License
-------
This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.

Current Maintainer
------------------
Vladimir (https://github.com/findlabnet/)

More information
----------------
For bug reports, feature or support requests, please use the module 
issue queue at https://github.com/backdrop-contrib/abuseipdb_report/issues.
