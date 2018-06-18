/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 02 - Search
*	File - GenericSearch.h
********************************************/

#include <string>
#include <stack>
#include <map>
#include <vector>
#include "Town.h"

#ifndef GENERIC_SEARCH_H
#define GENERIC_SEARCH_H

class GenericSearch {

	public:
		GenericSearch(std::map<std::string, Town> map, std::string startingTown);
		virtual Town strategy(std::map<std::string, Town> newMap, std::stack<std::string> newFringe, std::stack<std::string> newPath) = 0;
		std::string search(std::string seaMethod);
		int pathCost(); // Calcs path cost to track
		std::vector<std::string> pathStrings(); // returns all towns in stack
		std::stack<std::string> getFringe();
		std::map<std::string, Town> getMap();
		std::stack<std::string> getPath();
		void setPath( std::stack<std::string> newPath);
		void setMap(std::map<std::string, Town> map);
		void setFringe(std::stack<std::string> newFringe);

			
	private:
	
		std::map<std::string, Town> roadMap;
		std::stack<std::string> fringe;
		std::stack<std::string> path;
		std::string start;
		std::vector<std::string> expanded;
		std::vector<std::string> visited;
		
	};//end GenericSearch
	
#endif