import Ember from 'ember';
//import AuthenticatedRouteMixin from 'ember-simple-auth/mixins/authenticated-route-mixin';
import CasAuthenticatedRouteMixin from '../mixins/cas-authenticated-route';

export default Ember.Route.extend(CasAuthenticatedRouteMixin, {
  //autheticationRoute: 'home'
});
