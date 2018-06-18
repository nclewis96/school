<!-- View for the Reports navigation tree pane -->

<div id="tree" class="equal col2 treeClass">
	<table id="tableNav">
		<?php
			echo "<tr class='d0 collapse level0'><td class='treeElement'><span class='toggle expand'></span>Reports</td></tr>\xA";
			
			echo "<tr class='d1 expand level1'><td class='treeElement'><a href='ReportsREST.php?view=overviewOutcome'>Overview Outcome Report</a></td></tr>\xA";
			echo "<tr class='d1 expand level1'><td class='treeElement'><a href='ReportsREST.php?view=course'>Overview Course Report</a></td></tr>\xA";
			echo "<tr class='d1 expand level1'><td class='treeElement'><a href='ReportsREST.php?view=core'>C.O.R.E. Report</a></td></tr>\xA";
			echo "<tr class='d1 expand level1'><td class='treeElement'><a href='ReportsREST.php?view=outcome'>Outcome Report</a></td></tr>\xA";
			echo "<tr class='d1 expand level1'><td class='treeElement'><a href='ReportsREST.php?view=matrix'>Matrix Report</a></td></tr>\xA";
		?>
	</table>
</div>