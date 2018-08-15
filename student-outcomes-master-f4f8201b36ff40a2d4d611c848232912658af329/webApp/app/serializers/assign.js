import ApplicationSerializer from './application';

export default ApplicationSerializer.extend({
  attrs: {
    offeringId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    scaleId: {
      deserialize: 'records',
      serialize: 'ids'
    }
  }
});
