import DS from 'ember-data';

export default DS.Model.extend({
  programId: DS.belongsTo('program'),
  name: DS.attr('string'),
  outcomes: DS.hasMany('outcome')
});
