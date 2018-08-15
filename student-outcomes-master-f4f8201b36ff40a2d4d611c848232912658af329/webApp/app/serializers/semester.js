import ApplicationSerializer from './application';

export default ApplicationSerializer.extend({
  attrs: {
    typeId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    programCutoffs: {
      deserialize: 'records',
      serialize: false
    }
  }
});
