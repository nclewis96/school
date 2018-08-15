import DS from 'ember-data';

export default DS.Model.extend({
  offeringId: DS.belongsTo('offering'),
  scaleId: DS.belongsTo('scale'),
  score: DS.attr('number'),
  name: DS.attr('string'),
  desc: DS.attr('string'),
  maxScore: DS.attr('number')

});
