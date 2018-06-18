/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 05 - Machine Learning
*	File - dataPoint.h
********************************************/

#include "Centroid.h"
#include <vector>
#ifndef DATA_POINT
#define DATA_POINT

template <class ItemType>
class dataPoint : public Centroid<ItemType>{
	
	public:
	
		dataPoint(int numVals);
		int closestCent();
		void changeClosest(int centPos, int newDistance);
		int getDistanceToClosest();
		bool setCentChanged(bool changed);
		bool getCentChanged();
		ItemType getAnswer();
	
	private:
	
		std::vector<ItemType> data;
		int numValues;
		int closest;
		bool centroidChanged;
		int distanceToCentroid;
		
};
#include "dataPoint.cpp"
#endif
