import DS from 'ember-data';

export default DS.Model.extend({
  name: DS.attr('string'),
  username: DS.attr('string'),
  jobTitle: DS.belongsTo('jobTitle'),
  roles: DS.hasMany('role'),
  permissions: DS.hasMany('permission')
});
