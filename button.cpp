#include<iostream>
#include<fstream>
using namespace std;
#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<math.h>
#include<stdlib.h>
#include "spritesAndStructs.h"
#include"pokemon.h"
#include"button.h"
#include"texture.h"
#include<string.h>

ID string2ID(string);
void drawBox(double x, double y, double width, double height);

Button::Button(ifstream& is){
  is >> pos.x >> pos.y >> width >> height;
  int r, g, b, r2, g2, b2;
  is >> r >> g >> b >> r2 >> g2 >> b2;
  Fcolor.setRGB(r,g,b);
  Tcolor.setRGB(r2,g2,b2);
  string s;
  is >> s;
  icon.tex=loadTexture(("./Sprites/"+s+"/S1.pam").c_str());
  ButtonIsPressed = false;
};

Button::Button(Position p): Fcolor(.1,.1,.1,.5), Tcolor(1,1,1,.5) {
  pos=p;
  width=30;
  height=30;
  ButtonIsPressed = false;
  playpause=0;
};

void Button::drawButton() {
  if(ButtonIsPressed)
    glColor4f(Tcolor.red, Tcolor.green, Tcolor.blue, Tcolor.alpha);

  else
    glColor4f(Fcolor.red, Fcolor.green, Fcolor.blue, Tcolor.alpha);

  drawBox(pos.x, pos.y, width, height);
};

bool Button::checkOver(int x, int y){
  if (x>pos.x && x<pos.x+width && y>pos.y && y<pos.y+height)
    return true;
  else
    return false;
};
  
