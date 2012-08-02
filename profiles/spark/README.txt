To build the profile, run:

drush make build-spark.make /path/to/wwwroot

This will assemble a copy of Drupal core with the latest copy of the Spark
distro files from Git, along with all of its dependencies.

There are two other .make files, which are called from the "build" one:

- drupal-org-core.make:
  This file just contains the definition for how to package Drupal core. We
  hopefully shouldn't have to edit this much, unless we need to add additional
  core patches.

- drupal-org.make:
  This file is where the bulk of the work happens; contributed modules/themes,
  external libraries, non-core patches, etc. are all handled here.

See http://drupal.org/developing/distributions for the longer version of these
instructions. :)

