import Component from '@ember/component';

export default Component.extend({
  tagName: 'div',
  classNames: ['container'],
  renderedComponent: Ember.computed('controlType', function() {
    return `forms/form-${this.get('controlType')}`;
  })
});
