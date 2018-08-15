import Ember from 'ember';

export default Ember.Route.extend({
	classNames: ['courses'],
	model() {
		return 	{
			programs: [
			{
				semesters: [
				{
					courses:	[
					{
						name: 'MathyStuffy',
						num: '01',
						id:'32345'
					}],
					name: 'Fall 2017',
					id: '32323'
				}],
				name: 'Computer Sciences',
				id: '3232'
			}]
		};
	}

});
