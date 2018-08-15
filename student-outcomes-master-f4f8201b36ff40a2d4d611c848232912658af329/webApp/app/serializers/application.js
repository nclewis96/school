import DS from 'ember-data';

export default DS.JSONSerializer.extend(DS.EmbeddedRecordsMixin,{
  serializeId(snapshot, json, primaryKey) {
    var id = snapshot.id;
    json[primaryKey] = parseInt(id, 10);
  },
  payloadKeyFromModelName(modelName) {
    return modelName;
  },


  serializeRecordArray(store, modelClass, records) {
    let data = records.map(record => {
      return this.serialize(record._createSnapshot());
    });

    return data;
  },


});
