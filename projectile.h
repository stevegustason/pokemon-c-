#ifndef _PROJ_
#define _PROJ_
#include "texture.h"
#include "pokemon.h"
#include "minion.h"

class Projectile{
 protected:
  Minion* target;
  Position pos;
  Position* targetPos;
  int width;
  int height;
  unsigned int sizeArray;
  unsigned int currentArrayPos;
  Sprite sprite;
  bool done;

 public:
  Projectile(Position start, Minion* m);

  Position GetPosition(){return pos;}

  bool IsPathDone(){return done;}
  bool getDone() {return done;}
  void drawProjectile();
  void update();
};

#endif
