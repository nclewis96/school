<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
    <title>Experiment With SQL Injection</title>
    <link rel="stylesheet" type="text/css" href="main.css" />
    <meta http-equiv="Content-Type" 	content="text/html;charset=utf-8" />
</head>

<body>

	<h1>Display Grade</h1>

<?php
	$dbname='StudentInformation';	
	$username = 'csci340User';
	$password = 'csci340Pass';

	
	$myDB = new PDO("mysql:host=localhost; $dbname, $username, $password);
	@mysql_select_db($myDB) or die("Unable to select database");

	// Get student ID from input form. 
	$studentID = $_POST['txtStudID'];
    
	// Retrieve grade for the student
    	$query = "SELECT CONCAT(fName,' ', lName) AS 'name', score, grade
		   FROM Student
                 WHERE studentId=".$studentID.";";

	$myQuery = $myDB->prepare($query)
	$myQuery ->execute();
	$row_count = myQuery->rowCount;

	// Handle an empty table. 
	if($row_count==0) {
		echo ("<h3>Student ID not found in the database.</h3>");
	} else {
?>

<table>
	<tr>
           	<th>Name</th>
           	<th>Score</th>
           	<th>Grade</th>
       </tr>

<?php
		$i=0;
		while($i < $row_count) {
			$name = mysql_result($result, $i, "name");
			$score = mysql_result($result, $i, "score");
			$grade = mysql_result($result, $i, "grade");
?>
  	<tr>
           	<td><?php echo ($name); ?></td>
           	<td><?php echo ($score); ?></td>
           	<td><?php echo ($grade); ?></td>
     	</tr>
<?php
			$i++;
		} // while
?>

</table>

<?php
	} // else

	echo ("<br /><br />Here is the query: ".$query."<br /><br />");

?>


<br /><br /><br />
<a href="index.php">Back</a>

</body>
</html>

