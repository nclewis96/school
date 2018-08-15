import Ember from 'ember';
const { inject: { service } } = Ember;
import DS from 'ember-data';
import CasAuthenticatedRouteMixin from '../mixins/cas-authenticated-route';
import ENV from 'st-out/config/environment';
const { copy } = Ember;
const { Promise } = Ember.RSVP;
export default DS.JSONAPIAdapter.extend(CasAuthenticatedRouteMixin, {
  currentUser: service(),
  jwt: Ember.computed('currentUser', function(){
    return `Bearer ${this.get('currentUser.token')}`;
  }),
  host: ENV.APP.backendURL,
  headers: Ember.computed('jwt', function(){
    return{
    'Accept': 'application/json',
    'Authorization': this.get('jwt')
    };
  }),

  batchCreateForHasMany(store, modelName, relationshipName, records, parentRecord) {
    let modelClass = store.modelFor(modelName);
    let serializer = store.serializerFor(modelName);
    let serialized = serializer.serializeRecordArray(store, modelClass, records);
    let url = this.urlForPutHasMany(ENV.APP.backendURL, relationshipName);
    let params = {
      processData: false,
      data: serialized
    };

    this.ajax(url, "PUT", params)
      .then((jsonApiPayload) => {
        let normalized = serializer.normalizeResponse(store, modelClass, jsonApiPayload, null, 'query');
        store.push(normalized);
      });
  },

  urlForPutHasMany(host, relationshipName) {
    return `${host}/${relationshipName}`;
  }
});
