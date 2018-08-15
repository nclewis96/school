import ApplicationSerializer from './application';

export default ApplicationSerializer.extend({
  attrs: {
    courses: {
      deserialize: 'records',
      serialize: false
    }
  }
});
