import ApplicationSerializer from './application';

export default ApplicationSerializer.extend({
  attrs: {
    prefixId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    programId: {
      deserialize: 'records',
      serialize: 'ids'
    }
  }
});
