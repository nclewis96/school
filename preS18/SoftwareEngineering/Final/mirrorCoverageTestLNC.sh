#!/bin/bash

#Nathaniel Lewis
#Based on script designed by Kendall Schmit

#General precondition
	#If script will not run, make sure to run "chmod 744 serviceStationLNCtestRun.sh"
	#Change the initials variable below to match the initials of the student run being performed
	#Testing is ran by putting the following into the shell "./mirrorCoverageTestLNC.sh"
	
#Code file requirements
	#Code file should be named serviceStationLFM.cpp where LFM matches the variable initials below.
	#Code file should be a valid cpp file and should not require any other files to compile
	
#Test file requirements
	#Test files should be kept in a subfolder named unit_tests under where this script is kept
	#Test files should be named mirrorIn01.txt and mirrorOut01.txt with a different number for each pair
	#Test files with the same number should have a matching output for the given input file.
	#The test_count section should be updated to reflect the number of test cases
	#Test case files should be numbered with two digits from 01 to test_cases
	#Test files must have a blank line at the end to ensure that the compare operation reads the whole file
	
	
#Output of this script
	#Output is saved into a file mirrorCoverageTestRsltsLFM.txt, where LFM is defined by the initials variable
	#Output starts with a header and ends with a footer
	#Output will be the code, proceeded by a number telling how many times it was executed.
	
#Change these vars/functions as tests change
initials=LNC
exe=./mirrorCoverage$initials
file_prefix="mirrorUnitTestsLNC/mirror"$initials"T"
test_count=17
out_file="mirror"$initials"testRslts2.txt"

in_file_name(){
    echo "$file_prefix"$(printf "%02d" $1)"in.txt"
}

out_file_name(){
    echo "$file_prefix"$(printf "%02d" $1)"out.txt"
}

#Main procedure:
g++ -std=c++11 -fprofile-arcs -ftest-coverage -c mirror$initials.cpp
g++ -fprofile-arcs -ftest-coverage -o mirrorCoverage$initials mirror$initials.o
gcov ./mirror$initials
rm mirror$initials.o
rm $out_file
echo "+++mirror"$initials" Test Run+++" >> $out_file
echo "Testing the file mirror"$initials".cpp" >> $out_file
echo "" >> $out_file

success=true
failCount=0

for ((i = 1; i <= test_count; i++))
do
    echo "Input File: "$(in_file_name $i)"  Output File: "$(out_file_name $i) >> $out_file
    result=$($exe <$(in_file_name $i))
    expected=$(<$(out_file_name $i))
    if [ "$result" != "$expected" ]
    then
        success=false
		echo "FAILED" >> $out_file
		failCount=$(($failCount+1))
	else
		echo "Passed" >> $out_file
    fi
	echo "" >> $out_file
done

if [ $success = true ]
then
    echo "All test cases passed." >> $out_file
    echo "" >> $out_file
else
    echo $failCount" test cases FAILED" >> $out_file
    echo "" >> $out_file
fi


echo "---mirror"$initials" Test Run---" >> $out_file

cat mirrorLNC.cpp.gcov > mirrorCoverageTestRsltsLNC.txt
