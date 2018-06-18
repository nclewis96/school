/** @file Driver.cpp
 *  Graph Driver - use to test Graph class methods and
 *   any functions independent of the Graph class.
 *
 * @author  Jeff Braun
 * @author  Nathan Lewis
 * @version 1.0
 * @date 1/12/15
 **********************************************************/

//-----------------------
// C++ includes
//-----------------------
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

//-----------------------
// Application includes
//-----------------------
#include "WDiGraph.h"
#include "io_functions.h"


//----------------------
// Functions Prototypes
//----------------------
void displayGraph(WDiGraph* graph);        //displays graph   
void processOption(char&, WDiGraph*);      //processes menu input option

/** Graph Driver - use to test graph class methods and
 *  functions that are independent from the graph class.
 **********************************************************/
int main()
{
  string restoreGraphFlg;     // holds response to restore graph from a file
  string menuOption;          // holds menu option input from user
  int nVertices;              // holds graph size
  WDiGraph* aGraph;           // Pointer to a graph 

//Opening Message
  cout<< "Graph Driver - Tests the graph class" << endl;

//Restore the graph from a file
  cout<< "----------------------------------" << endl;
  cout<< "Would you like to restore the graph from a file? (Y/N) ";

//Read user input - use a string to accept all inputs
  getline(cin, restoreGraphFlg);
  if(restoreGraphFlg[0] == 'Y' || restoreGraphFlg[0] == 'y')
  {
    string filename;
    cout << "Filename?";
    getline(cin, filename);
    
    ifstream file(filename);
    WDiGraph* newGraph;
    //If file exists
    if(file.is_open() ) {
    	int number;
    	file >> number;
    	
    	newGraph = new WDiGraph(number);
    	
    	int start, end, weight;
    	while(file >> start) {
    	file >> end;
    	file >> weight;
    	newGraph -> add(start, end, weight);
    	}
    	
    }
    else {
        cout << "File not Found";
    }
    aGraph = newGraph;
    file.close();
  }
  else //Prompt user for graph size and create graph
  {
    cout<< "How many vertices in the graph? ";
    nVertices = getInt();
    aGraph = new WDiGraph(nVertices);    //Creates aGraph to user defined size
  }

//Menu driven part of main program
//Initial menu display and loop to process menu option
  printMenu();
  do {
    cout << "\nEnter menu selection (0 for menu): ";
    getline(cin, menuOption);    //Use a string in case user enters chars
    processOption(menuOption[0], aGraph);
  }while(menuOption[0] != '7');

  delete aGraph;
  return 0;
} // end main()


//---------------------------
// Local function definitions
//---------------------------

/**
 * Displays the graph as adjacency lists
 * @param[in] graph Graph to display
 * @remarks If graph is empty, prints empty graph message.
 */
void displayGraph(WDiGraph* graph)
{
  if(graph->getNumEdges() == 0)
  {
    cout << "Graph is empty" << endl;
  }
  else
  { 
    for(int i = 0; i < graph->getNumEdges(); i++) {
        cout << i << " : -> ";
        for(int j = 0; i < graph->getNumEdges(); j++) {
          if(graph->edgeExists(i, j))
           cout << "[" << j << "|" << graph->getEdgeWeight(i,j) << "] ";
        }
    cout << endl;
    }
  }
} // end displayGraph

/**
  * Process input menu option character from user.
  * @param[in] menuChar menu option character
  * @param[in,out] aGraph The graph to be modified
  */
void processOption(char &menuChar, WDiGraph* aGraph)
{
  string saveGraphFlg;
  int start, end, w;

  switch (menuChar)
  {
    case '0':                     // Display menu options
      printMenu();
      break;
    case '1':                     // Output graph size
      cout << "\nGraph contains " << aGraph->getNumVertices() 
           << " vertices and " << aGraph->getNumEdges() << " edges" << endl;
      break;
    case '2':                     //Check if edge is in graph
      cout << "Enter starting vertex> ";
      start = getInt();
      cout << "Enter ending vertex> ";
      end = getInt();
      try
      {
        cout << "Edge (" << start << "," << end << ") is ";
        if(aGraph->edgeExists(start, end)){
          cout << "in graph" << endl;
        }
        else {
          cout << "not in graph" << endl;
        }
      }
      catch (VertexOutOfRangeException e)
      { //print error message to user
        cout << "out of range." << endl;
        cout << e.what() << endl;
      }
      break;

	case '3': 					  //Insert an edge
	cout << "Enter starting vertex> ";
	start = getInt();
	cout << "Enter ending vertex> ";
	end = getInt();
	cout << "Enter weight of the edge> ";
	w = getInt();
	try
	{
	  cout << "Edge (" << start << "," << end << ") with weight " << w << " has ";
	  if(aGraph->add(start, end, w) ) {
	     cout << "been added." << endl;
	  }
	  else {
	     cout << "not been added." << endl;
	  }
	
	}
	  catch (VertexOutOfRangeException e)
      { //print error message to user
          cout << "out of range." << endl;
          cout << e.what() << endl;
      }
	  break;
	  
	case '4':					  //Delete an edge
	cout << "Enter starting vertex> ";
	start = getInt();
	cout << "Enter ending vertex> ";
	end = getInt();
	
	try
	{
	  cout << "Edge (" << start << "," << end << ")  has ";
	  if(aGraph->remove(start, end) ) {
	     cout << "been deleted." << endl;
	  }
	  else {
	     cout << "not been deleted." << endl;
	  }
	
	}
	  catch (VertexOutOfRangeException e)
      { //print error message to user
          cout << "out of range." << endl;
          cout << e.what() << endl;
      }
	  break;
	  
	case '5':					  //Retrieve an edge weight
	cout << "Enter starting vertex> ";
	start = getInt();
	cout << "Enter ending vertex> ";
	end = getInt();
	
	try
	{
	  cout << "Edge (" << start << "," << end << ")  has a weight of  ";
	  cout << aGraph->getEdgeWeight(start,end);
	
	}
	  catch (VertexOutOfRangeException e)
      { //print error message to user
          cout << "out of range." << endl;
          cout << e.what() << endl;
      }
	  break;

    case '6':                     //Display Graph 
      displayGraph(aGraph);
      break;
    case '7':                     // Exit program
      cout << "Would you like to save the graph to a file? ";
      getline(cin, saveGraphFlg);
      break;
    default:                      // Invalid menu option entered
      cout << "\nError!  Invalid option.  Please try again.\n\n";
      printMenu();
    }
}// end processOption()

