//Nathaniel Lewis

#include "maze.h"
#include "creature.h"

bool findExit(Maze &, Creature &);

int main(int argc, char *arv[])
{
  std::ifstream fin;
  std::string filename;

  if(argc == 2){
    filename = arv[1];
  }
  else {
    std::cout<<"Please enter the file name: ";
    std::cin >> filename;
  }
  fin.open(filename.c_str());

  while(!fin){
    std::cout << "Could not open " << filename <<std::endl;
    fin.clear();
    std::cout<<"Please enter the file name: ";
    std::cin >> filename;
    fin.open(filename.c_str());
  }

  if(fin){
    Maze myMaze(fin);
    Creature mouse;
    mouse.setStart(myMaze.getEntrance());
    std::cout<<mouse.getPos().row<<" " << mouse.getPos().col;
    myMaze.display();
    if(findExit(myMaze, mouse)){
        myMaze.display();
    }
    else{
        myMaze.display();
        std::cout<<"There is no solution" << std::endl;
    }
    fin.close();
  }
}

bool goNorth(Maze &m, Creature &c);
bool goSouth(Maze &m, Creature &c);
bool goWest(Maze &m, Creature &c);
bool goEast(Maze &m, Creature &c);

bool findExit(Maze &m, Creature &c)
{
    bool success;
    success=goNorth(m, c);
    if(!success) success=goSouth(m, c);
    if(!success) success=goWest(m, c);
    if(!success) success=goEast(m, c);
    return success;
}


//Checks N, if clear moves then calls N, then if impossible it calls W & E
//If all are impossible, it marks the spot and backtraces S
bool goNorth(Maze &m, Creature &c)
{
    bool success = false;
    Position pos=c.getPos();

    if( m.isClear(pos.row-1, pos.col)){
      c.moveN();
      m.markPath(c.getPos());
      if(m.isExit(c.getPos()))
        success=true;
      else{
        success = goNorth(m,c);
        if(!success){
          success = goWest(m,c);
          if(!success){
            success=goEast(m,c);
            if(!success){
              m.markVisited(c.getPos());
              c.moveS();
            }
          }
        }
      }
    }
    return success;
} 

//Checks S, if clear moves then calls S, then if impossible it calls W & E
//If all are impossible, it marks the spot and backtraces N
bool goSouth(Maze &m, Creature &c)
{
    bool success = false;
    Position pos=c.getPos();

    if( m.isClear(pos.row+1, pos.col)){
      c.moveS();
      m.markPath(c.getPos());
      if(m.isExit(c.getPos()))
        success=true;
      else{
        success = goSouth(m,c);
        if(!success){
          success = goEast(m,c);
          if(!success){
            success=goWest(m,c);
            if(!success){
              m.markVisited(c.getPos());
              c.moveN();
            }
          }
        }
      }
    }
    return success;
} 

//Checks E, if clear moves then calls E, then if impossible it calls N & S
//If all are impossible, it marks the spot and backtraces W
bool goEast(Maze &m, Creature &c)
{
    bool success = false;
    Position pos=c.getPos();

    if( m.isClear(pos.row, pos.col + 1)){
      c.moveE();
      m.markPath(c.getPos());
      if(m.isExit(c.getPos()))
        success=true;
      else{
        success = goEast(m,c);
        if(!success){
          success = goNorth(m,c);
          if(!success){
            success=goSouth(m,c);
            if(!success){
              m.markVisited(c.getPos());
              c.moveW();
            }
          }
        }
      }
    }
    return success;
} 

//Checks W, if clear moves then calls W, then if impossible it calls N & S
//If all are impossible, it marks the spot and backtraces E
bool goWest(Maze &m, Creature &c)
{
    bool success = false;
    Position pos=c.getPos();

    if( m.isClear(pos.row, pos.col - 1)){
      c.moveW();
      m.markPath(c.getPos());
      if(m.isExit(c.getPos()))
        success=true;
      else{
        success = goWest(m,c);
        if(!success){
          success = goSouth(m,c);
          if(!success){
            success=goNorth(m,c);
            if(!success){
              m.markVisited(c.getPos());
              c.moveE();
            }
          }
        }
      }
    }
    return success;
} 







