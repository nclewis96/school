import DS from 'ember-data';

export default DS.Model.extend({
  name: DS.attr('string'),
  userId: DS.belongsTo('user'),
  permissions: DS.hasMany('permission')
});
