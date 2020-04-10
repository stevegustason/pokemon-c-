#ifndef _TOWER_
#define _TOWER_
#include "pokemon.h"
#include "minion.h"
#include "wave.h"
#include "projectile.h"
#include "FloatingText.h"

class Tower : public Pokemon {
  int damage;
  int range;
  int attackSpeed;
  Minion* CurrentTarget;
  bool attacked;
  Projectile* Attack;
  FloatingText *ftext;

 public:
  Tower();
  Tower(Node n, ID i);

  FloatingText* getFtext() {return ftext;}
  Projectile* getAttack(){return Attack;}

  int getDamage() {return damage;}
  int getRange() {return range;}
  int getattackSpeed() {return attackSpeed;}
  Minion* getCurrentTarget() {return CurrentTarget;}
  bool getAttacked() {return attacked;}

  void acquireTarget(Wave& w);
  void attack();
  void drawPokemon();
  void update(Wave & w, bool ready);
};

#endif
