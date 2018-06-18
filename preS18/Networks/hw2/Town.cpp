/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 02 - Search
*	File - Town.cpp
********************************************/

#include <map>
#include "Town.h"
#include <iostream>
#include <vector>


//constructor
Town::Town(){}
//
Town::Town(std::string name, bool goal){
	townName = name;
	goalTown = goal; 
}//end Town

//Adds a connection between the current town and another
void Town::addConnection(std::string town, int distanceTo){
	connectedTowns.emplace_back(town);
	connectedTo.emplace(town, distanceTo);
}//end addConnections

//Sets the straight line distance from the current town to the goal town
void Town::setSLD(int distance){
	sld = distance;
}//end setSLD
	
//returns whether or not this is the goal town
bool Town::isGoal(){
	return goalTown;
}//end isGoal

//returns the distance from the current town directly to the goal
int Town::getSLD(){
	return sld;
}//end getSLD

int Town::getNumConnect(){
	return (int)connectedTo.size();
}

std::map<std::string, int> Town::getConnections(){
	return connectedTo;
}//Return map

//Looks up the travel cost from this town to the town requested
//If it's not connected, return 0
int Town::getTravelCost(std::string town){
	if(std::distance(connectedTo.begin(), connectedTo.find(town) ) < (int)connectedTo.size())
		return connectedTo[town];
	return 0;
}//end getTravelCost

std::vector<std::string> Town::getConnectedTowns(){
	return connectedTowns;
}

std::string Town::getName(){
	return townName;
}

/*
int main (){
	std::string Colstrip = "Colstrip";
	std::string Forsyth = "Forsyth";
	Town test(Colstrip, false);
	test.addConnection(Forsyth, 32);
	test.setSLD(100);
	int cost = test.getTravelCost(Forsyth);
	std::cout << test.isGoal() << std::endl;
	std::cout << test.getSLD() << std::endl;
	std::cout << cost << std::endl;
	std::cout << test.getNumConnect() << std::endl;
	
}*/


// town