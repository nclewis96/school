//*****************TABLES*******************//
//Metric Object
var metricObj{
    metric_id: 0,
    program: programObj,
    outcomes: [outcomeObj,...],
    name: ""
}

//Outcome Object
var outcomeObj{
    outcome_id: 0,
    name: "",
    description: ""
}

//Program Object
var programObj {
    program_id: 0,
    name: ""
}

//Course Prefix Object
var coursePrefixObj {
    prefix_id: 0,
    prefix: ""
}

//Course Object
var courseObj {
    course_id: 0,
    course_num: "",
    prefix: coursePrefixObj,
    course_title: "",
    program: programObj
}

//Program Cutoff Object
var progCutoffObj {
    program: programObj,
    semester: semesterObj,
    start_date: "",
    end_date: ""
}

//Offering Outcome Object
var offOutcome {
    offering: offeringObj,
    outcome: outcomeObj,
    score: 0
}

//Student_outcome Object
var studentOutObj{
    offering: offeringObj,
    outcome: outcomeObj,
    student_id: 0
}

//Offering Student
var offStudent {
    offering: offeringObj,
    student_id: 0,
    student_name: ""
}

//Semester Type Object
var semTypeObj{
    semester_type_id: 0,
    text: "",
    startMonth: ""
}

//Semester Object
var semesterObj {
	semester_id: 0,
	type: semTypeObj,
	year: ""
}

//Offering object
var offeringObj{
    offering_id: 0,
    course: courseObj,
    semester: semesterObj,
}

//Offering Assign Object
var offAssign {
    offering: offeringObj,
    assign: studAssignObj,
    score: 0,
    name: "",
    desc: "",
    max_score: 0
}

//Student Assign

//Job Title Object
var jobTitleObj {
    job_title_id: 0,
    title: ""
}

//User Object
var userObj{
    user_id: 0,
    fname: "",
    lname: "",
    email: "",
    job_title: jobTitleObj,
    user_level: [ProgramPermObj]
}

//Permission Set Object
var permSetObj {
    permission_id: 0,
    table: "",
    permission_level: ""
}

//Program Permissions Object
var ProgramPermObj {
    program_permission_id: 0,
    permission: permSetObj,
    user: userObj,
    program: programObj
}

//Scale Object
var scaleObj {
    scale_id: 0,
    name: "",
    desc: "",
    program: programObj
}

//Perf_Indicator Object
var perIndObj {
    perf_indicator_id: 0,
    scale: scaleObj,
    name: "",
    desc: "",
    rating: ""
}

//Program Outcomes
var progOutcomeObj {
	outcome: outcomeObj[],
	program: programObj
}
