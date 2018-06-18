/*
/	Nathaniel Lewis
/ 	Proj three
/	CSCI 332, PCurtiss
*/
#include "Point.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
using namespace std;

Point::Point(double newX, double newY) {
	x = newX;
	y = newY;
}

double Point::getX() {
	return x;
}

void Point::setX(const double &newX){
	x = newX;
}

double Point::getY() {
	return y;
}

void Point::setY(const double &newY){
	y = newY;
}

//Checks if the point is to the left, right, or in line with the current point
int Point::turnDirection(const Point p1, const Point p2) {
	double crossProd = ( (p1.x - this->x)*(p2.y - this->y)
						  - (p1.y - this->y)*(p2.x - this->x) );

	if(crossProd < 0) // Clockwise Turn
		return 1;
	else if(crossProd > 0) // Counter Clockwise Turn
		return -1;	

	return 0; // No turn, or collinear 
}

//Calculates the euclidean distance between the given and current points
double Point::distance( Point &P1){
	double x2 = P1.getX();
	double y2 = P1.getY();
	double distance = sqrt( (x2 - x)*(x2 - x) + (y2 - y)*(y2 - y) );
	
	return distance;
}

string Point::toString() {
	return ("(" + to_string(x) + ", " + to_string(y) + ")");
	
	
}
/* Test main
int main () {

	Point p1 = Point(0.0, 0.0);
	Point p2 = Point(1.0, 0.0);
	
	cout << p1.distance(p2) << endl;
	
	p2.setX(3.0);

	cout << p1.distance(p2) << endl;
	
	p2.setY(4.0);
	
	cout << p1.distance(p2) << endl;

}

*/


