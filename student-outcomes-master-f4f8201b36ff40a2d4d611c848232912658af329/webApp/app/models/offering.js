import DS from 'ember-data';
import './singular-plural-rules';

export default DS.Model.extend({
	courseId: DS.belongsTo('course'),
	instructorId: DS.belongsTo('user'),
	semesterId: DS.belongsTo('semester'),
	sectionNum: DS.attr('string'),
	locked: DS.attr('boolean'),
	numStudents: DS.attr('number'),
  instructorName: DS.attr('string'),
  scales: DS.hasMany('scale'),
  name: Ember.computed('courseId.title', 'sectionNum', function(){
      return `${this.get('courseId.title')} ${this.get('sectionNum')}`
	  })

});
