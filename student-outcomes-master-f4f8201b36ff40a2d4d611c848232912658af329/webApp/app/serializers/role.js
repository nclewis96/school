import ApplicationSerializer from './application';

export default ApplicationSerializer.extend({
  attrs: {
    userId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    permissions: {
      deserialize: 'records',
      serialize: false
    }
  }
});
