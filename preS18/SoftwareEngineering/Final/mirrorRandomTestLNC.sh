#@Title:	mirrorLNCtestRun.sh
#@Author:	NathanielLewis
#@Date:		12/10/2016

#@Run Instructions:	Simply type "bash mirrorLNCtestRun.sh" in the katie terminal
#@Preconditions:	In order for this program to work successfully, all input and output
#                   test files must be in the same directory as this shell program and
#                   the "MirrorLNC.cpp" file

#Bash program to compile and run tests for MirrorNKL.cpp
#This program will work for any file named "smtst_*_in" and "smtst_*_out" as long as * is in {1-34}
#It will output the test results to a file named "MirrorLNCtestResults.txt"

#Compile the current version
g++ -std=c++11 mirrorLNC.cpp -o testLNC
g++ -std=c++11 mirrorNKL.cpp -o testNKL

#Test output file
outFile=mirrorLNCRandomTestRslts.txt

#Formatting for output file Header
printf "+++MirrorLNC Test Run+++\n" > $outFile
printf "Testing the file MirrorLNC.cpp against MirrorNKL.cpp\n" >> $outFile
printf "\n-----------------------------------------\n" >> $outFile
#Count how many tests failed
numFailed=0
numTests=20
for i in mirrorRandomTestsLNC/mirrorLNC*.txt
do
	testNum=$(echo $i| cut -d'_' -f 2)
	outTestLNC=mirrorLNCT$iout.txt
	outTestNKL=mirrorNKL$iout.txt
	./testLNC < $i > $outTestLNC
	./testNKL < $i > $outTestNKL
	printf "Input File:\t%s\t" $i >> $outFile

	diff -w $outTestLNC $outTestNKL > /dev/null
	if [[ $? -eq 0 ]]
	then
		printf "Passed\n" >> $outFile
	else
		printf "Fuck\n" >> $outFile
		let "numFailed++"
	fi
	
	printf "\n-----------------------------------------\n" >> $outFile
done

rm mirrorLNCT$iout.txt
rm mirrorNKL$iout.txt

#Print out how many test failed or All tests passed
if [[ $numFailed -eq 0 ]]
then
	printf "All tests passed" >> $outFile
else
	printf "\n%s tests FAILED" $numFailed >> $outFile
fi


#Mark the end of file for the test results
printf "\n\n---MirrorLNC Test Run---\n" >> $outFile

