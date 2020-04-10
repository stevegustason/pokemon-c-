#ifndef _MINION_
#define _MINION_
#include "pokemon.h"

class Minion : public Pokemon {
  int health;
  int speed;
  int stagger;
  int value;
  bool dead;

 public:
  Minion();
  Minion(ID i, Node start, int s);
  virtual ~Minion();

  int getHealth() {return health;}
  int getSpeed() {return speed;}
  int getStagger() {return stagger;}
  int getValue() {return value;}
  Position getPosition() {return pos;}
  bool getDead() {return dead;}

  void setPosition(Position p) {pos=p;}
  void setStagger(int s) {stagger = s;}
  void setHealth(int h) {health = h;}
  void setSpeed(int s) {speed = s;}
  void setDead(bool d) {dead = d;}

  bool isDead() {return dead;}
  void update(int time);
  void drawPokemon();
};

#endif
