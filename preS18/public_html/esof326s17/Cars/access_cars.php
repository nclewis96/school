<!-- 
 Project: Class09Exercise
 
 File: .../cardata.html
 
 Execution Environments Firefox 50.1.0
 
 History
 ==========
 Date		Author				Description
 ----------------------------------
 02/1317	Nathaniel lewis		Initial PHP/C version
 
 Description
 Displays a webpage that asks for a query, 
	then displays the results from carsLNC

------- Requirements -------
R01 Display the purpose of the first form
R02 Prompt for user Query
R03 Text area that takes in the query
R04 Able to Clear the box
R05 Able to Submit the query to the next page
R06 Connects to the online database carsLNC
R07 Accepts query submitted
R08 Cleans up the Query
R08 Runs the Query
R09 Displays the results of the query
------- Algorithm ---------
A01 <title> with the purpose of the form
A02 Text Label that asks for the Query
A03 Text area that will accept the query
A04 Button that resets the page/box
A05 Button that submits the query to access_cars.php 
A06 Connection established between page and database
A07 Retrieves and stores query
A08 Trim Query to be useable
A09 Submits query to the database
A10 Builds a table that will display the results of the Query
-->
	<html>
		<head>
<!--L01-->	<title> Access the cars database with MySQL </title>
		</head>
		<body>
	<?php
	$stage = $_POST["stage"];
	if(!IsSet($stage)) {
	?>
	<p>
<!--L02-->		Please enter your query:
				<br />
<!--L03-->			<form method = "POST" action = "access_cars.php">
					<textarea rows = "2" cols =  "80" name = "query" >
					</textarea>
					<br /><br />
<!--L04-->			<input type = "hidden" name = "stage" value = "1" />
<!--L05-->			<input type = "submit" value = "Submit request" />
				</form>
			</p>
		<?php
	} else { //stage is set, process query 
		// Connect to MySQL
/*L06*/	$db = mysql_connect("katie.mtech.edu", "nlewis", "qwe123");
		if(!$db)
			exit("Error - Could not connect to MySQL on Katie");
		$er = mysql_select_db("carsLNC");
		// Get the query and clean it up (delete leading and trailing
		// white space, and remove backslashes from magic_quotes_gpc)
/*L07*/		$query = $_POST['query'];
/*L08*/		trim($query);
		$query = stripslashes($query);
		//Display the query, after fiing html characters
		$query_html = htmlspecialchars($query);
		print "<p> <b> The query is: </b> " . $query_html . "</p>";
		//Exec query
/*L09*/		$result = mysql_query($query);
		if (!$result) {
			print "Error - the query could not be excuted";
			$error = mysql_error();
			print "<p>" . $error . "</p>";0
			exit;
		}
		//Display the results in a table
/*L10*/	print "<table><caption> <h2> Query Results </h2> </caption>";
		print "<tr aling = 'center'>";
		//Get num rows, first row, num fields
		$num_rows = mysql_num_rows($result);
		$row = mysql_fetch_array($result);
		$num_fields = mysql_num_fields($result);
		//Produce the column labels
		$keys = array_keys($row);
		for ($index = 0; $index < $num_fields; $index++)
			print "<th>" . $keys[2 * $index + 1] . "</th>";
		print "</tr>";
		//output vals
		for ($row_num = 0; $row_num < $num_rows; $row_num++) {
			print "<tr align = 'center'>";
			$values = array_values($row);
			for ($index = 0; $index < $num_fields; $index++) {
				$value = htmlspecialchars($values[2 * $index + 1]);
				print "<th>" . $value . "</th> ";
			}
			print "</tr>";
			$row = mysql_fetch_array($result);
		}
		print "</table>";
	} //else 
	?>
		</body>
	</html>