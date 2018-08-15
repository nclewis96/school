import Ember from 'ember';

import CasAuthenticatedRouteMixin from '../../mixins/cas-authenticated-route';
const { inject: { service } } = Ember;
export default Ember.Route.extend(CasAuthenticatedRouteMixin, {
  currentUser: service(),
  model: function() {
    let store = this.get('store');
    return Ember.RSVP.hash({
      programs: store.query('permission', {
        userId: this.get('currentUser.userId')
      }).then(function (permissions) {
        return Ember.RSVP.all(permissions.map(function (permission) {
          const program = store.findRecord('program', permission.get('programId.id')).then(function (program) {
            return program
          });
          const users = store.query('permission', {
            programId: permission.get('programId.id')
          }).then(function (permissionUsers) {
            return Ember.RSVP.all(permissionUsers.map(function (permissionUser) {
              return store.findRecord('user', permissionUser.get('userId.id'));
            }));
          });
          return Ember.RSVP.hash({program, users: users});
        }))
      })
    })
  }
});
