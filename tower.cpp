#include "iostream"
using namespace std;
#include "tower.h"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <cmath>
#include "texture.h"
#include "wave.h"
#include "projectile.h"
#include "FloatingText.h"

Tower::Tower() : Pokemon(), damage(0), range(0), attackSpeed(0),
		 CurrentTarget(0), attacked(false) {}

Tower::Tower(Node n, ID i) : Pokemon (n, i), CurrentTarget(0), attacked(false){
  pos=n.pos;
  ftext=0;
  Attack=0;

  switch (i){
  case CHAR:
    name="Charmander";
    damage = 50;
    range = 200;
    attackSpeed = 30;
    value=75;
    break;
  case KANG:
    name = "Kangaskhan";
    damage=35;
    range=290;
    attackSpeed = 25;
    value=150;
    break;
  case JIGG:
    name = "Jigglypuff";
    damage=40;
    range=150;
    attackSpeed=30;
    value=50;
    break;
  case RAPID:
    name = "Rapidash";
    damage=100;
    range=140;
    attackSpeed=60;
    value=100;
    break;
  default:
    cout << "INVALID TOWER ID " << i << " " << name<< endl;
  }

  sprite.tex=loadTexture(("./Sprites/"+name+"/S1.pam").c_str());
  sprite.id=i;
};


void Tower::drawPokemon() {
  drawTexture(sprite.tex,pos.x, pos.y, 30, 30);
  if (Attack!=0)
    if (CurrentTarget!=0)
      Attack->drawProjectile();
  if (ftext!=0){
    ftext->DrawFText();
    if (ftext->IsDamage()){
      if (ftext->CheckTimer()%10==0){
	ftext->ChangePos(0,-1);
	ftext->ChangeColorAlpha(.05);
      }
    }
    --(*ftext);
    if (ftext->CheckTimer()<=0)
      ftext=0;
  }
};

/*acquires a target for the tower, changes the direction of the tower, and if the tower is ready, attacks a minion*/
void Tower::update(Wave& w, bool ready) {
  acquireTarget(w);
    
  if (CurrentTarget==0) {
    attacked = false;
    return;
  }

  else {
    if (abs(pos.x-(CurrentTarget->getPos()).x) >= abs(pos.y-(CurrentTarget->getPos()).y)){
      if (pos.x - (CurrentTarget->getPos()).x >= 0)
	axis = WEST;
      else 
	axis = EAST;
    }
    
    else{
      if (pos.y - (CurrentTarget->getPos()).y >= 0)
	axis = NORTH;
      else 
	axis = SOUTH;
    }
    
    if (ready ==true){
      if (Attack==0){
	Attack=new Projectile(pos, CurrentTarget);
      }
      if (Attack!=0){
	if (Attack->IsPathDone()){
	  if (ftext!=0)
	    ftext=0;
	  ftext=new FloatingText(to_string(damage), CurrentTarget->getPos());
	  attack();
	  Attack=0;
	  attacked = true;
	}
	else{
	  attacked=false;
	}
      }
      else attacked=false;
    }
    else attacked=false;
  }
};

//acquires a target for the tower (the closest minion in range)
void Tower::acquireTarget(Wave& w) {
  double inRange = range;
  Minion* closest = 0;
  for (int i = 0; i < w.getSize(); ++i) {
    double xrange = (pos.x - (w[i]->getPos()).x);
    double yrange = (pos.y - (w[i]->getPos()).y);
    if (w[i]->getHealth()>0){
      if ( abs(xrange) < inRange/2 && abs(yrange) < inRange/2)
	if (abs(xrange) + abs(yrange) < inRange) {
	  inRange = abs(xrange) + abs(yrange);
	  closest = w[i];
	}
	else
	  continue;
      else
	continue;
    }
    else 
      continue;
  }
  if(inRange == range)
    CurrentTarget = 0;
  
  else
    CurrentTarget = closest;
};

//attacks a minion
void Tower::attack() {
  CurrentTarget->setHealth (CurrentTarget->getHealth() - damage);
};
