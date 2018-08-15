import DS from 'ember-data';

export default DS.Model.extend({
  courseNum: DS.attr('string'),
  prefixId: DS.belongsTo('coursePrefix'),
  title: DS.attr('string'),
  programId: DS.belongsTo('program')
});
