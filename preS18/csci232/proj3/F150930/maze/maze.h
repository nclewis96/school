#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cassert>
#include "creature.h"  //struct Position defined here

class Maze {
  // Associations
  // Attributes
  private:
    std::string * mazeArray;
    int rows;
    int cols;
    int exit_row;
    int exit_col;
    int start_row;
    int start_col;
  // Operations
  public:
    Maze ( int width = 10, int height = 10 );
    Maze ( std::ifstream  & fin );
    ~Maze();
    void display (  );
    bool isWall ( int row, int col );
    bool isClear ( int row, int col );
    bool isExit(Position p);
    Position getEntrance();
    void markPath(Position p);
    void markVisited (Position p );
};

#endif
