const { Component, String: {w}, computed, computed:{equal}, getProperties, } = Ember;

export default Component.extend({
  store: Ember.inject.service(),
  semesterTypeList: computed('store', function(){
    return this.get('store').findAll('semesterType');
  }),
  actions: {
  },
  rules:  {
  }

});
