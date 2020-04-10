#include <iostream>
using namespace std;
#include "minion.h"
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
#include "texture.h"

Node* Startnode;

Minion::Minion() : Pokemon(), health(0), speed(0), stagger(0), dead(true) {}

Minion::Minion(ID i, Node startPos, int s) : Pokemon(startPos, i), stagger(s), dead(false) {
  pos=startPos.pos;
  target=startPos.next;

  switch(i) {
  case JIGG:
    health = 250;
    speed = 1;
    value = 5;
    break;
  case KANG:
    health = 2500;
    speed = 1;
    value = 50;
    break;
  case GYAR:
    health = 4000;
    speed = 1;
    value = 50;
    break;
  case RHY:
    health = 5000;
    speed = 1;
    value = 50;
    break;
  case DIG:
    health = 300;
    speed = 2;
    value = 5;
    break;
  case SEA:
    health = 500;
    speed = 2;
    value = 10;
    break;
  case ARB:
    health = 800;
    speed = 2;
    value = 15;
    break;
  case HAUNT:
    health = 1000;
    speed = 2;
    value = 15;
    break;
  case RATT:
    health = 150;
    speed = 3;
    value = 15;
    break;
  case RAPID:
    health = 500;
    speed = 4;
    value = 25;
    break;
  case ZU:
    health = 125;
    speed = 5;
    value = 10;
    break;
  case TAUR:
    health = 850;
    speed = 5;
    value = 30;
    break;
  default:
    cout << "INVALID ID" << endl;
  }
};

void Minion::drawPokemon(){
  drawTexture(sprite.tex,pos.x, pos.y, sprite.width, sprite.height);   
};

Minion::~Minion(){}

void Minion::update(int time){
  if (getStagger() <= time) {
    switch (axis) {
    case NORTH:
      if (pos.y > target->pos.y)
	pos.y = pos.y - (speed);
      else if (pos.y <= target->pos.y) {
	if (pos.x < target->next->pos.x)
	  axis = EAST;
      else
	axis = WEST;
	target = target->next;
      }
      break;
    case EAST:
      if (pos.x < target->pos.x)
	pos.x = pos.x + (speed);
      else if (pos.x >= target->pos.x) {
	if (pos.y < target->next->pos.y)
	  axis = SOUTH;
	else
	  axis = NORTH;
	target = target->next;
      }
      break;
    case SOUTH:
      if (pos.y < target->pos.y)
	pos.y = pos.y + (speed);
      else if (pos.y >= target->pos.y) {
	if (pos.x < target->next->pos.x)
	  axis = EAST;
	else
	  axis = WEST;
	target = target->next;
      }
      break;
    case WEST:
      if (pos.x > target->pos.x)
	pos.x = pos.x - (speed);
      else if (pos.x <= target->pos.x) {
	if (pos.y < target->next->pos.y)
	  axis = SOUTH;
	else
	  axis = NORTH;
	target = target->next;
      }
      break;
    }
  }
};
