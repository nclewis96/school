USE Stout;
DROP TABLE IF EXISTS Course_Outcome;
DROP TABLE IF EXISTS Offering_Outcome;
DROP TABLE IF EXISTS Student_Assign;
DROP TABLE IF EXISTS Offering_Student;
DROP TABLE IF EXISTS Student_Outcome;
DROP TABLE IF EXISTS Outcome_Assign; 
DROP TABLE IF EXISTS Outcome;
DROP TABLE IF EXISTS Metric;
DROP TABLE IF EXISTS Program_Cutoff;
DROP TABLE IF EXISTS Offering_Assign;
DROP TABLE IF EXISTS Offering;
DROP TABLE IF EXISTS Semester;
DROP TABLE IF EXISTS Course;
DROP TABLE IF EXISTS Course_Prefix;
DROP TABLE IF EXISTS Program_Permissions;
DROP TABLE IF EXISTS Users;
DROP TABLE IF EXISTS Roles;
DROP TABLE IF EXISTS Semester_Type;
DROP TABLE IF EXISTS Perf_Indicator;
DROP TABLE IF EXISTS Scale;
DROP TABLE IF EXISTS Program;
DROP TABLE IF EXISTS Job_Title;
DROP TABLE IF EXISTS Config;

SET time_zone = "-06:00";

CREATE TABLE `Metric` (
  `metric_id` int(11) NOT NULL AUTO_INCREMENT,
  `program_id` int(11) NOT NULL,
  `name` varchar(100),
  PRIMARY KEY (`metric_id`)
);

CREATE TABLE `Outcome` (
  `outcome_id` int(11) NOT NULL AUTO_INCREMENT,
  `metric_id` int(11) NOT NULL,
  `name` varchar(100) NOT NULL,
  `description` varchar(200) NOT NULL,
  PRIMARY KEY(`outcome_id`)
);

CREATE TABLE `Outcome_Assign` (
	`outcome_id` int(11) NOT NULL,
	`assign_id` int(11) NOT NULL,
	PRIMARY KEY(`outcome_id`, `assign_id`)
);

CREATE TABLE `Program` (
  `program_id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(30) NOT NULL,
  PRIMARY KEY (`program_id`)
);

CREATE TABLE `Course_Prefix` (
  `prefix_id` int(11) NOT NULL AUTO_INCREMENT,
  `prefix` varchar(4),
  PRIMARY KEY (`prefix_id`)
);

CREATE TABLE `Course` (
  `course_id` int(11) NOT NULL AUTO_INCREMENT,
  `course_num` varchar(6) NOT NULL,
  `prefix_id` int(11) NOT NULL,
  `title` varchar(100) NOT NULL,
  `program_id` int(11) NOT NULL,
  PRIMARY KEY(`course_id`)
);

CREATE TABLE `Course_Outcome` (
  `course_id` int(11) NOT NULL,
  `outcome_id` int(11) NOT NULL,
  PRIMARY KEY (`course_id`, `outcome_id`)
);

CREATE TABLE `Program_Cutoff` (
  `program_id` int(11) NOT NULL,
  `semester_id` int(11) NOT NULL,
  `start_date` DATE NOT NULL,
  `end_date` DATE NOT NULL,
  PRIMARY KEY(`program_id`, `semester_id`)
);

CREATE TABLE `Offering_Outcome` (
  `offering_id` int(11) NOT NULL,
  `outcome_id` int(11) NOT NULL,
  `score` DOUBLE NOT NULL,
  PRIMARY KEY(`offering_id`, `outcome_id`)
);

CREATE TABLE `Student_Outcome` (
  `offering_id` int(11) NOT NULL,
  `outcome_id` int(11) NOT NULL ,
  `student_id` int(11) NOT NULL,
  `score` DOUBLE NOT NULL,
  PRIMARY KEY(`student_id`, `outcome_id`, `offering_id`)
);

CREATE TABLE `Offering_Student` (
  `student_id` int(11) NOT NULL AUTO_INCREMENT,
  `offering_id` int(11) NOT NULL,	
  `student_name` varchar(100) NOT NULL,
  PRIMARY KEY(`student_id`)
);

CREATE TABLE `Semester_Type` (
  `semester_type_id` int(11) NOT NULL AUTO_INCREMENT,
  `text` varchar(100) NOT NULL,
  `startMonth` varchar(100) NOT NULL,
  PRIMARY KEY(`semester_type_id`)
);

CREATE TABLE `Semester` (
  `semester_id` int(11) NOT NULL AUTO_INCREMENT,
  `semester_type_id` int(11) NOT NULL,
  `year` varchar(100) NOT NULL,
  PRIMARY KEY(`semester_id`)
);

CREATE TABLE `Offering` (
  `offering_id` int(11) NOT NULL AUTO_INCREMENT,
  `course_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `semester_id` int(11) NOT NULL,
  `section_num` varchar(4)  NOT NULL,
  `locked` BIT NOT NULL,
  `num_students` int(11),
  PRIMARY KEY(`offering_id`)
);

CREATE TABLE `Offering_Assign` (
	`assign_id` int(11) NOT NULL AUTO_INCREMENT,
	`offering_id` int(11) NOT NULL,
	`score` int(11) NOT NULL,
	`name` varchar(100) NOT NULL,
	`desc` varchar(100) NOT NULL,
	`max_score` int(11)  NOT NULL,
	PRIMARY KEY(`assign_id`)
);

CREATE TABLE `Student_Assign` (
	`assign_id` int(11) NOT NULL,
	`student_id` int(11) NOT NULL,
	`score` int(11) NOT NULL,
	PRIMARY KEY(`assign_id`, `student_id`)
);

CREATE TABLE `Job_Title` (
  `job_title_id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(100) NOT NULL,
  PRIMARY KEY(`job_title_id`)
);

CREATE TABLE `Users` (
  `user_id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `username` varchar(100) NOT NULL,
  `job_title_id` int(11) NOT NULL,
  PRIMARY KEY(`user_id`)
);

CREATE TABLE `Roles` (
  `permission_id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  PRIMARY KEY(`permission_id`)
);

CREATE TABLE `Program_Permissions` (
  `program_permission_id` int(11) NOT NULL AUTO_INCREMENT,
  `permission_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `program_id` int(11) NOT NULL,
  PRIMARY KEY(`program_permission_id`)
);

CREATE TABLE `Config` (
  `key` varchar(100) NOT NULL,
  `value` varchar(100) NOT NULL,
  PRIMARY KEY (`key`)
);

CREATE TABLE `Scale` (
	`scale_id` int(11) NOT NULL AUTO_INCREMENT,
	`name` varchar(100) NOT NULL,
	`desc` varchar(100) NOT NULL,
	`program_id` int(11) NOT NULL,
	PRIMARY KEY(`scale_id`)
);

CREATE TABLE `Perf_Indicator`(
	`perf_indicator_id` int(11) NOT NULL AUTO_INCREMENT,
	`scale_id` int(11) NOT NULL,
	`name` varchar(100) NOT NULL,
	`desc` varchar(100),
	`rating` int(11) NOT NULL,
	PRIMARY KEY (`perf_indicator_id`)
);

ALTER TABLE `Metric`
	ADD CONSTRAINT `progMetric` FOREIGN KEY (`program_id`) REFERENCES `Program` (`program_id`) ON UPDATE CASCADE;

ALTER TABLE `Outcome`
	ADD CONSTRAINT `metOutcome` FOREIGN KEY (`metric_id`) REFERENCES `Metric` (`metric_id`) ON UPDATE CASCADE;

ALTER TABLE `Outcome_Assign`
	ADD CONSTRAINT `outOutAssign` FOREIGN KEY (`outcome_id`) REFERENCES `Outcome` (`outcome_id`) ON UPDATE CASCADE,
	ADD CONSTRAINT `offAssignOutAssign` FOREIGN KEY (`assign_id`) REFERENCES `Offering_Assign`(`assign_id`) ON UPDATE CASCADE;

ALTER TABLE `Course`
	ADD CONSTRAINT `progCourse` FOREIGN KEY (`program_id`) REFERENCES `Program` (`program_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `prefixCourse` FOREIGN KEY (`prefix_id`) REFERENCES `Course_Prefix` (`prefix_id`) ON UPDATE CASCADE;

ALTER TABLE `Course_Outcome`
	ADD CONSTRAINT `CourseOutCourse` FOREIGN KEY (`course_id`) REFERENCES `Course` (`course_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `CourseOutOutcome` FOREIGN KEY (`outcome_id`) REFERENCES `Outcome` (`outcome_id`) ON UPDATE CASCADE;
    
ALTER TABLE `Program_Cutoff`
	ADD CONSTRAINT `progProgCut` FOREIGN KEY (`program_id`) REFERENCES `Program` (`program_id`) ON UPDATE CASCADE,
	ADD CONSTRAINT `semProgCut` FOREIGN KEY (`semester_id`) REFERENCES `Semester` (`semester_id`) ON UPDATE CASCADE;

ALTER TABLE `Offering_Outcome`
	ADD CONSTRAINT `offOffOut` FOREIGN KEY (`offering_id`) REFERENCES `Offering` (`offering_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `outOffOut` FOREIGN KEY (`outcome_id`) REFERENCES `Outcome` (`outcome_id`) ON UPDATE CASCADE;

ALTER TABLE `Student_Outcome`
	ADD CONSTRAINT `offStudOut` FOREIGN KEY (`offering_id`) REFERENCES `Offering` (`offering_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `outStudOut` FOREIGN KEY (`outcome_id`) REFERENCES `Outcome` (`outcome_id`) ON UPDATE CASCADE;

ALTER TABLE `Offering_Student`
	ADD CONSTRAINT `offOffStud` FOREIGN KEY (`offering_id`) REFERENCES `Offering` (`offering_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `studOffStud` FOREIGN KEY (`student_id`) REFERENCES `Student_Outcome` (`student_id`) ON UPDATE CASCADE;

ALTER TABLE `Semester`
	ADD CONSTRAINT `semTypeSemester` FOREIGN KEY (`semester_type_id`) REFERENCES `Semester_Type` (`semester_type_id`) ON UPDATE CASCADE;

ALTER TABLE `Offering`
	ADD CONSTRAINT `courseOff` FOREIGN KEY (`course_id`) REFERENCES `Course` (`course_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `instOff` FOREIGN KEY (`user_id`) REFERENCES `Users` (`user_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `semOff` FOREIGN KEY (`semester_id`) REFERENCES `Semester` (`semester_id`) ON UPDATE CASCADE;
    
ALTER TABLE `Offering_Assign`
	ADD CONSTRAINT `offerOffAssign` FOREIGN KEY (`offering_id`) REFERENCES `Offering` (`offering_id`) ON UPDATE CASCADE;

ALTER TABLE `Student_Assign`
	ADD CONSTRAINT  `offAStudA` FOREIGN KEY (`assign_id`) REFERENCES `Offering_Assign` (`assign_id`) ON UPDATE CASCADE,
	ADD CONSTRAINT 	`offStudStudA` FOREIGN KEY (`student_id`) REFERENCES `Offering_Student` (`student_id`) ON UPDATE CASCADE;
	
ALTER TABLE `Users`
	ADD CONSTRAINT `jobTitleUser` FOREIGN KEY (`job_title_id`) REFERENCES `Job_Title` (`job_title_id`) ON UPDATE CASCADE;

Alter TABLE `Program_Permissions`
	ADD CONSTRAINT `permsPP` FOREIGN KEY (`permission_id`) REFERENCES `Roles` (`permission_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `userPerms` FOREIGN KEY (`user_id`) REFERENCES `Users` (`user_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `progPerms` FOREIGN KEY (`program_id`) REFERENCES `Program` (`program_id`) ON UPDATE CASCADE;
    
ALTER TABLE `Scale`
	ADD CONSTRAINT `progScale` FOREIGN KEY (`program_id`) REFERENCES `Program`(`program_id`) ON UPDATE CASCADE ;
	
ALTER TABLE `Perf_Indicator` 
	ADD CONSTRAINT `piScale` FOREIGN KEY (`scale_id`) REFERENCES `Scale`(`scale_id`) ON UPDATE CASCADE;
