import Route from '@ember/routing/route';
import CasAuthenticatedRouteMixin from '../mixins/cas-authenticated-route';
const { inject: { service } } = Ember;

export default Route.extend(CasAuthenticatedRouteMixin,{
  currentUser: service(),
  model: function() {
    const store = this.store;
    return Ember.RSVP.hash({
      assigns: store.findAll('assign'),
      coursePrefixes: store.findRecord('permission', this.get('currentUser.userId')).then(function (permission) {
          return store.query('coursePrefix', {
            programId: permission.get('programId').get('id')
          })
        }),
      jobTitles: store.findAll('jobTitle'),
      permissions: store.findAll('permission'),
      metrics: store.findAll('metric')

    });
  },

  actions: {
    submitRecord(data) {

      let store = this.get('store');
      data.eachRelationship(function (name, descriptor) {
        if (descriptor.kind === 'hasMany') {

          let relatedObject = data.get(name);
          let adapter = store.adapterFor(data.constructor.modelName);

          // what would be a more generic case
          // adapter.batchCreate(store, grades.toArray());

          // better for the hasMany case
          adapter.batchCreateForHasMany(store, descriptor.type, name, relatedObject.toArray(), data);
        }
      });
      if(data.hasDirtyAttributes)
        data.save();
    },
    deleteRecord(data) {
      data.destroyRecord();
    }
  }
});
