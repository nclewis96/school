import Ember from 'ember';

export default Ember.Route.extend({
	classNames: ['program-coord'],
	model() {
		return 	{
			programCoordinator:	{
				name: 'program-coordinator',
				actionList:	[	{
          actionName: 'Instructors'
        },  {
          actionName: 'Courses'
        },	{
          actionName: 'Outcomes'
        },  {
					actionName: 'Assessments'
				},	{
					actionName: 'Reports'
				}]
			}
		};
	}
});
