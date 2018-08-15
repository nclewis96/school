const { Component, String: {w}, computed, computed:{equal}, getProperties, } = Ember;

export default Component.extend({
  store: Ember.inject.service(),
  courseList: computed('store', function(){
    return this.get('store').findAll('course');
  }),
  instructorList: computed('store', function(){
    return this.get('store').findAll('user');
  }),
  semesterList: computed('store', function(){
    return this.get('store').findAll('semester');
  }),
  rules:  {
    courseId: 'required',
    instructorId: 'required',
    instructorName: 'required',
    semesterId: 'required',
    sectionNum: 'required',
    locked: 'required',
    numStudents: 'required'

  }

});
