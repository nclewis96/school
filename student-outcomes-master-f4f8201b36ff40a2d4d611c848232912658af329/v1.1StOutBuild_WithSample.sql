USE Stout;

/* Program_*/
INSERT INTO Program (name) 
VALUE ('Accounting'),
('Allied Health Med Supp'),
('American History'),
('Antrhopology'),
('Applied Health Science'),
('Arabic'),
('Automotive Technology');

/* Prefix */
INSERT INTO Course_Prefix (prefix)
VALUE ('ACTG'),
('AHMS'),
('HSTA'),
('ANTY'),
('AHS'),
('ARAB'),
('AT');

/*Course PK:course_id 
FK: FOREIGN KEY (`program_id`) REFERENCES `Program` (`program_id`) ON UPDATE CASCADE, 
FOREIGN KEY (`prefix_id`) REFERENCES `Course_Prefix` (`prefix_id`) ON UPDATE CASCADE;
*/
INSERT INTO Course (prefix_id,program_id,course_num,title)
VALUES ('1','1','111','Principles of Mangerial Accounting'),
('2','2','222','Advance Medical Coding'),
('3','3','333', 'American History I'),
('4','4','444','Anthropology & the human experience'),
('5','5','555','Advanced Physiology Of Exercise'),
('6','6','666','Elementary Modern Arabic I'),
('7','7','777','Brakes');

/*Metric PK: metric_id
FK: FOREIGN KEY (`program_id`) REFERENCES `Program` (`program_id`) ON UPDATE CASCADE;
*/
INSERT INTO Metric (program_id,name) 
VALUE ('1','first metric'),
('2','first metric'),
('3','first metric'),
('4','first metric'),
('5','first metric'),
('6','first metric'),
('7','first metric');

/*Outcome PK: outcome_id
FK:FOREIGN KEY (`metric_id`) REFERENCES `Metric` (`metric_id`) ON UPDATE CASCADE; */
INSERT INTO Outcome (metric_id, name, description) 
VALUES ('1' , 'Counting Money' , 'Can count the monies with such efficiency such accuracy'),
('2' , 'Cure coding' , 'Can code cures that kill viruses'),
('3' , 'Cure coding' , 'Can code cures that kill viruses'),
('4' , 'Cure coding' , 'Can code cures that kill viruses'),
('5' , 'Cure coding' , 'Can code cures that kill viruses'),
('6' , 'Cure coding' , 'Can code cures that kill viruses'),
('7' , 'Cure coding' , 'Can code cures that kill viruses');

/* Course_outcome:PK course_id , outcome_id
FK:FOREIGN KEY (`course_id`) REFERENCES `Course` (`course_id`) ON UPDATE CASCADE,
   FOREIGN KEY (`outcome_id`) REFERENCES `Outcome` (`outcome_id`) ON UPDATE CASCADE;  */   
INSERT INTO Course_Outcome (course_id, outcome_id)
VALUES ('1','1'),
('2','2'),
('3','3'),
('4','4'),
('5','5'),
('6','6'),
('7','7');

/*Job Title PK: Job_Title_id */
INSERT INTO Job_Title(job_title_id, title)
Value ('1','Faculty'),
('2','Program Director'),
('3','Observer');


/*Users PK:user_id
FK: FOREIGN KEY (`job_title_id`) REFERENCES `Job_Title` (`job_title_id`) ON UPDATE CASCADE;
*/
INSERT INTO Users (job_title_id, name, username) 
VALUES ('3','Abdulrahman Alduraiweesh', 'aealduraiweeh' ),
('2','Trevor Brooks', 'tbrooks'),
('2','Nathan Lewis', 'nlewis'),
('2','Jesse Anderson', 'janderson2'),
('1','Jeff Braun', 'jbraun') ;

/*Semester Type PK: symester_type_id*/
INSERT INTO Semester_Type (text, startMonth)
VALUES ('Spring', 'January'),
('Fall', 'September'),
('Summer', 'May');

/* Semster PK: semster_id 
FK:FOREIGN KEY (`semester_type_id`) REFERENCES `Semester_Type` (`semester_type_id`) ON UPDATE CASCADE;*/
INSERT INTO Semester (semester_type_id, year)
VALUES ('1','2017'),
('2','2017'),
('3','2017');


/*Offering PK:offering_id
FK: FOREIGN KEY (`course_id`) REFERENCES `Course` (`course_id`) ON UPDATE CASCADE,
FOREIGN KEY (`user_id`) REFERENCES `Users` (`user_id`) ON UPDATE CASCADE,RT INTO Offering (offering_id, course_id, user_id, semester_id, section_num)
FOREIGN KEY (`semester_id`) REFERENCES `Semester` (`semester_id`) ON UPDATE CASCADE;ES ('88' ,'1','799','111','02'); */
INSERT INTO Offering (course_id, user_id, semester_id, section_num, num_students, locked)
VALUES ('1','1','1','01', 5, 0),
('2','2','2','01', 5, 0),
('3','3','3','01', 5, 0),
('4','4','1','01', 5, 0),
('5','5','2','01', 5, 0),
('6','5','3','01', 5, 0),
('7','5','1','01', 5, 0);

/*Premisions Set PK:premission_id */
INSERT INTO Roles(name) 
VALUES ('Administrator'),
('Program Coordinator'),
('Faculty'),
('Observer'),
('Inactive Faculty');

/* Program Permissions PK program_permission_id ,

FK: FOREIGN KEY (`permission_id`) REFERENCES `Roles` (`permission_id`) ON UPDATE CASCADE,
	FOREIGN KEY (`user_id`) REFERENCES `Users` (`user_id`) ON UPDATE CASCADE,
    FOREIGN KEY (`program_id`) REFERENCES `Program` (`program_id`) ON UPDATE CASCADE;*/
INSERT INTO Program_Permissions (permission_id, user_id, program_id) 
VALUE ('1' ,'1', '1'),
('2' ,'2', '2'),
('3' ,'3', '3'),
('4' ,'4', '4'),
('5' ,'5', '5');

/*
Offering Outcome
FK:
ADD CONSTRAINT `offOffOut` FOREIGN KEY (`offering_id`) REFERENCES `Offering` (`offering_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `outOffOut` FOREIGN KEY (`outcome_id`) REFERENCES `Outcome` (`outcome_id`) ON UPDATE CASCADE;
*/
INSERT INTO Offering_Outcome (offering_id, outcome_id, score) 
VALUES ('1', '1','87'),
('2', '2','20'),
('3', '3','70'),
('4', '4','60'),
('5', '5','50'),
('6', '6','66'),
('7', '7','45');


/*
ADD CONSTRAINT `offStudOut` FOREIGN KEY (`offering_id`) REFERENCES `Offering` (`offering_id`) ON UPDATE CASCADE,
    ADD CONSTRAINT `outStudOut` FOREIGN KEY (`outcome_id`) REFERENCES `Outcome` (`outcome_id`) ON UPDATE CASCADE;
    */
INSERT INTO Student_Outcome (offering_id, outcome_id, student_id, score) 
VALUES ('1', '1', '1', '90'),
('2', '2', '2', '90'),
('3', '3', '3', '90'),
('4', '4', '4', '90'),
('5', '5', '5', '90'),
('6', '6', '5', '90'),
('7', '7', '5', '90');

/*
FK:
ADD CONSTRAINT `progProgCut` FOREIGN KEY (`program_id`) REFERENCES `Program` (`program_id`) ON UPDATE CASCADE,
	ADD CONSTRAINT `semProgCut` FOREIGN KEY (`semester_id`) REFERENCES `Semester` (`semester_id`) ON UPDATE CASCADE;
    */
INSERT INTO Program_Cutoff ( program_id,semester_id,start_date, end_date)
VALUES ('1','1','20111011', 20121122),
('2','2','20111011', 20121122),
('3','3','20111011', 20121122),
('4','1','20111011', 20121122),
('5','2','20111011', 20121122),
('6','3','20111011', 20121122),
('7','1','20111011', 20121122);
