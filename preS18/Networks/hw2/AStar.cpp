/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 02 - Search
*	File - AStar.cpp
********************************************/

#include "AStar.h"
#include "Town.h"
#include <string>
#include <stack>
#include <map>
#include <climits>
#include <iostream>

Town AStar::strategy(std::map<std::string, Town> newMap, std::stack<std::string> newFringe, std::stack<std::string> newPath){
	int distance;
	std::string nextTown;
	int shortestDistance = INT_MAX;
	setPath(newPath) ;
	while(!newFringe.empty()) {
		
		distance = newMap[newFringe.top()].getSLD();
		
		if(distance + pathCost() < shortestDistance){
			shortestDistance = distance + pathCost();
			nextTown = newFringe.top();

		}
		
		newFringe.pop();
		
	}
	
	
	
	return newMap[nextTown];
	
}

AStar::AStar(std::map<std::string, Town> map, std::string startingTown):
	GenericSearch(map, startingTown)
{
}

