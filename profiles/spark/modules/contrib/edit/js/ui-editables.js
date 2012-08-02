(function($) {

/**
 * @file ui-editables.js
 *
 * UI components for editables: toolbar, form.
 */

Drupal.edit = Drupal.edit || {};


Drupal.edit.toolbar = {
  create: function($editable) {
    if (Drupal.edit.toolbar.get($editable).length > 0) {
      return false;
    }
    else {
      // Render toolbar.
      var $toolbar = $(Drupal.theme('editToolbarContainer', {
        id: this._id($editable)
      }));

      // Insert in DOM.
      if ($editable.css('display') == 'inline') {
        $toolbar.prependTo($editable.offsetParent());

        var pos = $editable.position();
        Drupal.edit.toolbar.get($editable)
        .css('left', pos.left).css('top', pos.top);
      }
      else {
        $toolbar.insertBefore($editable);
      }

      // Remove any and all existing toolbars, except for any that are for a
      // currently being edited field.
      $('.edit-toolbar-container:not(:has(.edit-editing))')
      .trigger('edit-toolbar-remove.edit');

      // Event bindings.
      $toolbar
      .bind('mouseenter.edit', function(e) {
        // Prevent triggering the entity's mouse enter event.
        e.stopPropagation();
      })
      .bind('mouseleave.edit', function(e) {
        var el = $editable[0];
        if (e.relatedTarget != el && !jQuery.contains(el, e.relatedTarget)) {
          console.log('triggering mouseleave on ', $editable);
          $editable.trigger('mouseleave.edit');
        }
        // Prevent triggering the entity's mouse leave event.
        e.stopPropagation();
      })
      // Immediate removal whenever requested.
      // (This is necessary when showing many toolbars in rapid succession: we
      // don't want all of them to show up!)
      .bind('edit-toolbar-remove.edit', function(e) {
        $toolbar.remove();
      });

      return true;
    }
  },

  get: function($editable) {
    return ($editable.length == 0)
      ? $([])
      : $('#' + this._id($editable));
  },

  remove: function($editable) {
    var $toolbar = Drupal.edit.toolbar.get($editable);

    // Remove after animation.
    $toolbar
    // Prevent this toolbar from being detected *while* it is being removed.
    .removeAttr('id')
    .find('.edit-toolbar .edit-toolgroup')
    .addClass('edit-animate-invisible')
    .bind(Drupal.edit.const.transitionEnd, function(e) {
      $toolbar.remove();
    });
  },

  // Animate into view.
  show: function($editable, toolbar, toolgroup) {
    Drupal.edit.toolbar.get($editable)
    .find('.edit-toolbar.' + toolbar + ' .edit-toolgroup.' + toolgroup)
    .removeClass('edit-animate-invisible');
  },

  _id: function($editable) {
    var edit_id = ($editable.hasClass('edit-entity'))
      ? Drupal.edit.getID($editable)
      : Drupal.edit.getID(Drupal.edit.findFieldForEditable($editable));
    return 'edit-toolbar-for-' + edit_id.split(':').join('_');
  }
};


Drupal.edit.form = {
  create: function($editable) {
    if (Drupal.edit.form.get($editable).length > 0) {
      return false;
    }
    else {
      // Render form container.
      var $form = $(Drupal.theme('editFormContainer', {
        id: this._id($editable),
        loadingMsg: Drupal.t('Loading…')}
      ));

      // Insert in DOM.
      if ($editable.css('display') == 'inline') {
        $form.prependTo($editable.offsetParent());

        var pos = $editable.position();
        $form.css('left', pos.left).css('top', pos.top);
        // Reset the toolbar's positioning because it'll be moved inside the
        // form container.
        Drupal.edit.toolbar.get($editable).css('left', '').css('top', '');
      }
      else {
        $form.insertBefore($editable);
      }

      // Move  toolbar inside .edit-form-container, to let it snap to the width
      // of the form instead of the field formatter.
      Drupal.edit.toolbar.get($editable).detach().prependTo('.edit-form')

      return true;
    }
  },

  get: function($editable) {
    return ($editable.length == 0)
      ? $([])
      : $('#' + this._id($editable));
  },

  remove: function($editable) {
    Drupal.edit.form.get($editable).remove();
  },

  _id: function($editable) {
    var edit_id = ($editable.hasClass('edit-entity'))
      ? Drupal.edit.getID($editable)
      : Drupal.edit.getID(Drupal.edit.findFieldForEditable($editable));
    return 'edit-form-for-' + edit_id.split(':').join('_');
  }
};

})(jQuery);
