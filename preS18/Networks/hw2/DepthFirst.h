/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 02 - Search
*	File - DepthFirst.h
********************************************/

#include "Town.h"
#include "GenericSearch.h"
#ifndef DEPTH_FIRST_H
#define DEPTH_FIRST_H

class DepthFirst : public GenericSearch {
	public:
	DepthFirst(std::map<std::string, Town> map, std::string startingTown);
	Town strategy(std::map<std::string, Town> newMap, std::stack<std::string> newFringe, std::stack<std::string> newPath);

};

#endif 