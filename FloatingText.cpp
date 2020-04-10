#include"FloatingText.h"
#include"spritesAndStructs.h"
#include"pokemon.h"
#include<iostream>
using namespace std;
#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<string.h>

FloatingText::FloatingText(){
  pos.x=300;
  pos.y=200;
  Message="NA";
  DelayTimer=5;
  color.setRGBA(1,1,1,1);
  isDamage=false;
};

FloatingText::FloatingText(string s){
  pos.x=300;
  pos.y=200;
  Message=s;
  DelayTimer=5;
  color.setRGBA(.05, .31, .55,1);
  isDamage=false;
};

FloatingText::FloatingText(string s, Position p){
  pos=p;
  Message=s;
  DelayTimer=200;
  color.setRGBA(.63,.14,.13, 1);
  isDamage=true;
};

void FloatingText::DrawFText(){
  glColor4f(color.red, color.green, color.blue, color.alpha);
  glRasterPos2f(pos.x,pos.y);
  int length = (int)Message.length();
  for (int i = 0; i < length; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, Message[i]);
};
