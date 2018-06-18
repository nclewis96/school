/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 05 - Machine Learning
*	File - NumCluster.h
********************************************/

#include <vector>
#include "Centroid.h"
#include "Cluster.h"

#ifndef NUMERIC_CLUSTER
#define NUMERIC_CLUSTER

template <class ItemType>
class NumCluster : public Cluster<ItemType> {
	
	public:
		NumCluster(std::vector<dataPoint<ItemType>>& dataPts, int numCent, std::vector<std::string>& fieldTitles);

	
	private: 
		void adjustCentroid();
		double findDistance(Centroid<ItemType> cent, dataPoint<ItemType> pt);
		void findValues();
		void genCentroid(int numCent);
		std::vector<dataPoint<ItemType>> data;
		std::vector<Centroid<ItemType>> centroids;
		std::vector<std::string> fieldNames;
		double* valueSpread;
};
#include "NumCluster.cpp"
#endif
