/** @file VertexOutOfRangeException.h
  */

#ifndef VERTEX_EXCEPTS_H
#define VERTEX_EXCEPTS_H

#include <stdexcept>
#include <string>

using namespace std;

/** Vertex Out of Range Exception class
  * Exception class for vertices that are not in the graph.
  */
class VertexOutOfRangeException: public std::out_of_range
{
public:
  /**
   * Creates exception initialized with a message.
   * @param message exception message string
   */
   VertexOutOfRangeException(const std::string & message = "")
                        : std::out_of_range(message.c_str())
   { }
}; // end VertexOutOfRangeException

#endif

