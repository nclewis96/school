import DS from 'ember-data';

export default DS.Model.extend({
  metricId: DS.belongsTo('metric'),
  name: DS.attr('string'),
  description: DS.attr('string')
});
