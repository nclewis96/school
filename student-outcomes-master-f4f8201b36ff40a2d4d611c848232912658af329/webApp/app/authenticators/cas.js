import Ember from 'ember';
import BaseAuthenticator from 'ember-simple-auth/authenticators/base';
import ENV from '../config/environment';

export default BaseAuthenticator.extend({
  serverTokenEndpoint: ENV.APP.casURL,
  backendEndpoint: ENV.APP.backendURL + '/login',
  session: Ember.inject.service(),
  authenticate : function(data){
    "use strict";
    let backendEndpoint = this.get('backendEndpoint');
    return new Ember.RSVP.Promise((resolve, reject) => {
      Ember.$.ajax({
        type: 'POST',
        contentType: 'application/json',
        url: backendEndpoint,
        data: JSON.stringify({
          jwt: data.jwt,
          ticket: data.ticket,
          service: ENV.APP.frontendURL + '/secret'
        })
      }).done((response) => {
        Ember.run(() => {
          resolve({ username: response.username, jwt:response.jwt, user: response.user });
        });
      }).fail((xhr/* , status, error */) => {
        var response = xhr.responseText;
        Ember.run(() => {
          try{
            reject(JSON.parse(response));
          }catch(error){
            reject(error);
          }
        });
      });
    });
  },
  restore(data) {
    "use strict";

    return new Ember.RSVP.Promise((resolve, reject) => {
      if (!Ember.isEmpty(data.jwt)) {
        resolve(data.user);
      }
      else {
        reject();
      }
    });
  }
});

