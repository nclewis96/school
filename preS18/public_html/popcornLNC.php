
	 
<!-- -  - - - - - - - - - - - - - - - - - - - - - -
# PROJECT: Examples
# 
# FILE: .../popcornLNC.php
#
# EXECUTION ENVIRONMENTS
# Firefox 50.1.0
#
# HARD COPY
# From Programmer's Notepad v2.4 as Text
#
# HISTORY
# Date				Author			Description
# ====				======			===========
# 01/25/16			Nathaniel Lewis	Initial version
#
# DESCRIPTION
# Reads information from the popcorn order form, calculates the order
# displays the order in a readable form for the customer.
#
# REQUIREMENTS
# R01 Operates on Firefox 50.1.00
# R02 Shall be written in PHP and HTML
# R03 Shall read in information from the popcorn.html form
# R04 Will use the information to calculate the cost of the order
# R05 Will display this information back to the customer
#
# ALGORITHM
# A01 Set title;
#	  Set charset;
#	  Set text/css styles;
# .....
# A0x Display Customer heading;
# A0y <continue>
#
- - - - - - - - - - - - - - - - - - - - - - - - - - -->
	 
<html lang = "en">

<head>
<!-- L01 -->
	<title> Process the popcorn3.html form </title>
	<meta charset = "utf-8" />
	<style type = "text/css">
      td, th, table {border: thin solid black;}
    </style>
</head>

<body>
 
	<?php
	
		//get form info
		$unpopped = $_POST["unpopped"];
		$caramel = $_POST["caramel"];
		$caramelNut = $_POST["caramelNut"];
		$toffeyNut = $_POST["toffeyNut"];
		$buyerName = $_POST["buyerName"];
		$streetAddress = $_POST["streetAddress"];
		$cityStZip = $_POST["cityStZip"];
		$payment = $_POST["payment"];
		
		//Set blank quantities to 0
		if ($unpopped == " ") $unpopped = 0;
		if ($caramel == " ") $caramel = 0;
		if ($caramelNut == " ") $caramelNut = 0;
		if ($toffeyNut == " ") $toffeyNut = 0;
		
		//compute the order
		$unpopped_cost = 3.0 * $unpopped;
		$caramel_cost = 3.5 * $caramel;
		$caramelNut_cost = 4.5 * $caramelNut;
		$toffeyNut_cost = 5.0 * $toffeyNut;
		$total_price = $unpopped_cost + $caramel_cost + $caramelNut_cost + $toffeyNut_cost;
		$total_items = $unpopped + $caramel + $caramelNut + $toffeyNut;
		
		?>
<!-- L02 -->	
    <h4> Customer: </h4>
	<?php
		print ("$buyerName <br /> $streetAddress <br /> $cityStZip <br />");
	?>
	<p /> <p />
	<table border = "border">
		<caption> Order Information </caption>
		<tr>
			<th> Product </th>
			<th> Unit Price </th>
			<th> Quantity Ordered </th>
			<th> Item Cost </th>
		</tr>
		<tr align = "center">
			<td> Unpopped Popcorn </td>
			<td> $3.00 </td>
			<td> <?php print ("$unpopped"); ?> </td>
			<td> <?php printf ("$ %4.2f", $unpopped_cost); ?>
			</td>
		</tr>
		<tr align = "center">
			<td> Caramel Popcorn </td>
			<td> $3.50 </td>
			<td> <?php print ("$caramel"); ?> </td>
			<td> <?php printf ("$ %4.2f", $caramel_cost); ?>
			</td>
		</tr>
		<tr align = "center">
			<td> Caramel Nut Popcorn </td>
			<td> $4.50 </td>
			<td> <?php print ("$caramelNut"); ?> </td>
			<td> <?php printf ("$ %4.2f", $caramelNut_cost); ?>
			</td>
		</tr>
		<tr align = "center">
			<td> Toffey Nut Popcorn </td>
			<td> $5.00 </td>
			<td> <?php print ("$toffeyNut"); ?> </td>
			<td> <?php printf ("$ %4.2f", $toffeyNut_cost); ?>
			</td>
		</tr>
		</table>
	<p /> <p />
	
	<?php
		print "You ordered $total_items popcorn items <br />";
		printf ("Your total bill is: $ %5.2f <br />", $total_price);
		print "Your chosen method of payment is: $payment <br />";
	?>
	

</body>

</html>