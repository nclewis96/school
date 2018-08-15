import ApplicationSerializer from './application';

export default ApplicationSerializer.extend({
  attrs: {
    metricId: {
      deserialize: 'records',
      serialize: 'ids'
    }
  }
});
