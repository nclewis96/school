#include "creature.h"

Creature::Creature ( int r, int c){
    pos.row=r;
    pos.col=c;
}

void Creature::setStart(Position p){
    pos.row=p.row;
    pos.col=p.col;
}

Position Creature::getPos(){
    return pos;
}

int Creature::getRow(){
    return pos.row;
}

int Creature::getCol(){
    return pos.col;
}

void Creature::moveN (){
    pos.row--;
}

void Creature::moveE (){
    pos.col++;
}

void Creature::moveS (){
    pos.row++;
}

void Creature::moveW (){
    pos.col--;
}

