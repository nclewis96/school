/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 02 - Search
*	File - Town.h
********************************************/

#include <string>
#include <map>
#include <vector>

#ifndef TOWN_H
#define TOWN_H

class Town {

	public:
		Town();
		Town(std::string name, bool goal);
		void addConnection(std::string town, int distanceTo);
		void setSLD(int distance);
		bool isGoal();
		int  getSLD();
		int  getTownCost(std::string town);
		int  getNumConnect();
		std::map<std::string, int> getConnections();
		int getTravelCost(std::string town);
		std::vector<std::string> getConnectedTowns();
		std::string getName();	
		
	private:
		std::map<std::string, int > connectedTo;
		std::vector<std::string> connectedTowns;
		int sld;
		bool goalTown;
		std::string townName;
		
	};//end Town
	
#endif