/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 02 - Search
*	File - AStar.h
********************************************/

#include "GenericSearch.h"
#include "Town.h"
#include <map>
#include <string>
#ifndef A_STAR_H
#define A_STAR_H

class AStar : public GenericSearch {
	public:
	AStar(std::map<std::string, Town> map, std::string startingTown);
	Town strategy(std::map<std::string, Town> newMap, std::stack<std::string> newFringe, std::stack<std::string> newPath);

};

#endif 