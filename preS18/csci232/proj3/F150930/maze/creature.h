#ifndef CREATURE_H
#define CREATURE_H

struct Position{
  int row;
  int col;
};

class Creature {
  // Associations
  // Attributes
  private:
    Position pos;
  // Operations
  public:
    Creature ( int r = 0, int c = 0 );
    void setStart(Position p);
    Position getPos();
    int getRow();
    int getCol();
    void moveN ();
    void moveE ();
    void moveW ();
    void moveS ();
};

#endif
