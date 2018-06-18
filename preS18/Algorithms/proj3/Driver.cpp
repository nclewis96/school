/*
/	Nathaniel Lewis
/ 	Proj three
/	CSCI 332, PCurtiss
*/

#include "PointSet.h"
#include "Point.h"
#include <omp.h>


int main(int argc, char* argv[])
{
	string filename;
	PointSet set;
	double startT = 0, endT = 0;
	
	if(argc > 1)
	{
		filename = argv[1];
		set = PointSet(filename);
	}
	else
	{
		cout << "How many points would you like generated?  ";
		int numPoints = 0;
		cin >> numPoints;
		set = PointSet(numPoints);
	}	
	cout << set.toString() << endl;
	
	startT = omp_get_wtime();
	PointSet grahamSet = set.grahamScan();
	endT = omp_get_wtime() - startT;
	
	cout << grahamSet.toString() << endl;
	cout << endT << endl;
	
	startT = omp_get_wtime();	
	PointSet bruteHull = set.bruteForce();
	endT = omp_get_wtime() - startT;
	
	cout << bruteHull.toString() << endl;
	cout << endT << endl;
	
	return 0;
}