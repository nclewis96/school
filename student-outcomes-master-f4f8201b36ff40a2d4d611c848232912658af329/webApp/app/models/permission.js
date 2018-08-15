import DS from 'ember-data';

export default DS.Model.extend({
  permissionId: DS.belongsTo('role'),
  userId: DS.belongsTo('user'),
  programId: DS.belongsTo('program')
});
