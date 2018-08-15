import Component from '@ember/component';

export default Component.extend({
  tagName: 'div',
  classNames: ['container'],

  renderedComponent: Ember.computed('permission', function() {
    return `displays/${this.get('permission')}-view`;
  })
});
