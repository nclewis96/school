/** @file WDiGraph.cpp
 * @author Phillip J. Curtiss
 * @author Nathan Lewis
 * @version 1.0
 * @date 2016-01-22
*********************************************************/ 

#include "WDiGraph.h"

WDiGraph::WDiGraph(int n) : numOfVertices(n), numOfEdges(0)
{
  //Allocate 2D matrix to contain weighted graph
   
   /* assume new always succeeds */
   data = new int[numOfVertices*numOfVertices];
   matrix = new int*[numOfVertices];
   for (int i = 0; i < numOfVertices; ++i)
   {
         matrix[i] = &data[i * numOfVertices];
         for(int j = 0; j<numOfVertices; ++j)
         {
           matrix[i][j] = NOEDGE;
         }
   }
} //end constuctor     

WDiGraph::WDiGraph(const WDiGraph& graph) 
{
   numOfVertices = graph.getNumVertices();
   numOfEdges = graph.getNumEdges();
   
   data = new int[numOfVertices*numOfVertices];
   matrix = new int*[numOfVertices];
   for (int i = 0; i < numOfVertices; ++i)
   {
         matrix[i] = &data[i * numOfVertices];
         for(int j = 0; j<numOfVertices; ++j)
         {
           matrix[i][j] = graph.getEdgeWeight(i,j);
         }
   }
}

WDiGraph::~WDiGraph()
{
  delete data;
  delete matrix;
  data = nullptr;
  matrix = nullptr;
  
}

bool WDiGraph::edgeExists(int start, int end) const
     throw (VertexOutOfRangeException) 
{
  bool found = false;
  
  //Check if start and end are in range
  if(start < 0 || end < 0 || start >= numOfVertices || end >= numOfVertices){
    throw VertexOutOfRangeException("Invalid Vertex number");
  }
  if(matrix[start][end] != NOEDGE)
     found = true;
  
  return found;
}

int WDiGraph::getNumVertices() const
{
   return numOfVertices;
}  // end getNumVertices

int WDiGraph::getNumEdges() const
{
   return numOfEdges;
}  // end getNumEdges

int WDiGraph::getEdgeWeight(int start, int end) const
   throw (VertexOutOfRangeException)
{
  int weight = 0;
  if(start < 0 || end < 0 || start >= numOfVertices || end >= numOfVertices){
    throw VertexOutOfRangeException("Invalid Vertex number");
  }
  weight = matrix[start][end];
  
  return weight;
} // end getWeight


bool WDiGraph::add(int start, int end, int w)
  throw (VertexOutOfRangeException)
{
  if(start < 0 || end < 0 || start >= numOfVertices || end >= numOfVertices){
    throw VertexOutOfRangeException("Invalid Vertex number");
  }
  matrix[start][end] = w;
  numOfEdges++;
  
  return true;
}

bool WDiGraph::remove(int start, int end)
  throw (VertexOutOfRangeException)
{
  if(start < 0 || end < 0 || start >= numOfVertices || end >= numOfVertices){
    throw VertexOutOfRangeException("Invalid Vertex number");
  }
  matrix[start][end] = NOEDGE;
  numOfEdges--;

  return true;
}

WDiGraph& WDiGraph::operator=(const WDiGraph& rhs)
{
  delete data;
  delete matrix;
  WDiGraph * newGraph = new WDiGraph(rhs);
  
  return *newGraph;
}
  
