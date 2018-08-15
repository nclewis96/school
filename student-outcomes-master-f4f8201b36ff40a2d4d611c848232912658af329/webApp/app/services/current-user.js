import Ember from 'ember';

const { inject: { service } } = Ember;
export default Ember.Service.extend({
  _session: service('session'),
  userId: Ember.computed('_session.data.authenticated', function() {
    "use strict";
    let user = this.get('_session.data.authenticated');
    return (user ? user.user.id : -1);
  }),
  name: Ember.computed('_session.data.authenticated', function() {
    "use strict";
    let user = this.get('_session.data.authenticated');
    return (user ? user.user.name : "");
  }),
  token: Ember.computed('_session.data.authenticated', function() {
    "use strict";
    let user = this.get('_session.data.authenticated');
    return (user ? user.jwt : "");
  }),
  userType: Ember.computed('_session.data.authenticated', function() {
    "use strict";
    let user = this.get('_session.data.authenticated');
    return (user ? user.user_type : "");
  }),
  data: Ember.computed('_session.data.authenticated', function() {
    "use strict";
    let user = this.get('_session.data.authenticated');
    return (user ? user.user : null);
  }), 
  username: Ember.computed('_session.data.authenticated', function() {
    "use strict";
    let user = this.get('_session.data.authenticated');
    return (user ? user.username : "");
  }), 
  title: Ember.computed('_session.data.authenticated', function() {
    "use strict";
    let user = this.get('_session.data.authenticated');
    return (user ? user.user.jobTitle.title : "");
  }), 
  roleList: Ember.computed('_session.data.authenticated', function() {
    "use strict";
    let user = this.get('_session.data.authenticated');
    return (user ? user.user.roleList : null);
  }) 
});
