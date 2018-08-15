import ApplicationSerializer from './application';

export default ApplicationSerializer.extend( {
  attrs: {
    jobTitle: {
      deserialize: 'records',
      serialize: 'ids'
    },
    roles: {
      deserialize: 'records',
      serialize: false
    },
    permissions: {
      deserialize: 'records',
      serialize: false
    }
  }
});
