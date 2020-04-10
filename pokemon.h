#ifndef _POKEMON_
#define _POKEMON_
#include "spritesAndStructs.h"

class Pokemon {
 protected:
  string name;
  Position pos;
  Direction axis;
  Node* target;
  ID id;
  Sprite sprite;
  int value;

 public:
  Pokemon();
  Pokemon(Node t, ID i);

  Sprite& getSprite(){return sprite;}
  Position getPos() {return pos;}
  int getValue() {return value;}
  string getName(){return name;}
  Direction getAxis() {return axis;}
  ID getID(){return id;}

  void setName(const string& st) {name = st;}
  void setPosition(const Position p) {pos = p;}
  void setAxis(const Direction d) {axis = d;}
  void setTarget(const Node& node) {target = node.next;}
  void setID(const unsigned int i) {id = (ID)i;}
  void setSize(int x, int y) {sprite.width=x; sprite.height=y;}

  //checks if pokemon has reached the last node
  bool IsPathDone(){
    if (target->next!=0)
      return true;
    else
      return false;
  }
  void displayPos(){cout << pos.x << " " << pos.y << endl;}
  virtual void drawPokemon() =0;
};

#endif
