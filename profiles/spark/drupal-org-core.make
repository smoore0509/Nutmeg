; A separate drupal-org-core.make file makes it so we can apply core patches
; if we need to.

api = 2
core = 7.x
projects[drupal][type] = core
projects[drupal][version] = 7.14

; Core patches.
projects[drupal][patch][1637480] = http://drupal.org/files/1637480-1.patch

