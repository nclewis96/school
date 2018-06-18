/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 05 - Machine Learning
*	File - driver.cpp
********************************************/
#include <fstream>
#include <istream>
#include <vector>
#include <typeinfo>
#include <iostream>
#include "dataPoint.h"
#include "Centroid.h"
#include "NomCluster.h"
#include "NumCluster.h"


int main (int argc, char*argv[]){
	char valueTitles[100] ,rowValues[100], fieldVals[100];
	std::string dataFile, dataType;
	std::string delimeter = ","; 
	std::cout << "Please input file name!" << std::endl;
	std::cin >> dataFile;
	std::cout << "Is this nominal or numeric data?" <<std::endl;
	std::cin >> dataType;
	int numCentroids;
	std::cout << "How many Centroids?" << std::endl;
	std::cin >> numCentroids;
	
	std::vector<std::string> fieldNames;
	std::vector<std::string> dataValues;
	
	std::vector<dataPoint<std::string>> nominalData;
	std::vector<dataPoint<std::string>> nominalTesting;
	std::vector<dataPoint<double>> numericData;
	std::vector<dataPoint<double>> numericTesting;
	
	//Read in the contents of the CSV file
	try{
		
		std::fstream file(dataFile);
		//The first line that contains the titles of each column of data
		file.getline(fieldVals,100);
		std::string fValues (fieldVals);
		//Seperates the string based on the delimiter (a comma) and inserts it into a vector
		size_t pos = 0;
		while((pos = fValues.find(delimeter)) != std::string::npos) {
			fieldNames.push_back(fValues.substr(0,pos) );
			fValues.erase(0, pos + delimeter.size());
		}
		//Removes the empty row of values.
		file.getline(valueTitles, 100);
		//Loops through the rest of the file line by line.
		//while(file.is_open()){
		int counter = 0;
		
		while(counter < 15){
			//Reads in and splits row based on the comma
			file.getline(rowValues, 100);
			std::string rVal(rowValues);
			while((pos = rVal.find(delimeter)) != std::string::npos) {
				dataValues.push_back(rVal.substr(0,pos));
				rVal.erase(0, pos + delimeter.size());
			}
			//Creates a new data point that will be set up with the values read in
			if(dataType.compare("nominal") == 0 ){
				dataPoint<std::string> newEntry(fieldNames.size());
				for(int i = 0; i < (int)dataValues.size(); i++){
					newEntry.setVal(dataValues[i], i);
				}
				//Adds created data point to the vector colletion object
				nominalData.push_back(newEntry);
				
			} else if (dataType.compare("numeric") == 0){
				dataPoint<double> newEntry(fieldNames.size());
				for(int i = 0; i < (int)dataValues.size(); i++){
					double v = atof(dataValues[i].c_str());
					newEntry.setVal(v, i);
				}
				//Adds created data point to the vector colletion object
				numericData.push_back(newEntry);
			}
			
			counter++;
		}
		while(file.peek()){
			//Reads in and splits row based on the comma
			file.getline(rowValues, 100);
			std::string rVal(rowValues);
			while((pos = rVal.find(delimeter)) != std::string::npos) {
				dataValues.push_back(rVal.substr(0,pos));
				rVal.erase(0, pos + delimeter.size());
			}
			//Creates a new data point that will be set up with the values read in
			if(dataType.compare("nominal") == 0){
				dataPoint<std::string> newEntry(fieldNames.size());
				for(int i = 0; i < (int)dataValues.size(); i++){
					newEntry.setVal(dataValues[i], i);
				}
				//Adds created data point to the vector colletion object
				nominalTesting.push_back(newEntry);
				
			} else if (dataType.compare("numeric") == 0) {
				dataPoint<double> newEntry(fieldNames.size());
				for(int i = 0; i < (int)dataValues.size(); i++){
					double v = atof(dataValues[i].c_str());
					newEntry.setVal(v, i);
				}
				//Adds created data point to the vector colletion object
				numericTesting.push_back(newEntry);
			}
		}


	}catch(std::exception e){
		std::cout << "File not found!";
	}
	
	if(dataType.compare("nominal") ){
		NomCluster<std::string> clusters(nominalData, numCentroids, fieldNames);
		clusters.findClusters();
		for(int i =0; i < (int)nominalTesting.size(); i++){
			dataPoint<std::string> answer = clusters.findAnswer(nominalTesting[i]);
			std::cout << "Found Answer" << answer.getAnswer() << std::endl;
			std::cout << "Expected Answer" << nominalTesting[i].getAnswer() << std::endl;
		}
		
	}else if (dataType.compare("numeric")){
		NumCluster<double> clusters(numericData, numCentroids, fieldNames);
		clusters.findClusters();
		for(int i =0; i < (int)numericTesting.size(); i++){
			dataPoint<double> answer = clusters.findAnswer(numericTesting[i]);
			std::cout << "Found Answer" << answer.getAnswer() << std::endl;
			std::cout << "Expected Answer" << numericTesting[i].getAnswer() << std::endl;
		}
	}
	
	
	
	
	
	

}//end main