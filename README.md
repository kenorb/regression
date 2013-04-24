Regression
==========

Drupal module for regression site testing.


Usage
=====

  Open module configuration page.

  Go into /admin/config/regression/paths.

  Click "Add new path" button. You will be redirected to the page of path
  configurator.

  Enter list of pages which should be included or excluded from regression
  testing. You may use '%' character to describe dynamic parameters.

   - Now you have to describe some more settings:

      * How to identify that the page is unique (using predefined keys)

          Built-in (predefined) keys:

            - Domain name

            - Site name

            - Page path

            - Page arguments
                (If page arguments contain at least one '%' dynamic parameter
                then here we would see checkboxes to enable/disable their
                uniqueness) so pages with different dynamic parameter value can
                be treated as the same page.

               Unique parameters: node / [X] % / edit

            - Page callback name

            - User roles' IDs

          You can provide custom keys using hook_regression_build_key hook.

          Note that built-in keys should be selected from the above list if they
          apply to your need. By adding it in hook_regression_build_key you
          could break it's dynamic functionality (Today's or future. Currently
          "page arguments" is the complex one and you should use its built-in
          implementation).
           
      * [ ] Require approval/disapproval description

      * Where to send notifications about changes
      
         [X] Override general module configuration
         
            [ ] Send to the page administrators
            
            [ ] Send to recipients configured in general module configuration
                screen
            
         Send to:
         
            [johnny.b@example.com     ]
            [                         ]
            [                         ]

            

  When change has been made you will receive an e-mail that contain link for
  approval or disapproval page which contain of:

   - List of changes
   
      (List of differences between last and new version of the page content)
   
   - Available actions
   
      ( ) Approve the change and set the page as default
      
      ( ) Mark that change as dynamic (ignore it in the future)
      
           TODO: We probably want user to select portions of text that are
                 dynamic.

           IDEA: To support this kind of content ignoring we need to hold html
                 source for at least the previously created and current
                 revision.
                 
                 Show DOM's tree of the page's HTML source and
                 color the changes. Now user may click on the DOM container(s)
                 (div, span, ul, etc.) and thus provide XPath for the ignored
                 content(which is then removed from all revisions).
                 
                 Note that html will be needed only for the pages that have
                 ignored XPaths. After adding ignored XPath(s) all revisions
                 without html source becomes useless and may be removed from the
                 database.
                 
                 
      
      (*) Mark as regression
      
      ( ) Mark as broken
  
   [X] Description of approval/disapproval (If "Require approval/disapproval
       description" has been selected for the page then it becomes required)
   
      * Description
     
      * Priority (minor, major, blocker)
     
      * Module name (optional)
     
      * URL for bug tracker
     
      * Assignee (responsible)
   
Ignoring changes
================

  You may decide to ignore some changes per path configuration or per page entry.

  Path configuration ignores may be applied only by adding custom regular expressions as its page entries may totally differ in code produced.

  Page entry ignores may be applied by adding custom regular expressions or by inserting predefined expressions in diff's insert/delete fragments.

  E.g.:

    - Navigate to the revision candidate review page
    - Select "Mark that change as dynamic (ignore it in the future)"

    - Now we're able to modify working page text content and we can add some ignores.

      Difference between last working version of the page:
      (difference will be automatically updated as you edit last working page revision)

    firstly:
      [ <del>Welcome</del><ins>Hello</ins> world.                   ]
     then:
      [ No changes detected.                                        ]
      
    - You may also click on the deletion fragment to make it ignored - it will modify last working page content currently edited

      Editing last working page revision:

      [ [ignore]Welcome[/ignore] world.                             ]
      [                                                             ]

      Regular expression ignores:

      [ \* Edit.*?Skip to main content[^\n]+\n                      ]
      [                                                             ]




Technical notes
===============

  Regression entries are added for every unique page (identified using
  predefined parameters(keys)). There is a configuration screen that precedes
  adding a regression entry where we configure regression entry keys used to
  identify uniqueness of page.

  Regression revisions are added for every entity entry of which content has
  changed.

  Regression entries list are located on /admin/config/regression/paths.
  Regression entry editing is on /admin/config/regression/paths/%/edit.
  Regression revisions may be displayed on /admin/config/regression/revisions/%.
