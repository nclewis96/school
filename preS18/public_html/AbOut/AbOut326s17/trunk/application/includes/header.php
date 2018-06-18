<!-- Header content -->

<div class="header">
<?php
	if(isset($_SESSION['username']))
		include(INCLUDE_PATH.'widgets/logoutWidget.php');
?>
	<div class="introHeader">
		<h1 class="title">Ab<span class="title2">Out</span></h1>
		<div class="infoAction" id="infoActionId"> 		
		</div>
	</div>
</div>