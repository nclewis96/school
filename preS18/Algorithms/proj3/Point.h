/*
/	Nathaniel Lewis
/ 	Proj three
/	CSCI 332, PCurtiss
*/

#ifndef _POINT_H
#define _POINT_H

#include<string>

using namespace std;

class Point {
	private:
		double x;
		double y;
		
	public:
	
		Point(double newX, double newY);
			
		 double getX();
		
		 void setX(const double &newX);
		
		 double getY();
		
		 void setY(const double &newY);
		
		 int turnDirection(const Point p1, const Point p2);
		
		 double distance(Point &P1);

		string toString();
};

#endif