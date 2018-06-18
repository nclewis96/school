/*
/	Nathaniel Lewis
/ 	Proj three
/	CSCI 332, PCurtiss
*/
#ifndef _POINTSET_H
#define _POINTSET_H

using namespace std;
#include <vector>
#include "Point.h"
#include <iostream>
#include <fstream>

class PointSet {

private :
	
	vector<Point> pointSet;
	
	
	
	struct polarSort {
		PointSet* memberInfo;
		polarSort(PointSet* set): memberInfo(set){}
		
		bool operator()(Point a, Point b){
			if(memberInfo->pointSet.size() < 1)
				return false;
					
			Point pivotPt = memberInfo->pointSet.front();
			int orderOfPoints = pivotPt.turnDirection(a,b);
			if(orderOfPoints == 0)
				return pivotPt.distance(a) < pivotPt.distance(b);
			return(orderOfPoints == -1);
				
		}
	};

	
public :
	
	PointSet();
	
	PointSet(string filename);
	
	PointSet(int numPoints);
	
	void add(Point toAdd);
	
	PointSet bruteForce();
	
	PointSet grahamScan();
	
	string toString();
	
	
};
#endif