/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 05 - Machine Learning
*	File - NumCluster.cpp
*
********************************************/
#include <vector>
#include "math.h"
#include "NumCluster.h"
#include "Cluster.h"


template <class ItemType>
NumCluster<ItemType>::NumCluster(std::vector<dataPoint<ItemType>>& dataPts, int numCent, 
	std::vector<std::string>& fieldTitles) : Cluster<ItemType>(dataPts, numCent, fieldTitles){
		double valueSpread[fieldTitles.size()*2];
}

//Adust a numeric Centroid by averaging the value of the closest datapoints
template <class ItemType>
void NumCluster<ItemType>::adjustCentroid(){
	
	for(int i = 0; i < centroids.size(); i++){
		int counter = 0;
		double avg[fieldNames.size()];
		
		for(int j = 0; j < data.size(); j++){
			
			if(data[j].closestCent() == i){
				for(int x = 0; x < fieldNames.size(); x++)
					avg[x] = data[j].getValue(x);
				counter++;
			}
			
		}
		
		for(int j = 0; j < fieldNames.size(); j++){
			avg[j] = avg[j] / counter;
			centroids[i].setVal(avg[j], j);
		}
	}
}

//finds the numeric distance between the centroids and data points.
template <class ItemType>
double NumCluster<ItemType>::findDistance(Centroid<ItemType> cent, dataPoint<ItemType> pt){
	double distance;
	for(int i = 0; i < fieldNames.size(); i++){
		distance += ( cent.getValue(i) - pt.getValue(i) ) * ( cent.getValue(i) - pt.getValue(i) );
	}
	distance = sqrt(distance);
	return distance;
}

//Finds range of numeric values, allows to find a random value later
template <class ItemType>
void NumCluster<ItemType>::findValues(){
	
	//posVal[i][j] = posVal[i*data.size()+j]
	//Value[0] = Max, Value[1] = Min
	valueSpread = new double[fieldNames.size() * 2];

	//Check if nominal data, if it is, find all values possible.
	
		for(int i = 0; i < fieldNames.size(); i++){
			for(int j = 0; j < data.size(); j++){
				double numericValue = data[j].getValue(i);
				
				
				//if it's larger than the current max, or smaller than the current min
				if(numericValue > valueSpread[i*data.size()]){
					valueSpread[i*data.size()] = numericValue;
				}else if(numericValue < valueSpread[i*data.size()+1]){
					valueSpread[i*data.size()+1] = numericValue;
					
				}
			}//end J for

		}//end i for
}

//Creates Numeric Centroids that will be used to define clusters
template <class ItemType>
void NumCluster<ItemType>::genCentroid(int numCent){
	for(int i = 0; i < numCent; i++){
		Centroid<double> nextCentroid(fieldNames.size());
		for(int j = 0; j < fieldNames.size(); j++){
			double val = rand % valueSpread[j*data.size()] + valueSpread[j*data.size()+1];
			nextCentroid.setVal(val, j);
		}
		centroids.push_back(nextCentroid);
	}
}


