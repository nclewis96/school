import ApplicationSerializer from './application';

export default ApplicationSerializer.extend({
  attrs: {
    permissionId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    userId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    programId: {
      deserialize: 'records',
      serialize: 'ids'
    }
  }
});
