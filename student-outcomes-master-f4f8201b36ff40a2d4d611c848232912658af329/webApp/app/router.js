import Ember from 'ember';
import config from './config/environment';

const Router = Ember.Router.extend({
  location: config.locationType,
  rootURL: config.rootURL
});

Router.map(function() {
  this.route('home');
  this.route('admin', function() {
    this.route('users');
    this.route('courses');
    this.route('outcomes');
    this.route('students');
    this.route('reports');
  });
  this.route('program-coordinator', function() {
    this.route('assessments');
    this.route('outcomes');
    this.route('courses');
    this.route('instructors');
    this.route('reports');
  });
  this.route('faculty', function() {
    this.route('courses');
    this.route('metrics');
    this.route('students');
    this.route('reports');
  });
  this.route('observer', function() {
    this.route('courses');
    this.route('outcomes');
    this.route('reports');
  });
  this.route('secret');
  this.route('unauthorizedUser');
  this.route('unauthorized-user');
  this.route('testing-models');

  this.route('protos', function() {});
  this.route('testing-models2');
  this.route('testing-nav');
});

export default Router;
