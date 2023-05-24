AbuseIPDB report
================

> making the internet safer, one IP at a time
>
> **Report abusive IPs** engaging in hacking attempts or other malicious behavior and help fellow sysadmins!

This module provides reporting capabilities to the [AbuseIPDB](https://www.abuseipdb.com/) database.
You can report an IP to the AbuseIPDB directly from the module's admin UI or
automate the reporting process using pluggable modules like as [Antiscan](https://backdropcms.org/project/antiscan).

Installation
------------
Install this module using the official Backdrop CMS instructions at https://backdropcms.org/guide/modules

**Note:** [PHP cURL](http://php.net/manual/en/curl.setup.php) library needs to be installed on your server.

Configuration and usage
-----------------------
The administration page is available via the *Administration > Configuration >
Web services > AbuseIPDB report* menu (admin/config/services/abuseipdb_report).

You will need your own free [API key](https://www.abuseipdb.com/register).
You can also use multiple keys for different sites.
Immediately after saving this key you can report abusive IPs and enable automated reporting via the Antiscan module (version 1.x-1.0.4 or higher).

**Screenshots** are available at https://findlab.net/projects/abuseipdb-report

Credits
------
Some inspiration comes from the Drupal "AbuseIPDB" module.

License
-------
This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.

Current maintainer
------------------
Vladimir (https://github.com/findlabnet/)

More information
----------------
For bug reports, feature or support requests, please use the module
issue queue at https://github.com/backdrop-contrib/abuseipdb_report/issues.
