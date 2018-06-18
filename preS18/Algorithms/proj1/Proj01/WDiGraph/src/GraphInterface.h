/** An interface for the ADT undirected, connected graph. 
 Carrano and Henry Code  Listing 20-1.
 @file GraphInterface.h */

#ifndef _GRAPH_INTERFACE
#define _GRAPH_INTERFACE
#include "VertexOutOfRangeException.h"
#include "NotFoundException.h"

const int NOEDGE = 0;

template<class LabelType>
class GraphInterface
{
public:
   /** Gets the number of vertices in this graph.
    @pre   None.
    @return  The number of vertices in the graph. */
   virtual int getNumVertices() const = 0;
   
   /** Gets the number of edges in this graph.
    @pre   None.
    @return  The number of edges in the graph. */
   virtual int getNumEdges() const = 0;
   
   /** Creates an undirected edge in this graph between two vertices
       that have the given labels. If such vertices do not exist, creates
       them and adds them to the graph before creating the edge.
    @param start  A label for the first vertex. 
    @param end  A label for the second vertex.
    @param edgeWeight  The integer weight of the edge.
    @throw VertexOutOfRangeException if either vertex is not in range.
    @return  True if the edge is created, or false otherwise. */
   virtual bool add(LabelType start, LabelType end, int edgeWeight) = 0;
   
   /** Removes an edge from this graph. If a vertex has no other edges, 
       it is removed from the graph since this is a connected graph. 
    @pre  None.
    @param start  A label for the first vertex.
    @param end  A label for the second vertex.
    @throw VertexOutOfRangeException if either vertex is not in range.
    @return  True if the edge is removed, or false otherwise. */
   virtual bool remove(LabelType start, LabelType end) = 0;

   /** Determine if edge is in graph
    @param start - edge start vertex
    @param end - edge end vertex
    @throw VertexOutOfRangeException if either vertex is not in range.
    @return true if edge (start, end) is in the graph */
   virtual bool edgeExists(LabelType start, LabelType end) const = 0;
                               
   /** Gets the weight of an edge in this graph.
    @throw VertexOutOfRangeException if either vertex is not in range.
    @return  The weight of the specified edge. 
       If no such edge exists, returns a negative integer. */
   virtual int getEdgeWeight(LabelType start, LabelType end) const = 0;
   
   /** Performs a depth-first search of this graph beginning at the given
       vertex and calls a given function once for each vertex visited.
    @param start  A label for the first vertex.
    @param visit  A client-defined function that performs an operation on
       or with each visited vertex. */
//   virtual void depthFirstTraversal(LabelType start, void visit(LabelType&)) = 0;

   /** Performs a breadth-first search of this graph beginning at the given
       vertex and calls a given function once for each vertex visited.
    @param start  A label for the first vertex.
    @param visit  A client-defined function that performs an operation on
       or with each visited vertex. */
//   virtual void breadthFirstTraversal(LabelType start, void visit(LabelType&)) = 0;
}; // end GraphInterface
#endif
