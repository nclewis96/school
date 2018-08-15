import ApplicationSerializer from './application';

export default ApplicationSerializer.extend({
  attrs: {
    courseId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    instructorId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    semesterId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    scales: {
      deserialize: 'records',
      serialize: false
    }
  }
});
