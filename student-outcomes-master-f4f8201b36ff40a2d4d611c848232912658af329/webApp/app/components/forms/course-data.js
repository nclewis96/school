const { Component, String: {w}, computed, computed:{equal}, getProperties, } = Ember;

export default Component.extend({
  store: Ember.inject.service(),
  programList: computed('store', function(){
    return this.get('store').findAll('program');
  }),
  prefixList: computed('store', function(){
    return this.get('store').findAll('coursePrefix');
  }),
  rules:  {
  }

});
