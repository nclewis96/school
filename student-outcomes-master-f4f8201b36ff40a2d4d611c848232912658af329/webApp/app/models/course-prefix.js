import DS from 'ember-data';

export default DS.Model.extend({
  prefix: DS.attr('string'),
  courses: DS.hasMany('course')
});
