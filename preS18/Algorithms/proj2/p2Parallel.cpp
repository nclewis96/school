/* Nathaniel Lewis
 * Proj 2 - Numerical Integration
 * Parallel Version
*/

#include <omp.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

int main () {
	
	double startT, totT;
	int n;
	int r = 1;
	
	int cores;
	
	//retrieves the num div
	cout<<"How many divisions would you like to use? ";
	cin >> n;
	
	cout<<"How many threads would you like to use? ";
	cin >> cores;
	
	//If the number input isn't valid, finds the num of cores on the compiling device
	if(cores<=0) 
		cores = omp_get_num_procs();
	
	double x, y,  pi = 0.0;
	double sum = 0.0;
	
	//The width of each rectangle
	double inc = r/(double) n;
	
	//Sets the number of threads
	omp_set_num_threads(cores);
	
	startT = omp_get_wtime();
	
	#pragma omp parallel for reduction(+:sum) private(x,y)
	//Calculates the sum of the area of the rectangles
	for(int i = 0; i < n; i++) {
	
		//find the x coord
		x = (r + i) * inc;
		//finds the y coord using f(x) = sqrt(r^2-x^2) where r = 1
		y = sqrt(r - (x*x) );
		//Finds area l*w where w = inc and l = y
		sum += inc*y;
	
	}
	
	//calculates pi using the reiman sum
	pi = 4 * (sum + inc/2);
	
	totT= omp_get_wtime() - startT;
	
	cout.precision(20);
	
	//outputs the final results
	cout << "Pi = " << pi << endl;
	cout << "Time: " << totT << endl;


}