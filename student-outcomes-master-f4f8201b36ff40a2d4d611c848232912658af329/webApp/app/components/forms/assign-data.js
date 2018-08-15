const { Component, String: {w}, computed, computed:{equal}, getProperties, } = Ember;

export default Component.extend({
  store: Ember.inject.service(),
  offeringList: computed('store', function(){
    return this.get('store').findAll('offering');
  }),
  scaleList: computed('store', function(){
    return this.get('store').findAll('scale');
  }),
  rules:  {
  }

});
