import DS from 'ember-data';

export default DS.Model.extend({
  typeId: DS.belongsTo('semesterType'),
  year: DS.attr('number'),
  programCutoffs: DS.hasMany('programCutoff')
});
