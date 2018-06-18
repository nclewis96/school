/**
 * constructs the navigation tree structure for use by the admin, faculty, and report navigation trees
 */

$(document).ready(function() {
	$('#tableNav').on('click', '.toggle', function () {
		//Gets all <tr>'s  of greater depth
		//below element in the table
		var findChildren = function (tr) {
			var depth = tr.attr('class').split(' ')[0];
			return tr.nextUntil($('tr').filter(function () {
				var temp = $(this).closest('table').attr('id');
				if(temp == 'tableNav')
					return $(this).attr('class').split(' ')[0] <= depth;
				return true;
			}));
		};

		var el = $(this);
		var tr = el.closest('tr'); //Get <tr> parent of toggle button
		var children = findChildren(tr);

		//Remove already collapsed nodes from children so that we don't
		//make them visible. 
		//(Confused? Remove this code and close Item 2, close Item 1 
		//then open Item 1 again, then you will understand)
		var subnodes = children.filter('.expand');
		subnodes.each(function () {
			var subnode = $(this);
			var subnodeChildren = findChildren(subnode);
			children = children.not(subnodeChildren);
		});

		//Change icon and hide/show children
		if (tr.hasClass('collapse')) {
			tr.removeClass('collapse').addClass('expand');
			children.hide();
		} else {
			tr.removeClass('expand').addClass('collapse');
			children.show();
		}
		return children;
	});
});