import ApplicationSerializer from './application';

export default ApplicationSerializer.extend({
  attrs: {
    programId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    outcomes: {
      deserialize: 'records',
      serialize: false
    }
  }
});
