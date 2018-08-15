import Ember from 'ember';
const { inject: { service } } = Ember;
export default Ember.Controller.extend({
  session: Ember.inject.service('session'),
  currentUser: service('currentUser'),
  queryParams: ['ticket'],
  ticket: null,
  init() {
    "use strict";

    this._super(...arguments);
    let session = this.get('session');
    let store = session.get('store');

    if (store) {
      store.restore().then((data) => {
        if (Ember.isPresent(data.authenticated.jwt)) {
          this.send('login');
        }
      }).catch(() => {
        this.get('session.store').clear();
      }).finally(() => {
      });
    }
  },

  actions:{
    login() {
      let session = this.get('session');
      let user = session.get('data.authenticated');
      session.get('store').persist(user);
      this.set('currentUser', user);
      console.log("Welcome back, " + user.user.name);
    }
  }
});
