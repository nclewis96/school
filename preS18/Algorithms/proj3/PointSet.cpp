/*
/	Nathaniel Lewis
/ 	Proj three
/	CSCI 332, PCurtiss
*/


#include "PointSet.h"
#include <cstdlib>
#include <math.h>
#include <algorithm>


PointSet::PointSet(){}

//reads points in from a file
PointSet::PointSet(string filename){
	ifstream file(filename);
	if(!file.is_open()){
		cout << "Error opening file" << endl;
		return;
	}
	double x = 0.0, y = 0.0;
	while(file >> x && file >> y) 
		add(Point(x,y) );
}

//Creates a set of random points with size "numPoints"
PointSet::PointSet(int numPoints){
	double randomX = 0, randomY = 0;
	srand( time(NULL) );
	for(int i = 0; i < numPoints; i++){
	randomX = (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * 200 - 100;
	randomY = (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * 200 - 100;
	
	add( Point(randomX, randomY) );
	}
}

//Adds a new point to the Set
void PointSet::add(Point toAdd) {
	if(pointSet.size() > 0 && toAdd.getY() <= pointSet.front().getY() 
		&& toAdd.getX() <= pointSet.front().getX() ) {
		pointSet.insert(pointSet.begin(), toAdd);	
	}
	else {
		pointSet.push_back(toAdd);
	}
	
}

//Finds the hull of the vector by checking the lines between all points in the vector
PointSet PointSet::bruteForce() {
	
	PointSet orderedPts = PointSet();
	orderedPts.pointSet = this->pointSet;
	int numPts = orderedPts.pointSet.size();
	
	if(numPts < 3)
		return orderedPts;
	
	PointSet hull;

	for(int i = 0; i < numPts - 1; i++){
	
		Point a = orderedPts.pointSet.at(i);
		for(int j = i + 1; j < numPts; j++){
			
			bool onHull = true;
			int prevArea = 0;
			Point b = orderedPts.pointSet.at(j);
			for(int k = 0; k < numPts; k++){
				
				Point c = orderedPts.pointSet.at(k);
				
				int curArea = a.turnDirection(b,c);
				if(prevArea != 0 ){
					if( (curArea > 0 && prevArea < 0) || (curArea < 0 && prevArea > 0) ) {
						onHull = false;
						break;
					}
				} else {
					prevArea = curArea;
				}
			}
			if(onHull){
				bool addA = true, addB = true;
				for(unsigned int k = 0; k < hull.pointSet.size(); k++) {
					
					if(		(hull.pointSet.at(k).getX() == a.getX() ) 
						 && (hull.pointSet.at(k).getY() == a.getY() ) )
						 addA = false;
					if(		(hull.pointSet.at(k).getX() == b.getX() ) 
						 && (hull.pointSet.at(k).getY() == b.getY() ) )
						 addB = false;
				}
				if(addA)
					hull.pointSet.push_back(a);
				if(addB)
					hull.pointSet.push_back(b);
			}
		}
	}
	
	polarSort angle(&hull);
	sort(hull.pointSet.begin() + 1, hull.pointSet.end(), angle);
	
	for(unsigned int i = 0; i < hull.pointSet.size() - 2; i++) {
		for(unsigned int j = i + 1; j < hull.pointSet.size() - 1; j++){
			for(unsigned int k = j + 1; k < hull.pointSet.size(); k++){
				if(hull.pointSet.at(i).turnDirection(hull.pointSet.at(j), hull.pointSet.at(k) ) == 0) {
					hull.pointSet.erase(hull.pointSet.begin() + j);
					k--;
				}
			}
		}
	}
	
	return hull;
		
}

//Finds the hull of the vector of points using the graham scan algorithm.
PointSet PointSet::grahamScan() {
	
	PointSet orderedPts = PointSet();
	orderedPts.pointSet = this->pointSet;
	
	if(orderedPts.pointSet.size() < 3)
		return orderedPts;
	
	PointSet hull;
	
	polarSort angle(this);
	
	sort(orderedPts.pointSet.begin() + 1, orderedPts.pointSet.end(), angle);
	
	hull.pointSet.push_back(orderedPts.pointSet.at(0) );
	hull.pointSet.push_back(orderedPts.pointSet.at(1) );
	
	if(hull.pointSet.front().turnDirection(hull.pointSet.back(), orderedPts.pointSet.at(2) ) == 0 )
		hull.pointSet.pop_back();
	hull.pointSet.push_back(orderedPts.pointSet.at(2) );
	
	for(unsigned int i = 3; i < orderedPts.pointSet.size(); i++){
		Point top = hull.pointSet.back();
		hull.pointSet.pop_back();
		while(hull.pointSet.back().turnDirection(top, orderedPts.pointSet.at(i) ) != -1 ){
			top = hull.pointSet.back();
			hull.pointSet.pop_back();
		}
		hull.pointSet.push_back(top);
		hull.pointSet.push_back(orderedPts.pointSet.at(i) );
	}
	
	return hull;
}


string PointSet::toString() {
	string output = "";
	for(unsigned int i = 0; i < pointSet.size(); i++){
		output += pointSet.at(i).toString() + "\n";
	}
	return output;
	
}