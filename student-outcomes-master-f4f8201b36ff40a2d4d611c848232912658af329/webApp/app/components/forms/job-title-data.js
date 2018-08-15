const { Component, String: {w}, computed, computed:{equal}, getProperties, } = Ember;

export default Component.extend({
  store: Ember.inject.service(),
  userList: computed('store', function(){
    return this.get('store').findAll('user');
  }),
  rules:  {
  }

});
