
const { Component, String: {w}, computed, computed:{equal}, getProperties, } = Ember;
export default Component.extend({
	saved: false,
  classNames: ['container'],

model:{

	offering_id: null,
	outcome_id: null,
	student_id: null,
	score: null,
},




rules: computed('showAdmin', 'showFaculty', function() {

const {showFaculty, showAdmin} = getProperties(this, 'showAdmin', 'showFaculty');
const additionalField = showFaculty ? 'companyName' : 'universityName';

return{

sharedValidation: {
	required: w('offering_id outcome_id student_id userType ${additionalField}'),
},

}

}),

actions: {
	submit() {
		this.set('saved', true);
		console.log("json:");
		console.log(JSON.stringify(this.model, null, "  "));
	}
}

});



/**
 * A handler function to prevent default submission and run our custom script.
 * @param  {Event} event  the submit event triggered by the user
 * @return {void}
 */
const handleFormSubmit = event => {

  // Stop the form from submitting since we’re handling that with AJAX.
  event.preventDefault();


  console.log(JSON.stringify(model, null, "  "));

  // ...this is where we’d actually do something with the form data...
};

