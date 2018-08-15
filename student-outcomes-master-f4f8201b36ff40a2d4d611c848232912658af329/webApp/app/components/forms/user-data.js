const { Component, String: {w}, computed, computed:{equal}, getProperties, } = Ember;

export default Component.extend({
  store: Ember.inject.service(),

  jobTitleList: computed('store', function(){
    return this.get('store').findAll('jobTitle');
  }),
  roleList: computed('store', function(){
    return this.get('store').findAll('role');
  }),
});
