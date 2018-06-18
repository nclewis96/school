<!-- When included displays the navigation tabs -->

<?php $file = basename($_SERVER['SCRIPT_FILENAME'], 'Controller.php'); ?>
<div class="tabs">
	<ul>
		<li>
			<a <?php if($file === 'Admin') echo 'id="navSelect"';?> class="nav" href="<?php echo HTTP_ADMIN_PATH; ?>AdminController.php">
				Administrator
			</a>
		</li>
		<li>
			<a <?php if($file === 'Faculty') echo 'id="navSelect"';?> class="nav" href="<?php echo HTTP_FACULTY_PATH; ?>FacultyController.php">
				Faculty
			</a>
		</li>
		<li>
			<a <?php if($file === 'Reports') echo 'id="navSelect"';?> class="nav" href="<?php echo HTTP_REPORTS_PATH; ?>ReportsController.php">
				Reports
			</a>
		</li>
	</ul>
</div>
<script>
$(document).ready(function() {
	$('.nav').click(function(event) {
		$.when(
			$.post(document.URL.replace('Controller', 'FormProcessor'), {tree: treeToString()}),
			$(this)
		).then(function(response, link) {
			window.location.href = link.attr('href');
		});
		
		//stop the link from going to the page it points to
		event.preventDefault();
		return false;
	});
});
</script>