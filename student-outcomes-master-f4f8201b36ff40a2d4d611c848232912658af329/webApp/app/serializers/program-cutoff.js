import ApplicationSerializer from './application';

export default ApplicationSerializer.extend({
  attrs: {
    semesterId: {
      deserialize: 'records',
      serialize: 'ids'
    },
    programId: {
      deserialize: 'records',
      serialize: 'ids'
    }
  },
  serialize(snapshot, options) {
    return {
      programId: snapshot.belongsTo('programId').id,
      semesterId: snapshot.belongsTo('semesterId').id,
      start: snapshot.attr('start'),
      end: snapshot.attr('end')
    };
  },
  normalize(typeClass, rawPayload){
    rawPayload.id = rawPayload.programId + '/' + rawPayload.semesterId;
    return this._super.apply(this, arguments);
  }
});
