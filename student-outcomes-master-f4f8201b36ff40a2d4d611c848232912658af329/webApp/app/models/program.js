import DS from 'ember-data';

export default DS.Model.extend({
  name: DS.attr('string'),
  metrics: DS.hasMany('metric'),
  permissions: DS.hasMany('permission'),
  users: computed('permissions.@each.users', {
    get() { return this.permissions.map(p => p.users).reduce((a,b) => [...a,...b], []); }
  }),
});
