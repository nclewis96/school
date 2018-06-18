/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 05 - Machine Learning
*	File - Cluster.h
********************************************/

#include <vector>
#include "Centroid.h"
#include <string>
#include "dataPoint.h"

#ifndef CLUSTER
#define CLUSTER


template <class ItemType>
class Cluster {
	
	public:
	
		Cluster(std::vector<dataPoint<ItemType>>& dataPts, int numCent, std::vector<std::string>& fieldTitles);
		void findClusters();
		std::vector<Centroid<ItemType>> getCentroids();
		dataPoint<ItemType> findAnswer(dataPoint<ItemType>& pt);
	
	protected:
		int numCentroids;
	
	private: 
		void setup();
		virtual void adjustCentroid() = 0;
		virtual double findDistance(Centroid<ItemType> cent, dataPoint<ItemType> pt) = 0;
		virtual void findValues() = 0;
		virtual void genCentroid(int numCent) = 0;
		std::vector<dataPoint<ItemType>> data;
		std::vector<Centroid<ItemType>> centroids;
		std::vector<std::string> fieldNames;
		
};

#endif