#include "maze.h"

Maze::Maze ( int width, int height ){
    rows=height;
    cols=width;
    mazeArray = new std::string[rows];
}

Maze::~Maze(){
    delete [] mazeArray;
}

Maze::Maze ( std::ifstream & fin ){
    fin >> cols >> rows;
    fin >> exit_row >> exit_col;
    fin >> start_row >> start_col >> std::ws;
    assert(exit_row <= rows && exit_col <= cols);
    assert(start_row <= rows && start_col <= cols);
    mazeArray =  new std::string[rows];

    int r=0;
    std::string tmpStr;
    while(getline(fin, tmpStr)){
      assert(r<rows);
      mazeArray[r]=tmpStr;
	    assert((int)mazeArray[r].length() <= cols);
      r++;
    }
    assert(isClear(start_row, start_col));
    mazeArray[start_row][start_col]='o';
}

void Maze::display (  ){

    usleep(300000);
    system("clear");
    std::cout << std::endl;
    std::cout << "Entrance is at: " << start_row << ", " <<start_col<<std::endl;
    for(int r=0; r<rows;r++){
        std::cout << mazeArray[r];
        std::cout << std::endl;
    }
    std::cout << "Exit is at: " << exit_row << ", " <<exit_col<<std::endl;
    std::cout << std::endl;
}

bool Maze::isWall ( int row, int col ){

    return mazeArray[row][col] == 'x';
}

bool Maze::isClear ( int row, int col ){
    bool success=false;

    if(row > -1 && col > -1 && row < rows && col < cols){
        if(mazeArray[row][col] == ' ')
	    success=true;
    }
    return success;
}

Position Maze::getEntrance(){

    Position p;
    p.row=start_row;
    p.col=start_col;
    return p;
}

bool Maze::isExit(Position p) {
    return (p.row==exit_row && p.col==exit_col);
}

void Maze::markVisited ( Position p){

    assert(mazeArray[p.row][p.col] == 'o');
    mazeArray[p.row][p.col] = '.';
    display();
}

void Maze::markPath ( Position p){

    assert(mazeArray[p.row][p.col] == ' ');
    mazeArray[p.row][p.col] = 'o';
    display();
}
