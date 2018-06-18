<!-- View for the Matrix Report generation pane -->

<div id="form" class='equal col1 dispForms table'>
	<form id='dataForm' action='ReportsFormProcessor.php' method='post' enctype='multipart/form-data'>
		<?php
			echo '<h1 class="reportTitle">'.$_SESSION['tableHeader'].'</h1>';
			echo $_SESSION['table'];
		?>
		<br/>
		<fieldset>
			<label>Save Report as PDF</label>
			<input type='submit' name='savePDF' value='Save' />
		</fieldset>
	</form>
	<style>
		.table {
			white-space: nowrap;
		}
		
		.table th {
			text-align: right;
		}
		
		.table table {
			border: 1px solid;
			margin: 5px;
		}
		
		.table th, .table td {
			border-right: 1px solid;
			padding: 2px;
		}
		
		.reportTitle {
			font-size: 35pt !important;
		}
		
		.table h1 {
			text-align: left !important;
			padding: 5px 0px !important;
			margin: 5px 0px !important;
		}
	</style>
</div>
