#ifndef _TRAINER_
#define _TRAINER_
#include "spritesAndStructs.h"

class Trainer {
  unsigned int health;
  unsigned int money;
  Sprite sprite;
  Position pos;
  bool *DEX;

 public:
  Trainer(Node n, int h, int m);

  unsigned int getHealth() {return health;}
  unsigned int getMoney() {return money;}
  Position getPos() {return pos;}
  Sprite& getSprite() {return sprite;}

  void setHealth(int h) {health = h;}
  void setMoney(int m) {money = m;}

  void drawTrainer();
  bool IsSeen(ID i){return DEX[((int)i)-1];}
  void ChangeSeen(ID i){DEX[((int)i)-1]=true;}
};



#endif
