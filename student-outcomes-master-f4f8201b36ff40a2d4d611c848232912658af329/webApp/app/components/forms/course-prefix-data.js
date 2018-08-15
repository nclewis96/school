const { Component, String: {w}, computed, computed:{equal}, getProperties, } = Ember;

export default Component.extend({
  store: Ember.inject.service(),
  courseList: computed('store', function(){
    return this.get('store').findAll('course');
  }),
  rules:  {
  }

});
