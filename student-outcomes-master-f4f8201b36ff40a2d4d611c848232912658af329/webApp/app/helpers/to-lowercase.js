import Ember from 'ember';

export function toLowercase([arg]) {
  return arg.toLowerCase();
}

export default Ember.Helper.helper(toLowercase);
