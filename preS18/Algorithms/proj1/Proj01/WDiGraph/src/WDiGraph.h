/** @file WDiGraph.h
  * Weighted Digraph Class with adjacency list implementation
  *  Vertex indices range from 0 to numVertices-1
  *  Multiple edges from one vertex to another vertex are not allowed
  *
  * @author Phillip J. Curtiss
  * @version 0.95
  * @date 2016-01-22
  *********************************************************/

#ifndef WDGRAPH_H
#define WDGRAPH_H

#include "GraphInterface.h"

/** Weighted DiGraph - matrix implementation using integer vertex labels*/
class WDiGraph : public GraphInterface<int>
{
public:
   /** Default Constructor (default size is 10 vertices) 
     * @pre The graph is empty.
     * @post The graph is initialized to hold n vertices. */
   WDiGraph(int n=10);              

   /** Copy Constructor
     * @param graph - the graph to copy. */
   WDiGraph(const WDiGraph& graph); 

   /** Destructor. */
   virtual ~WDiGraph();

   /** Determines the number of vertices in the graph.
    * @return The number of vertices in the graph. */
   int getNumVertices() const;

   /** Determines the number of edges in the graph.
    * @return The number of edges in the graph. */
   int getNumEdges() const;

   bool add(int start, int end, int edgeweight)
      throw (VertexOutOfRangeException);

   bool remove(int start, int end)
      throw (VertexOutOfRangeException);

   bool edgeExists(int start, int end) const
      throw (VertexOutOfRangeException);
 
   int getEdgeWeight(int start, int end) const
      throw (VertexOutOfRangeException);

   /** Assignment operator overload for deep copy of rhs graph 
    * @pre The lhs and rhs graphs exist
    * @post The lhs graph is deallocated and now contains the rhs graph*/
   WDiGraph& operator=(const WDiGraph& rhs);

private:
   int* data;    /** Dynamicly allocated contiguous data block*/ 
   int* *matrix; /** 2D matrix that points to rows in data block*/
   int numOfVertices;  /** Number of vertices in the graph. */
   int numOfEdges;     /** Number of edges in the graph. */
}; //end WDiGraph

#endif

