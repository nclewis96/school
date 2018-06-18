<?php
/** 
* Reports form processor - processes data that user inputs into forms and
*  modifies model based on the input
*/

	require_once('../includes/Bootstrap.php');
	require_once(INCLUDE_PATH.'startup.php');
	require_once(INCLUDE_PATH.'tcpdf/tcpdf.php');
	require_once(INCLUDE_PATH.'tcpdf/config/lang/eng.php');
	
	/** 
	* Initialize a TCPDF object with title $title
	* @param title - title for the PDF
	* @return Initialized TCPDF object
	*/
	function initializePdf($title)
	{
		//create new pdf
		$pdf = new TCPDF('L', PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);
		
		//set document information
		$pdf->SetCreator(PDF_CREATOR);
		$pdf->SetAuthor('Computer Science Department');
		$pdf->SetTitle($title);
		
		//set footer font
		$pdf->setFooterFont(array(PDF_FONT_NAME_DATA, '', PDF_FONT_SIZE_DATA));
		
		//set default monospaced font
		$pdf->SetDefaultMonospacedFont(PDF_FONT_MONOSPACED);
		
		//set margins
		$pdf->SetMargins(1, 10, 1);
		$pdf->SetFooterMargin(PDF_MARGIN_FOOTER);
		
		//set auto page breaks
		$pdf->SetAutoPageBreak(true, PDF_MARGIN_BOTTOM);
		
		//set some language-dependent strings
		//$pdf->SetLanguageArray($l);
		
		$pdf->SetFont('helvetica', 'B', 20);
		$pdf->AddPage();
		$pdf->Write(0, $title, '', 0, 'L', true, 0, false, false, 0);
		
		$pdf->SetFont('helvetica', '', 6.5);
		
		return $pdf;
	}
	
	//if the facult tab called for a report
	if(isset($_SESSION['post']))
	{
		$_POST = $_SESSION['post'];
		unset($_SESSION['post']);
	}
	
	if(isset($_POST['savePDF']))
	{
		$table = $_SESSION['table'];
		$tableName = $_SESSION['tableName'];
		$tableHeader = $_SESSION['tableHeader'];
		
		//unset($_SESSION['table']);
		//unset($_SESSION['tableName']);
		//unset($_SESSION['tableHeader']);
		
		$pdf = initializePdf($tableHeader);
		$pdf->writeHTML($table, true, false, true, false, '');
		$pdf->Output($tableName, 'D');
	}
	else if(!isset($_POST['view']))
	{
		header('Location: ReportsController.php');
	}
	else
	{
		$view = $_POST['view'];
		
		include('model/ReportsModel.php');
		$model = new ReportsModel($DB_Read, $DB_Write);
		
		if($view == 'overviewOutcome')
		{
			//print_r($_POST);
			$program = $_POST['program'];
			$single = $_POST['single'];
			$start = $_POST['start'];
			$end = $_POST['end'];
			$raw = $_POST['raw'] == 'yes';
			
			if($single !== 'null')//use single semester
			{
				$start = $single;
				$end = $single;
			}
			
			if(isset($_POST['csv']))
			{
				//csv
				
				$csv = 'Outcome,';
				
				$semesters = $model->getSemestersInRange($start, $end);
				$outcomes = $model->getProgramOutcomes($program);
				
				//generate the top row and initialize column arrays
				foreach($semesters as $semester)
				{
					$csv .= $semester['semester'].',';
					if($raw)
						$csv .= 'Students Passed, Total Students,';
				}
				for ($i = 0; $i < count($semesters); $i++)
				{
					$colScore[$i] = 0;
					$colStudPass[$i] = 0;
					$colStud[$i] = 0;
					$colWithStud[$i] = 0;
					for ($j = 0; $j < count($outcomes); $j++)
					{
						$colAvg[$i][$j] = 0;
					}
				}

				$outIndex = 0;
				$csv .= "Row Average,";
				if($raw)
					$csv .= 'Students Passed, Total Students,';
				$csv .= "\xA";
				//end top row
				
				foreach($outcomes as $outcome)
				{
					$oAbbrev = $outcome['oAbbrev'];
					$csv .= "$oAbbrev,";
					
					$courses = $model->getCoursesForOutcome($oAbbrev);
					foreach($courses as $course)
					{
						//row totals
						$sum = 0;
						$sumStud = 0;
						$sumStudPass = 0;
						$sumWithStud = 0;
						$count = 0;
						$cAbbrev = $course['cAbbrev'];

						foreach($semesters as $semester)
						{
							$semesterId = $semester['semesterId'];
							//$result = $model->calculatePercent($outcome, $cAbbrev, $semesterId);
							$result = $model->calculatePercent($oAbbrev, $cAbbrev, $semesterId);
							$noStudPass = $result['noStudPass'];
							if($noStudPass == '')
								$noStudPass = 0;
						
							$noStud = $result['noStud'];
							$score = $result['score'];
							
							$sum += $score;
							$sumStud += $noStud;
							$sumStudPass += $noStudPass;
						
							$colScore[$count] += $score;
							$colStudPass[$count] += $noStudPass;
							$colStud[$count] += $noStud;
							if($noStud > 0)
							{
								$colWithStud[$count]++;
								$sumWithStud++;
							}
						
							$count++;
						}
					}
				
				
					//variables used for calculating course averages
					$score = 0;
					$pass = 0;
					$stud = 0;
					$cols = 1;
				
					//calculate average of courses in a semester for an outcome
					for($i = 0; $i < count($semesters); $i++)
					{
						if($colWithStud[$i] > 0)
						{
							$score += ($colScore[$i] / $colWithStud[$i]);
							
							$colAvg[$i][$outIndex] += ($colScore[$i] / $colWithStud[$i]);
						}
						$cols++;
						$pass += $colStudPass[$i];
						$stud += $colStud[$i];
					
						//add semester average for outcome to report
						$csv .= sprintf('%.0f%%,', $colWithStud[$i] > 0 ?	$colScore[$i]/$colWithStud[$i] : 0);
					}
				
					//add average of course averages across semesters to report
					$csv .= sprintf('%.0f%%,', $cols > 0 ? $score/($cols-1) : 0);  // Fix after 2014 IAB meeting
					if($raw)
						$csv .= "$pass,$stud,";
					$csv .= "\xA";

					$outIndex++;				
				}
				
				$csv .= "Column Average,";
				for ($i = 0; $i < count($semesters); $i++)
				{
					$outAvg = 0;
					for ($j = 0; $j < count($outcomes); $j++)
					{
						$outAvg += $colAvg[$i][$j];
					}
					$outAvg /= count($outcomes);
					$csv .= sprintf('%.0f%%,', $outAvg);
				}
				
				header('Content-type: text/csv');
				header("Content-Disposition: attachment; filename=OVERVIEW_OUTCOME.csv");
				echo $csv;
				
				
				
			/////////////////////////////////////////////////////	
			}//end overview outcome csv
			else
			{
				$output .= '<h3>This report shows the percentage of students in the 
					semester who earned 70% or higher on all assessments measuring the outcome.</h3>';

				$output .= '<table border="0.5" cellpadding="1">';
				$output .= '<tr bgcolor="#cccccc" color="#000000"><th>Outcome</th>';
				
				$semesters = $model->getSemestersInRange($start, $end);
				$outcomes = $model->getProgramOutcomes($program);
				
				//generate the top row and initialize column arrays
				foreach($semesters as $semester)
				{
					$sem = $semester['semester'];
					$output .= "<th align='center'>$sem</th>";
					if($raw)
					{
						$output .= "<th align='center'>Students Passed</th>";
						$output .= "<th align='center'>Total Students</th>";
					}
				}
				for ($i = 0; $i < count($semesters); $i++)
				{
					$colScore[$i] = 0;
					$colStudPass[$i] = 0;
					$colStud[$i] = 0;
					$colWithStud[$i] = 0;
					for ($j = 0; $j < count($outcomes); $j++)
					{
						$colAvg[$i][$j] = 0;
					}
				}

				$outIndex = 0;
				$output .= "<th align='center'>Row Average</th>";
				if($raw)
				{
					$output .= "<th align='center'>Students Passed</th>";
					$output .= "<th align='center'>Total Students</th>";
				}
				$output .= "</tr>";
				//end top row
				
				$mod = false;
				foreach($outcomes as $outcome)
				{
					$oAbbrev = $outcome['oAbbrev'];
					$output .= "<tr";
					
					if($mod)
					{
						$output .= ' bgcolor="#cccccc" color="#000000"';
						$mod = false;
					}

					else
					{
						$mod = true;
					}
					$output .= "><th align='center'>$oAbbrev</th>";

					$courses = $model->getCoursesForOutcome($oAbbrev);
					foreach($courses as $course)
					{
						//row totals
						$sum = 0;
						$sumStud = 0;
						$sumStudPass = 0;
						$sumWithStud = 0;
						$count = 0;
						$cAbbrev = $course['cAbbrev'];

						foreach($semesters as $semester)
						{
							$semesterId = $semester['semesterId'];
							//$result = $model->calculatePercent($outcome, $cAbbrev, $semesterId);
							$result = $model->calculatePercent($oAbbrev, $cAbbrev, $semesterId);
							$noStudPass = $result['noStudPass'];
							if($noStudPass == '')
								$noStudPass = 0;
						
							$noStud = $result['noStud'];
							$score = $result['score'];
							
							$sum += $score;
							$sumStud += $noStud;
							$sumStudPass += $noStudPass;
						
							$colScore[$count] += $score;
							$colStudPass[$count] += $noStudPass;
							$colStud[$count] += $noStud;
							if($noStud > 0)
							{
								$colWithStud[$count]++;
								$sumWithStud++;
							}
						
							$count++;
						}
					}
				
				
					//variables used for calculating course averages
					$score = 0;
					$pass = 0;
					$stud = 0;
					$cols = 1;
				
					//calculate average of courses in a semester for an outcome
					for($i = 0; $i < count($semesters); $i++)
					{
						if($colWithStud[$i] > 0)
						{
							$score += ($colScore[$i] / $colWithStud[$i]);
							
							$colAvg[$i][$outIndex] += ($colScore[$i] / $colWithStud[$i]);
						}
						$cols++;
						$pass += $colStudPass[$i];
						$stud += $colStud[$i];
					
						//add semester average for outcome to report
						$appendThis = sprintf('%.0f%%', $colWithStud[$i] > 0 ?	$colScore[$i]/$colWithStud[$i] : 0);
						$output .= "<td>$appendThis</td>";
					}
				
					//add average of course averages across semesters to report
					$appendThis = sprintf('%.0f%%', ($cols-1) > 0 ? $score/($cols-1) : 0);	// Fix after 2014 IAB meeting
					$output .= "<td>$appendThis</td>";
					if($raw)
					{
						"<th align='center'>$pass</th>";
						"<th align='center'>$stud</th>";
					}
					$output .= "</tr>";

					$outIndex++;				
				}
				
				$output .= "<tr><th align='center'>Column Average</th>";
				for ($i = 0; $i < count($semesters); $i++)
				{
					$outAvg = 0;
					for ($j = 0; $j < count($outcomes); $j++)
					{
						$outAvg += $colAvg[$i][$j];
					}
					$outAvg /= count($outcomes);
					$appendThis = sprintf('%.0f%%', $outAvg);
					$output .= "<td>$appendThis</td>";
				}
				$output .= "<th align='center'></th>";
				$output .= '</tr></table>';
				
				$_SESSION['table'] = $output;
				$_SESSION['tableName'] = 'OVERVIEW_OUTCOME';
				$_SESSION['tableHeader'] = 'Overview Outcome Report';
				header('Location: ReportsController.php?view=table');
			}
		}
		else if($view == 'course')
		{
			//print_r($_POST);
			$program = $_POST['program'];
			$single = $_POST['single'];
			$start = $_POST['start'];
			$end = $_POST['end'];
			$raw = $_POST['raw'] == 'yes';
			
			if($single !== 'null')//use single semester
			{
				$start = $single;
				$end = $single;
			}
			
			if(isset($_POST['csv']))
			{
				//csv
				$filename = 'OVERVIEW_COURSE';
				
				if($program == 'cac' || $program == 'both')
					$filename .= '_CAC';
				
				if($program == 'eac' || $program == 'both')
					$filename .= '_EAC';
				
				$filename .= '.csv';
				
				$csv = ",";

				$semesters = $model->getSemestersInRange($start, $end);
				$outcomes = $model->getProgramOutcomes($program);
				
				foreach ($outcomes as $outcome)
				{
					$csv .= $outcome['oAbbrev'].",";
				}
	
				$csv .= "Row Average\n";

				$courses = $model->getProgramCoursesInRange($program, $start, $end);

				for ($i = 0; $i <= count($outcomes); $i++)
				{
					$sumCol[$i] = 0;
					$sumColNoStud[$i] = 0;
					$noColPercents[$i] = 0;
				}

				$rowAvgSum = 0;
				foreach ($courses as $course)
				{
					// Initialize variables to accumulate averages
					$sumRowSem = 0;
					$sumRow = 0;
					$sumNoStudSem = 0;
					$sumNoStud = 0;
					$noRowPercents = 0;
					$count = 0;
					$cAbbrev = $course['cAbbrev'];
					$csv .= $cAbbrev.",";

					foreach ($outcomes as $outcome)
					{
						$oAbbrev = $outcome['oAbbrev'];
						$sumRowSem = 0;
						$sumNoStudSem = 0;
						foreach($semesters as $semester)
						{
							$semesterId = $semester['semesterId'];
							$result = $model->calculatePercent($oAbbrev, $cAbbrev, $semesterId);
							$noStud = $result['noStud'];
							$score = $result['score'];
							$sumNoStudSem += $noStud;	
							
							$sumRowSem += $score;
						}

						if ($sumNoStudSem == 0)
						{
							$display = "";
						}
						else if ($raw)
						{
							$display = sprintf("%3d%% %3d",$sumRowSem,$sumNoStudSem);
				
							$sumNoStud += $sumNoStudSem;
							$sumColNoStud[$count] += $sumNoStudSem;
							$noColPercents[$count]++;
							$noRowPercents++;
						}
						else
						{
							$display = sprintf("%3d%%",$sumRowSem);

							$noColPercents[$count]++;
							$noRowPercents++;
						}

						$sumRow += $sumRowSem;
						$sumCol[$count] += $sumRowSem;
						$csv .= $display.",";
						$count++;
					}
	
					if ($raw && $noRowPercents != 0)
					{
						$display = sprintf("%3d%% %3d",($sumRow/$noRowPercents),
										($sumStud/$noRowPercents));

						//$sumCol[count($outcomes)] += $sumRow/$noRowPercents;
						//$noColPercents[count($outcomes)]++;
					}
					else if ($noRowPercents != 0)
					{
						$display = sprintf("%3d%%",($sumRow/$noRowPercents));

						//$sumCol[count($outcomes)] += $sumRow/$noRowPercents;
						//$noColPercents[count($outcomes)]++;
					}
					else
					{
						$display = "";
					}
					$csv .= $display."\n";
				}
				$csv .= "Column Average,";

				for ($i = 0; $i < count($outcomes); $i++)
				{
					if ($raw && $noColPercents[$i] != 0)
					{
						$display = sprintf("%3d%% %3d",($sumCol[$i]/$noColPercents[$i]),
										($sumColNoStud[$i]/$noColPercents[$i]));
					}
					else if ($noColPercents[$i] != 0)
					{
						$display = sprintf("%3d%%",($sumCol[$i]/$noColPercents[$i]));
					}
					else
					{
						$display = "";
					}
					$csv .= $display.",";
				}

				header('Content-type: text/csv');
				header('Content-Disposition: attachment; filename='.$filename.'');
				echo $csv;
 			}
			else
			{
				$filename = 'OVERVIEW_COURSE';
				
				if($program == 'cac' || $program == 'both')
					$filename .= '_CAC';
				
				if($program == 'eac' || $program == 'both')
					$filename .= '_EAC';

				$output .= '<h3>This report shows the percentage of students in the course who 
					earned	70% or higher on all assessments measuring the outcome</h3>';

				$output .= '<table border="0.5" cellpadding="1">';
				$output .= '<tr bgcolor="#cccccc" color="#000000"><th>Course</th>';

				$semesters = $model->getSemestersInRange($start, $end);
				$outcomes = $model->getProgramOutcomes($program);
				
				foreach ($outcomes as $outcome)
				{
					$oAbbrev = $outcome['oAbbrev'];
					$output .= "<th align='center'>$oAbbrev</th>";
				}
	
				$output .= "<th align='center'>Row Average</th></tr>";

				$courses = $model->getProgramCoursesInRange($program, $start, $end);

				for ($i = 0; $i <= count($outcomes); $i++)
				{
					$sumCol[$i] = 0;
					$sumColNoStud[$i] = 0;
					$noColPercents[$i] = 0;
				}

				$rowAvgSum = 0;
				$mod = false;
				foreach ($courses as $course)
				{
					// Initialize variables to accumulate averages
					$sumRowSem = 0;
					$sumRow = 0;
					$sumNoStudSem = 0;
					$sumNoStud = 0;
					$noRowPercents = 0;
					$count = 0;
					$cAbbrev = $course['cAbbrev'];
					$output .= "<tr";
		
					if($mod)
					{
						$output .= ' bgcolor="#cccccc" color="#000000"';
						$mod = false;
					}

					else
					{
						$mod = true;
					}
					$output .= "><th align='center'>$cAbbrev</th>";
					foreach ($outcomes as $outcome)
					{
						$oAbbrev = $outcome['oAbbrev'];
						$sumRowSem = 0;
						$sumNoStudSem = 0;
						foreach($semesters as $semester)
						{
							$semesterId = $semester['semesterId'];
							$result = $model->calculatePercent($oAbbrev, $cAbbrev, $semesterId);
							$noStud = $result['noStud'];
							$score = $result['score'];
							$sumNoStudSem += $noStud;	
							
							$sumRowSem += $score;
						}

						if ($sumNoStudSem == 0)
						{
							$display = "";
						}
						else if ($raw)
						{
							$display = sprintf("%3d%% %3d",$sumRowSem,$sumNoStudSem);
				
							$sumNoStud += $sumNoStudSem;
							$sumColNoStud[$count] += $sumNoStudSem;
							$noColPercents[$count]++;
							$noRowPercents++;
						}
						else
						{
							$display = sprintf("%3d%%",$sumRowSem);

							$noColPercents[$count]++;
							$noRowPercents++;
						}

						$sumRow += $sumRowSem;
						$sumCol[$count] += $sumRowSem;
						$output .= "<td>$display</td>";
						$count++;
					}
	
					if ($raw && $noRowPercents != 0)
					{
						$display = sprintf("%3d%% %3d",($sumRow/$noRowPercents),
										($sumStud/$noRowPercents));

						//$sumCol[count($outcomes)] += $sumRow/$noRowPercents;
						//$noColPercents[count($outcomes)]++;
					}
					else if ($noRowPercents != 0)
					{
						$display = sprintf("%3d%%",($sumRow/$noRowPercents));

						//$sumCol[count($outcomes)] += $sumRow/$noRowPercents;
						//$noColPercents[count($outcomes)]++;
					}
					else
					{
						$display = "";
					}
					$output .= "<td>$display</td></tr>";
				}
				$output .= "<tr><th align='center'>Column Average</th>";

				for ($i = 0; $i < count($outcomes); $i++)
				{
					if ($raw && $noColPercents[$i] != 0)
					{
						$display = sprintf("%3d%% %3d",($sumCol[$i]/$noColPercents[$i]),
										($sumColNoStud[$i]/$noColPercents[$i]));
					}
					else if ($noColPercents[$i] != 0)
					{
						$display = sprintf("%3d%%",($sumCol[$i]/$noColPercents[$i]));
					}
					else
					{
						$display = "";
					}
					$output .= "<td>$display</td>";
				}
				$output .= "<th align='center'></th>";
				$output .= '</tr></table>';
				
				$_SESSION['table'] = $output;
				$_SESSION['tableName'] = $filename;
				$_SESSION['tableHeader'] = 'Overview Course Report';
				header('Location: ReportsController.php?view=table');
			}
		}
		else if($view == 'core')
		{
			$cAbbrev = $_POST['course'];
			$semesterId = $_POST['semester'];
			$semester = $model->getSemester($semesterId);
			$section = $_POST['section'];
			$raw = $_POST['raw'] == 'yes';
			$cName = $model->getCourseName($cAbbrev);
			$outcomes = $model->getCourseOutcomes($cAbbrev);
			
			if(isset($_POST['csv']))
			{
				$csv = 'Outcome,Score,';
				if($raw)
					$csv .= 'Passing Students,Number Of Students,';
				$csv .= "\xA";
				
				foreach($outcomes as $outcome)
				{
					$outcomeDesc = $outcome['oText'];
					$outcomeDesc = str_replace(',', '', $outcomeDesc);
					$outcome = $outcome['oAbbrev'];
					$csv .= "$outcome,";
					
					$result = $model->calculatePercent($outcome, $cAbbrev, $semesterId);
					$score = sprintf('%.0f%%', $result['score']);
					$noStud = $result['noStud'];
					$passingStud = $result['noStudPass'];
					
					$csv .= "$score,";
					if($raw)
						$csv .= "$passingStud,$noStud,";
					$csv .= "$outcomeDesc,";
					$csv .= "\xA";
				}
				
				$course = str_replace(' ', '_', $cAbbrev);
				header('Content-type: text/csv');
				header("Content-Disposition: attachment; filename=CORE_$course.csv");
				echo $csv;
			}
			else
			{
				$output .= '<table border="0.5" cellpadding="1">';
				$output .= '<tr bgcolor="#cccccc" color="#000000"><th ';
				$output .= "align='left'>Outcome</th>";
				$output .= "<th align='left'>Score</th>";
				$output .= "<td>Outcome Description</td>";
				if($raw)
				{
					$output .= "<th align='left'>Passing Students</th>";
					$output .= "<th align='left'>Number of Students</th>";
				}
				$output .= "</tr>";
				
				$mod = false;
				foreach($outcomes as $outcome)
				{
					$outcomeDesc = $outcome['oText'];
					$outcomeDesc = str_replace(',', '', $outcomeDesc);
					$outcome = $outcome['oAbbrev'];
					$output .= '<tr';
					
					if($mod)
					{
						$output .= ' bgcolor="#cccccc" color="#000000"';
						$mod = false;
					}

					else
					{
						$mod = true;
					}
					$output .= "><th align='center'>$outcome</th>";

					$result = $model->calculatePercent($outcome, $cAbbrev, $semesterId);
					$score = sprintf('%.0f%%', $result['score']);
					$noStud = $result['noStud'];
					$passingStud = $result['noStudPass'];
					
					$output .= "<th align='left'>$score</th>";
					if($raw)
					{
						"<th align='left'>$passingStud</th>";
						"<th align='left'>$noStud</th>";
					}
					$output .= "<td>$outcomeDesc</td>";
					$output .= "</tr>";
				}
				
				$course = str_replace(' ', '_', $cAbbrev);
				$output .= '</table>';
				
				$_SESSION['table'] = $output;
				$_SESSION['tableName'] = 'CORE_'.$course;
				$_SESSION['tableHeader'] = 'CORE Report';
				header('Location: ReportsController.php?view=table');
			}
		}
		else if($view == 'outcome')
		{
			$outcome = $_POST['outcome'];
			$single = $_POST['single'];
			$start = $_POST['start'];
			$end = $_POST['end'];
			$raw = $_POST['raw'] == 'yes';
		
			if($single !== 'null')//use single semester
			{
				$start = $single;
				$end = $single;
			}
		
			if(isset($_POST['csv']))
			{
				$csv = ',';
				
				$semesters = $model->getSemestersInRange($start, $end);
				$courses = $model->getCoursesForOutcome($outcome);

				//generate the top row and initialize column arrays
				foreach($semesters as $semester)
				{
					$colScore[] = 0;
					$colStudPass[] = 0;
					$colStud[] = 0;
					$colWithStud[] = 0;
					
					$csv .= $semester['semester'].',';
					if($raw)
						$csv .= 'Students Passed, Total Students,';
				}
				
				$csv .= "Row Average,";
				if($raw)
					$csv .= 'Students Passed, Total Students,';
				$csv .= "\xA";
				
				//start populating table and adding to csv
				foreach($courses as $course)
				{
					$cAbbrev = $course['cAbbrev'];
					$csv .= "$cAbbrev,";
					//row totals
					$sum = 0;
					$sumStud = 0;
					$sumStudPass = 0;
					$sumWithStud = 0;
					$count = 0;
					
					foreach($semesters as $semester)
					{
						$semesterId = $semester['semesterId'];
						$result = $model->calculatePercent($outcome, $cAbbrev, $semesterId);
						
						$noStudPass = $result['noStudPass'];
						if($noStudPass == '')
							$noStudPass = 0;
						
						$noStud = $result['noStud'];
						$score = $result['score'];
						$sum += $score;
						$sumStud += $noStud;
						$sumStudPass += $noStudPass;
						
						$colScore[$count] += $score;
						$colStudPass[$count] += $noStudPass;
						$colStud[$count] += $noStud;
						if($noStud > 0)
						{
							$colWithStud[$count]++;
							$sumWithStud++;
						}
						
						$csv .= sprintf('%.0f%%,', $score);
						if($raw)
						{
							$csv .= "$noStudPass,$noStud,";
						}
						
						$count++;
					}
					
					$csv .= sprintf('%.0f%%,', $sumWithStud > 0 ? $sum/$sumWithStud : 0);
					if($raw)
						$csv .= "$sumStudPass,$sumStud,";
					$csv .= "\xA";
				}
				
				$csv .= 'Column Totals,';
				
				$score = 0;
				$pass = 0;
				$stud = 0;
				$cols =0;
				
				
				for($i = 0; $i < count($semesters); $i++)
				{
					if($colWithStud[$i] > 0)
					{
						$score += ($colScore[$i] / $colWithStud[$i]);
						$cols++;
					}
					$pass += $colStudPass[$i];
					$stud += $colStud[$i];
					
					$csv .= sprintf('%.0f%%,', $colWithStud[$i] > 0 ? $colScore[$i]/$colWithStud[$i] : 0);
					if($raw)
						$csv .= $colStudPass[$i].','.$colStud[$i].',';
				}
				
				$csv .= sprintf('%.0f%%,', $cols > 0 ? $score/$cols : 0);
				if($raw)
					$csv .= "$pass,$stud,";
				$csv .= "\xA";
				
				$outcome = str_replace(' ', '_', $outcome);
				
				header('Content-type: text/csv');
				header("Content-Disposition: attachment; filename=OUTCOME_$outcome.csv");
				echo $csv;
			}
			else
			{
				$output .= '<h3>This report shows the percentage of students in the course
				offering(s) who earned 70% or higher on all assessments measuring for '.
				$outcome.' in the semester(s)</h3>';

				$output .= '<table border="0.5" cellpadding="1">';
				$output .= '<tr bgcolor="#cccccc" color="#000000"><th>Course</th>';

				$semesters = $model->getSemestersInRange($start, $end);
				$courses = $model->getCoursesForOutcome($outcome);

				//generate the top row and initialize column arrays
				foreach($semesters as $semester)
				{
					$colScore[] = 0;
					$colStudPass[] = 0;
					$colStud[] = 0;
					$colWithStud[] = 0;
					
					$sem = $semester['semester'];
					$output .= "<th align='center'>$sem</th>";

					if($raw)
					{
						$output .= "<th align='center'>Students Passed</th>";	
						$output .= "<th align='center'>Total Students</th>";				
					}
				}
					$output .= "<th align='center'>Row Average</th>";
					if($raw)
					{
						$output .= "<th align='center'>Students Passed</th>";	
						$output .= "<th align='center'>Total Students</th>";				
					}

					$output .= '</tr>';
				
				$mod = false;
				//start populating table and adding to csv
				foreach($courses as $course)
				{
					$cAbbrev = $course['cAbbrev'];
					$output .= '<tr';
					
					if($mod)
					{
						$output .= ' bgcolor="#cccccc" color="#000000"';
						$mod = false;
					}
					else
					{
						$mod = true;
					}

					$output .= "><th align='center'>$cAbbrev</th>";
					$sum = 0;
					$sumStud = 0;
					$sumStudPass = 0;
					$sumWithStud = 0;
					$count = 0;
					
					foreach($semesters as $semester)
					{
						$semesterId = $semester['semesterId'];
						$result = $model->calculatePercent($outcome, $cAbbrev, $semesterId);
						
						$noStudPass = $result['noStudPass'];
						if($noStudPass == '')
							$noStudPass = 0;
						
						$noStud = $result['noStud'];
						$score = $result['score'];
						$sum += $score;
						$sumStud += $noStud;
						$sumStudPass += $noStudPass;
						
						$colScore[$count] += $score;
						$colStudPass[$count] += $noStudPass;
						$colStud[$count] += $noStud;
						if($noStud > 0)
						{
							$colWithStud[$count]++;
							$sumWithStud++;
						}
						$appendThis = sprintf('%.0f%%', $score);
						$output .= "<th align='center'>$appendThis</th>";
						
						if($raw)
						{
							$output .= "<th align='center'>$noStudPass</th>";
							$output .= "<th align='center'>$noStud</th>";
						}
						
						$count++;
					}
					$appendThis = sprintf('%.0f%%', $sumWithStud > 0 ? $sum/$sumWithStud : 0);
					$output .= "<th align='center'>$appendThis</th>";
					if($raw)
						{
							$output .= "<th align='center'>$sumStudPass</th>";
							$output .= "<th align='center'>$sumStud</th>";
						}
					$output .= '</tr>';
				}
				
				$output .= "<tr bgcolor='#cccccc' color='#000000'><th align='center'>Column Totals</th>";
				
				$score = 0;
				$pass = 0;
				$stud = 0;
				$cols =0;
				
				
				for($i = 0; $i < count($semesters); $i++)
				{
					if($colWithStud[$i] > 0)
					{
						$score += ($colScore[$i] / $colWithStud[$i]);
						$cols++;
					}
					$pass += $colStudPass[$i];
					$stud += $colStud[$i];
					
					$appendThis = sprintf('%.0f%%', $colWithStud[$i] > 0 ? $colScore[$i]/$colWithStud[$i] : 0);
					$output .= "<th align = 'center'>$appendThis</th>";
					if($raw)
					{
						$output .= "<th align='center'>$colStudPass[$i]</th>";
						$output .= "<th align='center'>$colStud[$i]</th>";
					}
				}
				
				$appendThis = sprintf('%.0f%%', $cols > 0 ? $score/$cols : 0);
				$output .= "<th align = 'center'>$appendThis</th>";
				if($raw)
				{
					$output .= "<th align='center'>$pass</th>";
					$output .= "<th align='center'>$stud</th>";
				}
				$output .= '</tr>';
				
				$output .= '</table>';

				$_SESSION['table'] = $output;
				$_SESSION['tableName'] = 'OUTCOME_'.$outcome;
				$_SESSION['tableHeader'] = 'Outcome Report';
				header('Location: ReportsController.php?view=table');

			}
		}
		else if($view == 'matrix')
		{
		
			$program = $_POST['program'];
			
			/** 
			* Filters outcomes based on selected program
			* @param $var - abbreviation of outcome to be filtered
			* @return True if outcome is for selected program, else false
			*/
			function outcomeFilter($var)
			{
				global $program;
				return ($program == 'both' || stripos($var[0], $program) === 0);
			}
			
			$outcomes = $model->getOutcomes();
			$outcomes = array_filter($outcomes, 'outcomeFilter');
			
			if($program == 'both')
			{
				$courses = $model->getCourses();
				$output = '<h1>CS and SE Student Outcomes</h1>';
			}
			else if($program == 'cac')
			{
				$courses = $model->getCSCourses();
				$output = '<h1>Computer Science Student Outcomes</h1>';
			}
			else
			{
				$courses = $model->getSECourses();
				$output = '<h1>Software Engineering Student Outcomes</h1>';
			}
			
			if(isset($_POST['csv']))
			{
				//csv
				$filename = 'Matrix';
				
				if($program == 'cac' || $program == 'both')
					$filename .= '_CAC';
				
				if($program == 'eac' || $program == 'both')
					$filename .= '_EAC';
				
				$filename .= '.csv';
				
				$csv = ",";
				
				foreach($outcomes as $outcome)
				{
					$csv .= $outcome['oAbbrev'].",";
				}
				
				$csv .= "\xA";
				
				foreach($courses as $course)
				{
					$cAbbrev = $course['cAbbrev'];
					$csv .= "$cAbbrev,";
					
					if($program == 'both')
					{
						$courseOutcomes = $model->getCourseOutcomes($cAbbrev);
					}
					else if($program == 'cac')
					{
						$courseOutcomes = $model->getCourseCSOutcomes($cAbbrev);
					}
					else
					{
						$courseOutcomes = $model->getCourseSEOutcomes($cAbbrev);
					}
								
					$count = 0;
					foreach($outcomes as $outcome)
					{
						$oAbbrev = $outcome['oAbbrev'];
						
						if($count < count($courseOutcomes) && $oAbbrev == $courseOutcomes[$count]['oAbbrev'])
						{
							$csv .= "X,";
							$count++;
						}
						else
						{
							$csv .= ",";
						}
					}
					$csv .= "\xA";
				}
				
				header('Content-type: text/csv');
				header("Content-Disposition: attachment; filename=$filename");
				echo $csv;
			}
			else
			{
				$output .= '<h3>This report shows the outcomes measured by each course in the program.</h3>';
				$output .= '<table border="0.5" cellpadding="1">';
				$output .= '<tr bgcolor="#cccccc" color="#000000"><th></th>';
				
				foreach($outcomes as $outcome)
				{
					$oAbbrev = $outcome['oAbbrev'];
					$output .= "<th align='center'>$oAbbrev</th>";
				}
				
				$output .= '</tr>';
				
				$mod = false;
				foreach($courses as $course)
				{
					$cAbbrev = $course['cAbbrev'];
					
					$output .= "<tr";
					if($mod)
					{
						$output .= ' bgcolor="#cccccc" color="#000000"';
						$mod = false;
					}
					else
					{
						$mod = true;
					}
					$output .= "><th>$cAbbrev</th>";
					
					if($program == 'both')
					{
						$courseOutcomes = $model->getCourseOutcomes($cAbbrev);
					}
					else if($program == 'cac')
					{
						$courseOutcomes = $model->getCourseCSOutcomes($cAbbrev);
					}
					else
					{
						$courseOutcomes = $model->getCourseSEOutcomes($cAbbrev);
					}
					
					$count = 0;
					foreach($outcomes as $outcome)
					{
						$oAbbrev = $outcome['oAbbrev'];
						
						$output .= '<td align="center">';
						
						if($count < count($courseOutcomes) && $oAbbrev == $courseOutcomes[$count]['oAbbrev'])
						{
							$output .= 'X';
							$count++;
						}
						else
						{
							$output .= ' ';
						}
						$output .= '</td>';
					}
					$output .= '</tr>';
				}
				$output .= '</table>';
				
				$_SESSION['table'] = $output;
				$_SESSION['tableName'] = 'Matrix.pdf';
				$_SESSION['tableHeader'] = 'Matrix Report';
				header('Location: ReportsController.php?view=table');
			}
		}
	}
?>