import DS from 'ember-data';

export default DS.Model.extend({
  programId: DS.belongsTo('program'),
  semesterId: DS.belongsTo('semester'),
  start: DS.attr('date'),
  end: DS.attr('date')
});
