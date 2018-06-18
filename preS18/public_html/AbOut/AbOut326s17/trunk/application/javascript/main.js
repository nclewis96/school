$(document).ready(function() {
	$('.treeElement a').click(function(event) {
		var url = $(this).attr('href');
		
		$.when(
			$.get(url)
		).then(function(response) {
			response = response.replace(/<!--[\s\S]*?-->/g, '');
			$('#dataForm').off();
			$('#form').remove();
			$('.colleft').append(response);
			//attach the state of the tree when the user submits the form
			var temp = $('#dataForm');
			var submit = temp.attr('onsubmit');
			if(submit == undefined)
				submit = '';
			temp.attr('onsubmit', 'appendTree(); '+submit);
			equalize();
			window.scrollTo(0,0);
		});
		
		//stop the link from going to the page it points to
		event.preventDefault();
		return false;
	});
	
	var temp = $('#dataForm');
	var submit = temp.attr('onsubmit');
	temp.attr('onsubmit', 'appendTree(); '+submit);
});

function appendTree()
{
	$('<input type="hidden" name="tree"/>').attr('value', treeToString()).appendTo('#dataForm');
}

/************* Functions for the C.O.R.E. report form ******************/
function updateSectionNo()
{
	var temp = document.getElementsByName('course')[0];
	var course = temp.options[temp.selectedIndex].value;
	temp = document.getElementsByName('semester')[0];
	var semester = temp.options[temp.selectedIndex].value;
	populateSectionNo(course, semester, callbackSectionNo);
}

//callback function
function callbackSectionNo(sectionNos) 
{
	var section = document.getElementsByName('section')[0];
	section.innerHTML = '';
	
	if(sectionNos.length > 0)
	{
		sectionNos.forEach(function (value) {
			section.innerHTML += '<option value="'+value+'">'+value+'</option>';
		});
		
		$('.center input[type="submit"]').removeAttr('disabled');
	}
	else
	{
		$('.center input[type="submit"]').attr('disabled','disabled');
	}
}

function populateSectionNo(course, semester, callback)
{
	var ajax;
	if(window.XMLHttpRequest)
		ajax = new XMLHttpRequest();
	else
		ajax = new ActiveXObject("Microsoft.XMLHTTP");
	
	ajax.open('GET', 'ReportsREST.php?request=section&course='+course+'&semester='+semester);
	ajax.onreadystatechange = function() {
		if(ajax.readyState == 4 && ajax.status == 200)
		{
			var sectionNos = ajax.responseText.split('\n');
			sectionNos.pop();
			callback(sectionNos);
		}
	};
	ajax.send();
}

/**********Checks if ok to delete*********/
var deleteClicked = false;
var remove = null;

function removeSet(event)
{
	remove = event;
}

function deleteStudent(event)
{
	var deleteClicked = true;
	if(remove != null)
	{
		deleteClicked = confirm("All assessment scores for this student will be lost. Are you sure you want to delete?");
	}
	remove = null;
	return deleteClicked;
}

function deleteCourse()
{
	deleteClicked = true;
}

function deleteOffering()
{
	deleteClicked = confirm("Information will be lost. Are you sure you want to delete this Offering?");
	if(!deleteClicked) {
		//change html element name so that the deletion won't happen
		document.getElementById("delete").name="cancelDelete";
		//change html element type so no informational message will appear
		//document.getElementById("delete").type="cancel";
	}
}

function deleteOutcome()
{
	deleteClicked = confirm("Information will be lost. Are you sure you want to delete this Outcome?");
	if(!deleteClicked) {
		//change html element name so that the deletion won't happen
		document.getElementById("delete").name="cancelDelete";
		//change html element type so no informational message will appear
		//document.getElementById("delete").type="cancel";
	}
}

function deleteUser()
{
	deleteClicked = confirm("Assessments associated with offerings taught by the user will"+
										"no longer be accessible. Are you sure you want to delete this User?");
	if(!deleteClicked) {
		//change html element name so that the deletion won't happen
		document.getElementById("delete").name="cancelDelete";
		//change html element type so no informational message will appear
		//document.getElementById("delete").type="cancel";
	}
}

function deleteAssessment()
{
	deleteClicked = confirm("All student scores associated with this assessment will be lost."+
										"Are you sure you want to delete this Assessment?");
	if(!deleteClicked) {
		//change html element name so that the deletion won't happen
		document.getElementById("delete").name="cancelDelete";
		//change html element type so no informational message will appear
		//document.getElementById("delete").type="cancel";
	}
}

function courseSubmit()
{
	$.when(
		$.get('AdminREST.php?request=deleteCourse&course='+$('input[name="courseId"]').val())
	).then(function(numOfferings) {
		if(parseInt(numOfferings) == 0)
		{
			var answer = confirm("Information will be lost. Are you sure you want to delete this Course?");
			if(answer)
			{
				$('#dataForm').append($('<input>').attr('type', 'hidden').attr('name','delete').val('Delete'));
				$('#dataForm').submit();
			}
		}
		else
			alert('This course still has offerings associated with it!');
	});
	
	var result = !deleteClicked;
	deleteClicked = false;
	return result;

}

var addClicked = false;

function addOffering()
{
	if($('input[name="offeringId"]').val() == '-1')
		addClicked = true;
}

function checkOffering()
{
	if (addClicked)
	{
		var url = 'AdminREST.php?request=checkOffering&section='+$('input[name="section"]').val()+'&semester='+$('select[name="single"]').val()+'&course='+$('input[name="course"]').val();
		$.when(
			$.get(url)
		).then(function(numOfferings) {
			if(parseInt(numOfferings) == 0)
			{
				$('#dataForm').append($('<input>').attr('type', 'hidden').attr('name','save').val('Save'));
				$('#dataForm').submit();
			}
			else
				informAction("Could not create offering - this offering already exists");
			
		});
		addClicked = false;
		return false;
	}
	return true;
}

//clears out the start and end semester
function updateSingleSemester()
{
	var start = $('select[name="start"]');
	var end = $('select[name="end"]');
	end.html(start.html());
	
	start.val($('select[name="start"] option:first').val());
	end.val($('select[name="end"] option:first').val());
	
	$('select[name="single"] option[value="null"]').remove();
}

//clears out the single semester and makes the end semester only have valid options
function updateEndSemester()
{
	$('select[name="single"]').html($('select[name="start"]').html());

	var start = $('select[name="start"]');
	var end = $('select[name="end"]');
	end.html(start.html());
	
	if(start.val() !== "null")
	{
		$('select[name="end"] option[value="null"]').remove();
		$('select[name="end"] option:gt('+(start[0].selectedIndex - 1)+')').remove();
	}
}

//shows or hides the outcomes related to a given program
function updateCheck(degree)
{
	if($('input[name="'+degree+'"]')[0].checked)
	{
		$('#'+degree+'Outcomes').show();
	}
	else
	{
		$('#'+degree+'Outcomes').hide();
	}
}


function validateName(input)
{
	if(input.value.length > 0)
	{
		$('input[name="add"]').removeAttr('disabled');
	}
	else
	{
		$('input[name="add"]').attr('disabled', 'disabled');
	}
}

//faculty assessment validator
function validateAssessment()
{
	//check the description has something in it
	var validDesc = $('#asDesc').val().length > 0;
	outline('#asDesc', validDesc);
	
	//check that max points is an integer greater than 0
	var maxpoints = parseInt($('#maxText').val());
	validMP = /^([1-9]\d*)$/.test(maxpoints);
	outline('#maxText', validMP);
	
	//check at least one outcome is used
	var validOut = false;
	$('input[name^="CAC"],input[name^="EAC"]').each(function(index, value) {
		validOut = validOut || value.checked;
	});
	outline('#outcomes', validOut);
	
	//check that all students have a score greater than or equal to 0
	var validPoint = true;
	var validPoints = true;
	$('input[name^="student"]').each(function(index, value) {
		val = parseInt(value.value);
		validPoint = (/^(0|([1-9]\d*))(\.\d+)?$/.test(val) && (val <= maxpoints || !validMP));
		outline(value, validPoint); // does not work
		validPoints = validPoint && validPoints;
	});
	
	if(validDesc && validMP && validOut && validPoints)
	{
		$('#save').removeAttr('disabled');
	}
	else
	{
		$('#save').attr('disabled', 'disabled');
	}
}

//admin course validator
function validateCourse()
{
	var cNumber = $('input[name="cNumber"]');
	var validNum = cNumber.length > 0 ? /^\d{3,4}$/.test(cNumber.val()) : true;
	outline('input[name="cNumber"]', validNum);
	
	var validName = $('input[name="courseName"]').val().length > 0;
	outline('input[name="courseName"]', validName);
	
	var validProg = $('input[name="cs"]').is(':checked') || $('input[name="se"]').is(':checked');
	outline('#program', validProg);
	
	//check at least one outcome is used
	var validOut = false;
	if($('input[name="cs"]').is(':checked'))
	{
		$('input[name^="CAC"]').each(function(index, value) {
			validOut = validOut || value.checked;
		});
	}
	
	if($('input[name="se"]').is(':checked'))
	{
		$('input[name^="EAC"]').each(function(index, value) {
			validOut = validOut || value.checked;
		});
	}
	if (validProg)
		outline('#outcomes', validOut);
	else
		$('#outcomes').css('border-color', 'white');
	
	if(validNum && validName && validOut)
	{
		$('input[name="save"]').removeAttr('disabled');
	}
	else
	{
		$('input[name="save"]').attr('disabled', 'disabled');
	}
}

//admin offering validator
function validateOffering()
{
	var validSec = /^[01][1-9]$/.test($('input[name="section"]').val());
	outline('input[name="section"]', validSec);
	
	if(validSec)
	{
		$('input[name="save"],input[name="import"]').removeAttr('disabled');
		
		if($('input[name="student"]').val().length > 0)
		{
			$('input[name="add"]').removeAttr('disabled');
		}
		else
		{
			$('input[name="add"]').attr('disabled', 'disabled');
		}
	}
	else
	{
		$('input[name="save"],input[name="import"]').attr('disabled', 'disabled');
	}
}

//admin outcome validator
function validateOutcome()
{
	var oName = $('input[name="outcomeName"]');
	//in edit outcome there is no outcomeName input tag so it already valid
	var validName = oName.length > 0 ? oName.val().length > 0 : true;
	outline('input[name="outcomeName"]', validName);
	
	var validText = $('textarea[name="outcomeDescription"]').val().length > 0;
	outline('textarea[name="outcomeDescription"]', validText);
	
	if(validName && validText)
	{
		$('input[name="save"]').removeAttr('disabled');
	}
	else
	{
		$('input[name="save"]').attr('disabled', 'disabled');
	}
}

//admin user validator
function validateUser()
{
	var validName = $('input[name="name"]').val().length > 0;
	outline('input[name="name"]', validName);
	
	var validUN = $('input[name="username"]').val().length > 0;
	outline('input[name="username"]', validUN);
	
	if(validName && validUN)
	{
		$('input[name="save"]').removeAttr('disabled');
	}
	else
	{
		$('input[name="save"]').attr('disabled', 'disabled');
	}
}

//tree navigation highlighting
$(window).load(function() {
	$('.d1 .treeElement, .d2 .treeElement').hover(function() {
		$(this).css('background-color', '#5D87A1');
	},function() {
		$(this).css('background-color', '');
	});
});

//timeout: amount of time that the informative message
//stays on the screen before it disappears
const timeout = 2000;
const fadeOutTime = 5000;
var timeoutID;
function informAction(message) {
	$('.infoAction').text(message);
	$('.infoAction').css('background-color','#FFFFFF');
	window.clearTimeout(timeoutID);
	timeoutID = window.setTimeout(resetInfoActionDiv, timeout);
}

function resetInfoActionDiv() {
	$("#infoActionId").fadeOut(fadeOutTime);
}

function outline(element, valid)
{
	var color = '';
	if (!valid)
		color = 'red';
	$(element).css('border-color', color);
}

//generates a string representation of the tree
function treeToString()
{
	var str = '';
	$('.treeElement').each(function(index, value) {
		if(value.parentNode.className.indexOf('expand') > -1)
			str += '0';
		else
			str += '1';
		str+= '.'+value.textContent+'|';
	});
	str = str.substring(0, str.length-1);
	return str;
}

function expandTree(tree)
{
	var elements = tree.split('|');
	elements = $(elements).map(function(index, value) {
		//first element is if the tree is in expand or collapse, second element is the text node 
		return new Array(value.split('.'));
	});
	
	var curTree = $('.treeElement').map(function(index, value) {
		return new Array(new Array(value, value.textContent));
	});
	
	var j = 0;
	for(var i = 0; i < curTree.length; i++)
	{
		//check if the text of both nodes is the same
		if(elements[j][1] == curTree[i][1])
		{
			//if the node was open and the node on the tree can be expanded
			if(elements[j][0] == '1' && curTree[i][0].firstChild.nodeName == 'SPAN')
			{
				var parent = $(curTree[i][0]).parent();
				var sibling = parent;
				while(sibling.attr('class').indexOf('d0') == -1)
					sibling = sibling.prev();
				
				//if the curnode is a d0 or the d0 above the curnode is open
				if(parent == sibling || sibling.attr('class').indexOf('expand') == -1)
					$(curTree[i][0].firstChild).trigger('click');
			}
			
			j++;
		}
	}
}

