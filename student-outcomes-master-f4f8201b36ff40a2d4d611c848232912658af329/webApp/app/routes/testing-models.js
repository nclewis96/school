import Route from '@ember/routing/route';
import CasAuthenticatedRouteMixin from '../mixins/cas-authenticated-route';
const { inject: { service } } = Ember;

export default Route.extend(CasAuthenticatedRouteMixin,{
  currentUser: service(),
	model: function() {
    return Ember.RSVP.hash({
      offerings: this.store.findAll('offering'),
      offering: this.store.findRecord('offering', 1),
      users: this.store.findAll('user'),
      user: this.store.findRecord('user', 1),
      assigns: this.store.findAll('assign'),
      courses: this.store.findAll('course'),
      outcomes: this.store.findAll('outcome'),
      metrics: this.store.findAll('metric'),
      semesters: this.store.findAll('semester'),
      programCutoffs: this.store.findAll('programCutoff'),
      programCutoff: this.store.findRecord('programCutoff', '6/3'),
      offeringsQueried: this.store.query('offering', {
        instructorId  : this.get('currentUser.userId')
      })
    });
	},

	actions: {
    addOffering() {
      this.get('store').createRecord('offering', {
        courseId: '',
        instructorId: '',
        semesterId: '',
        sectionNum: '',
        locked: false,
        numStudents: '',
        instructorName: '',
        scales: ''
      });

    },
	addUser() {
	  this.get('store').createRecord('user', {
		    name: '',
			username: ''
	  });
	},
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
