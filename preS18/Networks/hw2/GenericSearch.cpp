/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 02 - Search
*	File - GenericSearch.cpp
********************************************/
#include "GenericSearch.h"
#include "Town.h"
#include "AStar.h"
#include "DepthFirst.h"
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>


GenericSearch::GenericSearch(std::map<std::string, Town> map, std::string startingTown ){
	start.assign(startingTown);
	roadMap = map;
	fringe.push(start);
	path.push(start);
	visited.emplace(visited.begin(), start);

}//Constructor

std::string GenericSearch::search(std::string seaMethod){
	std::string prevCity, goalCity;
	Town nextTown;
	bool goalFound = false;
	int count;
	while(!goalFound && fringe.size() != 0){
		if(seaMethod.compare("AStar" )== 0){
			std::string newTown = fringe.top();
			AStar strat(roadMap, newTown );
			nextTown = strat.strategy(roadMap, fringe, path);
		}else if (seaMethod.compare("DFS") == 0){
			std::string newTown = fringe.top();
			DepthFirst strat(roadMap, newTown );
			nextTown = strat.strategy(roadMap, fringe, path);
		}//end if
			
		prevCity.assign(fringe.top() );
		fringe.pop();
		expanded.insert(expanded.begin(), prevCity);
		std::vector<std::string> connections = nextTown.getConnectedTowns();
		
		
		for(int i = 0; i < nextTown.getNumConnect(); i++){
			 bool inExpanded = false;
			 bool inVisited = false;
			 
			 
			 for(int j = 0; j < (int)expanded.size(); j++){
				if(connections[i].compare(expanded[j]) == 0){
					inExpanded = true;
				}
			 }
			 
			 for(int j = 0; j < (int)visited.size(); j++) {
				if(connections[i].compare(visited[j]) == 0){
					inVisited = true;
					count++;
				 }//if
			 }//for
			// bool addToPath = true;
			if( !inExpanded && !inVisited ) {
				fringe.push(connections[i] );
				visited.insert(visited.begin(), connections[i] );
			}
			if(count == (int)connections.size() ){
				path.pop();
			}
		
		}//end for
		std::stack<std::string> fringeCopy = fringe;
		
		if (!((int)connections.size() == 1 ) && (nextTown.getName().compare(start) != 0 ) ){
			path.push(nextTown.getName() );
		}
		if(nextTown.isGoal()){
			goalFound = true;
			goalCity = "Whitefish";
		}//end if
	}//end while
	return goalCity;
	

}

int GenericSearch::pathCost(){
	std::stack<std::string> fringeCopy = path;
	
	std::string townA;
	std::string townB;
	int pathCost = 0 ;
	int pathValue;
	
	while(fringeCopy.size() > 1){
		
		townA = fringeCopy.top();
		fringeCopy.pop();
		townB = fringeCopy.top();
		if(roadMap[townA].getTravelCost(townB) > 0 ){
			pathValue = roadMap[townA].getTravelCost(townB);
		} else if(roadMap[townB].getTravelCost(townA) > 0){
			pathValue = roadMap[townB].getTravelCost(townA);
		} else {
			pathValue = 0;
		}
		 
		pathCost = pathCost + pathValue;
	}
	
	return pathCost;
	
}

std::stack<std::string> GenericSearch::getFringe(){
	return fringe;
}

std::stack<std::string> GenericSearch::getPath(){
	return path;
}

std::vector<std::string> GenericSearch::pathStrings(){
	return expanded;
}

std::map<std::string, Town> GenericSearch::getMap(){
	return roadMap;
}

void GenericSearch::setPath(std::stack<std::string> newPath){
	while(!newPath.empty()){
		path.push(newPath.top() );
		newPath.pop();
	}
}

void GenericSearch::setMap(std::map<std::string, Town> map){
	roadMap = map;
}

void GenericSearch::setFringe(std::stack<std::string> newPath){
	path = newPath;
}