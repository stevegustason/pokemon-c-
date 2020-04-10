#include<iostream>
using namespace std;
#include"projectile.h"
#include"pokemon.h"
#include <math.h>

double distance(int x, int y, Position p){
  double a=x-p.x;
  double b=y-p.y;
  return sqrt(a*a + b*b);
};

Projectile::Projectile(Position start, Minion* m): target(m), sprite(){
  targetPos=new Position(m->getPos());
  pos=start;
  pos.y+=10;
  pos.x+=10;
  width=20;
  height=20;
  done=false;
};

bool IsLeft(int x, int x2){
  if (x<x2)
    return true;
  else
    return false;
};

bool IsRight(int x, int x2){
  if (x>x2)
    return true;
  else
    return false;
};

bool IsUp(int y, int y2){
  if (y>y2)
    return true;
  else
    return false;
};

bool IsDown(int y, int y2){
  if (y<y2)
    return true;
  else
    return false;
};

void Projectile::drawProjectile(){
  if (!done){
    sprite.width=20;
    sprite.height=20;
    sprite.tex=(loadTexture("./Sprites/projectile/p1.pam"));
    drawTexture(sprite.tex,pos.x, pos.y, 10, 10);
  }
};

//changed position of the projectile
void Projectile::update(){
  for(int i=0; i<2 ; i++){
    targetPos=0;
    targetPos=new Position(target->getPos());
    targetPos->x+=10;
    targetPos->y+=10;
    if (IsLeft(pos.x,targetPos->x))
      pos.x+=1;
    else if (IsRight(pos.x,targetPos->x))
      pos.x-=1;
    if (IsUp(pos.y, targetPos->y))
      pos.y-=1;
    else if (IsDown(pos.y, targetPos->y))
      pos.y+=1;
  }
  if (abs(pos.x-(targetPos->x))<6 && abs((pos.y-(targetPos->y))<6)) {
    done=true;
    return;
  }
};
