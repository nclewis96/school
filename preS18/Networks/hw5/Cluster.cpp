/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 05 - Machine Learning
*	File - Cluster.cpp
*
********************************************/
#include <vector>
#include "math.h"
#include "Cluster.h"
#include "Centroid.h"
#include "dataPoint.h"

template <class ItemType>
Cluster<ItemType>::Cluster(std::vector<dataPoint<ItemType>>& dataPts, int numCent, std::vector<std::string>& fieldTitles){
	data = dataPts;
	fieldNames = fieldTitles;
	numCentroids = numCent;
}

//Recursively calls itself until points quit reassigning themselves to Centroids
template <class ItemType>
void Cluster<ItemType>::findClusters(){
	int numChanged = 0;
	for(int i = 0; i < data.size(); i ++) {
		for(int j = 0; j < centroids.size(); j++){
			Centroid<ItemType> cent = centroids[j];
			dataPoint<ItemType> dataHolder = data[i];
			double dist = findDistance(cent, dataHolder);
			if(dist < data[i].getDistanceToClosest()){
				data[i].changeClosest(j,dist);
				numChanged++;
			}
		}
			
	}
	
	
	if(numChanged != 0){
		adjustCentroid();
		findClusters();
	}
}
template <class ItemType>
dataPoint<ItemType> Cluster<ItemType>::findAnswer(dataPoint<ItemType>& pt){
	double minDist = 100000;
	int closestCent;
	for(int i = 0; i < centroids.size(); i++){
		double dist = findDistance(centroids[i], pt);
		if(dist < minDist){
			minDist = dist;
			closestCent = i;
		}
	}
	return centroids[closestCent];
}

//Returns the Centroids
template <class ItemType>
std::vector<Centroid<ItemType>> Cluster<ItemType>::getCentroids(){
	return centroids;
}

template <class ItemType>
void Cluster<ItemType>::setup(){
	findValues();
	genCentroid(numCentroids);
}




















