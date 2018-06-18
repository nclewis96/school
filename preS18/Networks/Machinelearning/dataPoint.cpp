/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 05 - Machine Learning
*	File - dataPoint.cpp
********************************************/
#ifndef Data_Point_Imp
#define Data_Point_Imp
#include "dataPoint.h"
#include <cstddef>
#include "Centroid.h"

//Default constructor, tracks the number of values that will be in this dataPoint. 
//AKA the number of dimensions
template <class ItemType>
dataPoint<ItemType>::dataPoint(int numVals) : 
	Centroid<ItemType>(numVals){
}
		
//Returns the closest Centroid to this data Point
template<class ItemType>
int dataPoint<ItemType>::closestCent(){
	return closest;
}

//Changes the closest centroid, and distance to the centroid.
template<class ItemType>
void dataPoint<ItemType>::changeClosest(int centPos, int newDistance){
	closest = centPos;
	distanceToCentroid = newDistance;
}

//Returns the distance to the closest Centroid. Used when finding if another centroid would be closer.	
template<class ItemType>		
int dataPoint<ItemType>::getDistanceToClosest(){
	return distanceToCentroid;
}

//Sets a bool that tracks whether or not the centroid has been changed on the last iteration
template<class ItemType>
bool dataPoint<ItemType>::setCentChanged(bool changed){
	centroidChanged = changed;
	return centroidChanged;
}

//Returns a bool that tracks whether the centroid has been changed.
template<class ItemType>
bool dataPoint<ItemType>::getCentChanged(){
	return centroidChanged;
}

template<class ItemType>
ItemType dataPoint<ItemType>::getAnswer(){
	return data[numValues];
}
#endif
