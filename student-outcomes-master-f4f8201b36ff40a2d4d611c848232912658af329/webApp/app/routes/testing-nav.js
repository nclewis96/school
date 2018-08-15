import Route from '@ember/routing/route';
import CasAuthenticatedRouteMixin from "../mixins/cas-authenticated-route";
const { inject: { service } } = Ember;

export default Route.extend(CasAuthenticatedRouteMixin,{
  currentUser: service(),
  model: function() {
    let store = this.get('store');
    return Ember.RSVP.hash({
      programs: store.query('permission', {
        userId: this.get('currentUser.userId')
      }).then(function (permissions) {
        return Ember.RSVP.all(permissions.map(function (permission) {
          const program = store.findRecord('program', permission.get('programId.id')).then(function (program) {
            return program;
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
          /*
                    var programCutoffsPromises = programs.getEach('programCutoffs');
                    console.log('program ', programs);
                    console.log(programCutoffsPromises);
                    Ember.RSVP.all(programCutoffsPromises).then(function(programCutoffsCollections) {
                      console.log(programCutoffsCollections);
                      programCutoffsCollections.forEach(function (programCutoff){
                        console.log(programCutoff.semesterId.id);
                        return store.findRecord('semester', programCutoff.semesterId.id).then(function(semester){
                          console.log(semester);
                          var offeringsPromises = semester.getEach('offerings');

                          return Ember.RSVP.all(offeringsPromises).then(function (offeringsCollections) {
                            var offerings = offeringsCollections.reduce(function (sum, val) {
                              return sum.pushObjects(val.toArray());
                            }, []);
                            console.log(offerings);
                          })


                        })
                      })
                    })*/
          //  })
 // }

  });
