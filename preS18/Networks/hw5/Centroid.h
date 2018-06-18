/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 05 - Machine Learning
*	File - Centroid.h
********************************************/

#include <vector>

#ifndef CENTROID_H
#define CENTROID_H

template <class ItemType>
class Centroid{
	
	public:
	
		Centroid(int numVals);
		ItemType getValue(int valPos);
		void setVal(ItemType value, int pos);
		ItemType getAnswer();
		
	protected: 
	
		int numValues;
		
	private: 
		

		std::vector<ItemType> data;
		
	
};

#endif