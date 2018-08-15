import DS from 'ember-data';

export default DS.Model.extend({
  text: DS.attr('string'),
  startMonth: DS.attr('string'),
  semesters: DS.hasMany('semester')
});
