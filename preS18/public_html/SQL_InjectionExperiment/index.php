<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
    <title>Experiment With SQL Injection</title>
    <link rel="stylesheet" type="text/css" href="main.css" />
    <meta http-equiv="Content-Type" 	content="text/html;charset=utf-8" />
</head>

<body>

	<h1>Find Grade</h1>

	<form action="displayGrade.php" method="post">

		<label>
			Enter your student ID:
		</lable>
		<input type="text" name="txtStudID" />

		<br />
		<br />
		<input type="submit" value="Display Grade">

          	<br />
         	</form>
</body>
</html>