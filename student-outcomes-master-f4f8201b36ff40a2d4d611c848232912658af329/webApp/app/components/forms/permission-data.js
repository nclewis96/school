const { Component, String: {w}, computed, computed:{equal}, getProperties, } = Ember;

export default Component.extend({
  store: Ember.inject.service(),
  userList: computed('store', function(){
    return this.get('store').findAll('user');
  }),
  permissionList: computed('store', function(){
    return this.get('store').findAll('role');
  }),
  programList: computed('store', function(){
    return this.get('store').findAll('program');
  }),
  rules:  {
  }

});
