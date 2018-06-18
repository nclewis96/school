/* Nathaniel Lewis
 * Proj 2 - Numerical Integration
 * Serial Version
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
	
	//retrieves the num div
	cout<<"How many divisions would you like to use? ";
	cin >> n;
	
	double x, y, sum, pi = 0.0;
	
	//The width of each rectangle
	double inc = r/(double) n;
	
	
	startT = omp_get_wtime();
	
	//Calculates the sum of the area of the rectangles
	for(int i = 0; i < n; i++) {
	
		//find the x coord
		x = (r + i) * inc;
		//finds the y coord using f(x) = sqrt(r^2-x^2) where r = 1
		y = sqrt(r - (x*x) );
		//Finds area (l*w) where w = inc and l = y
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