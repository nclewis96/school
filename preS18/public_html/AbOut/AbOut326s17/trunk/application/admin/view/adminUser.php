<!-- View for Add/Edit Course panes -->

<div id="form" class='equal col1 dispForms'>
	<form id='dataForm' action="AdminFormProcessor.php" method="post" enctype="multipart/form-data">
		<h3><?php echo $head;?></h3>
		<br/>
		<fieldset>
			<table>
				<tr>
					<td>Name: </td>
					<td style='padding: 0px 20px' ><input type='text' name='name' value='<?php if($user > -1) echo $uName; ?>' onkeyup='validateUser()' onpaste='setTimeout(validateUser, 0)'/></td>
				</tr>
				<tr>
					<td>Mtech Username: </td>
					<td style='padding: 0px 20px'><input type='text' name='username' value='<?php if($user > -1) echo $username; ?>' onkeyup='validateUser()' onpaste='setTimeout(validateUser, 0)'/></td>
				</tr>
				<tr>
					<td>Active: </td>
					<td style='padding: 0px 20px'><input type='checkbox' name='active' <?php if($user > -1 && $active) echo 'checked="checked"'; ?>/></td>
				</tr>
			</table>
			<br/>
			<input type='hidden' name='userId' value='<?php echo $user; ?>'/>
			<input type='submit' name='save' value='Save'/>
			<?php
				if($user > -1)
					echo "<input type='submit' id='delete' name='delete' value='Delete' onclick='deleteUser();'/>";
			?>
			<script>
				validateUser();
			</script>
		</fieldset>
	</form>
</div>
