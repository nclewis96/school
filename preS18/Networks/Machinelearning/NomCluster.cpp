/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 05 - Machine Learning
*	File - NomCluster.cpp
*
********************************************/
#ifndef Nom_Cluster_Imp
#define Nom_Cluster_Imp

#include <vector>
#include "math.h"
#include "NomCluster.h"
#include "Cluster.h"

template <class ItemType>
NomCluster<ItemType>::NomCluster(std::vector<dataPoint<ItemType>>& dataPts, int numCent, 
	std::vector<std::string>& fieldTitles) : Cluster<ItemType>(dataPts, numCent, fieldTitles){
		
	}

//Adjust a nominal Centroid by finding the mode of the values in the datapoints closest to the Centroid and using that value 
template <class ItemType>
void NomCluster<ItemType>::adjustCentroid(){
	
	for(int i = 0; i < (int)centroids.size(); i++){
		
		int valueMode[fieldNames.size() * data.size()];
		std::string centVals[fieldNames.size() * data.size()];
		
		for(int j = 0; j < (int)data.size(); j++){
			
			if(data[j].closestCent() == i){
				for(int x = 0; x < (int)fieldNames.size(); i++){
					
					std::string nominalValue = data[j].getValue(x);
					bool inPossible = false;
					//Check to see if the value is already in the array
					for(int y = 0; y < (int)data.size(); y++){
						if(centVals[y*(int)data.size()+ x].compare(data[j].getValue(x)) == 0)
							inPossible = true;
					}
					if(inPossible){
						valueMode[x * (int)data.size() + j]++;
					}else{
						centVals[x*(int)data.size() + j] = data[j].getValue(x);
						valueMode[x * (int)data.size() + j] = 1;
					}
					
				}
			}
			
		}
		
		for(int j = 0; j < (int)fieldNames.size(); j++){
			int mode  = 0;
			for(int x = 0; x < (int)data.size(); x++){
				if(valueMode[x* (int)data.size() + j] > mode){
					mode = valueMode[x*(int)data.size() + j];
				}
			}
			centroids[i].setVal(possibleVals[j*data.size() + mode], j);
		}
		
		
	}
}

//finds the distance between the Centroids and Data points
template <class ItemType>
double NomCluster<ItemType>::findDistance(Centroid<ItemType> cent, dataPoint<ItemType> pt){
	int distance;
	for(int i = 0; i < (int)fieldNames.size(); i++){
		if(cent.getValue(i).compare(pt.getValue(i)) != 0){
			distance++;
		}
	}
	return distance;
}


//Finds the possible values and the number each time is in the data set
template <class ItemType>
void NomCluster<ItemType>::findValues(){
	
	//posVal[i][j] = posVal[i*data.size()+j]
	possibleVals = new std::string[fieldNames.size() * data.size()];
		for(int i = 0; i < (int)fieldNames.size(); i++){
			for(int j = 0; j < (int)data.size(); j++){
				std::string nominalValue = data[j].getValue(i);
				bool inPossible = false;
				//Check to see if the value is already in the array
				for(int x = j; x < (int)data.size(); x++){
					if(possibleVals[i*data.size()+ x].compare(data[j].getValue(i)) ==0)
						inPossible = true;
				}
				//if it's not in the array, add it
				if(inPossible){
					possibleVals[i*data.size()+j] = "";
				}else{
					possibleVals[i*data.size()+j] = nominalValue;
				}
			}//end J for

		}//end i for
}//end findValMode

//Creates Nominal Centroids that will be used to define clusters
template <class ItemType>
void NomCluster<ItemType>::genCentroid(int numCent){
	for(int i = 0; i < numCent; i++){
		Centroid<std::string> nextCentroid(fieldNames.size());
		for(int j = 0; j < (int)fieldNames.size(); j++){
			std::string value = "";
			while(value.compare("") == 0){
				int pos = rand() % (int)data.size();
				value = possibleVals[j*data.size()+pos];
			}
		}
		centroids.push_back(nextCentroid);
	}
}
#endif
