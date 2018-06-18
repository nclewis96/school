/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 05 - Machine Learning
*	File - Centroid.cpp
********************************************/
#ifndef Centroid_Imp
#define Centroid_Imp
#include <cstddef>
#include "Centroid.h"
template <class ItemType>
Centroid<ItemType>::Centroid(int numVals){
	numValues = numVals;
}

//Returns the value at the position requested.
template <class ItemType>
ItemType Centroid<ItemType>::getValue(int valPos){
	return data[valPos];
}

//Sets a value at the position requested to the given value
template <class ItemType>
void Centroid<ItemType>::setVal(ItemType value, int pos){
	data[pos] = value;
}

template<class ItemType>
ItemType Centroid<ItemType>::getAnswer(){
	return data[numValues];
}
#endif
