import { module, test } from 'qunit';
import { setupTest } from 'ember-qunit';

module('Unit | Route | testing-nav', function(hooks) {
  setupTest(hooks);

  test('it exists', function(assert) {
    let route = this.owner.lookup('route:testing-nav');
    assert.ok(route);
  });
});
