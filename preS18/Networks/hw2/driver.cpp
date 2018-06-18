/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 02 - Search
*	File - driver.cpp
********************************************/

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "Town.h"
#include "GenericSearch.h"
#include "AStar.h"
#include "DepthFirst.h"

int main(int argc, char* argv[]){
	std::map<std::string , Town> roadMap;
	std::string mapFile;
	std::string distFile;
	std::string destination = "Whitefish";
	std::string begin = "Jordan";
	int cost;
	std::stack<std::string> path;
	
	//if(argc > 2){
		mapFile = "Roads.txt";
		distFile = "SLD.txt";
	//}
	
	std::ifstream file(mapFile);
	std::string townA, townB;
	int distance;
	bool isGoal = false;
	while(file >> townA && file >> townB && file >> distance){
		if(std::distance(roadMap.begin(), roadMap.find(townA) ) != (int)roadMap.size()){
			roadMap[townA].addConnection(townB, distance);
		}else {
			isGoal = townA.compare(destination) == 0;
			Town newTown(townA, isGoal);
			roadMap.emplace(townA, newTown);
			roadMap[townA].addConnection(townB, distance);
		}//end if/else
		
		if(std::distance(roadMap.begin(), roadMap.find(townB) ) != (int)roadMap.size()){
			roadMap[townB].addConnection(townA, distance);
		}else {
			isGoal = townB.compare(destination) == 0;
			Town newTown(townB, isGoal);
			roadMap.emplace(townB, newTown);
			roadMap[townB].addConnection(townA, distance);
		}//end if/else
	
	}//end while - Read in state file
	file.close();
	std::ifstream file2(distFile);
	std::string sld;
	while(file2 >> townA && file2 >> sld){
		distance = std::atoi(sld.c_str());
		roadMap[townA].setSLD(distance);		
	}//end while - Read in SLD
	file2.close();
	std::string seaMethod;
	std::cout << "What algorithm would you like to use? DFS or AStar?" << std::endl;
	std::cin >> seaMethod;
	std::string goalString;
	if(seaMethod.compare("DFS") == 0 ){
		DepthFirst search(roadMap, begin);
		goalString = search.search(seaMethod);
		cost = search.pathCost();
		path = search.getPath();
	}else if(seaMethod.compare("AStar") == 0 ){
		AStar search(roadMap, begin);
		goalString = search.search(seaMethod);
		cost = search.pathCost();
		path = search.getPath();
	}else {
		std::cout << "Sorry, that's not an option." << std::endl;
	}
	
	std::cout << "Nodes visited with " << seaMethod << " : " << std::endl;
	while(!path.empty()){
		std::cout << path.top() << std::endl;
		path.pop();
	}
	std::cout << std::endl;
	std::cout << "Path cost : " << cost << std::endl;

}//main