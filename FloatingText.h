#ifndef _FTEXT_
#define _FTEXT_
#include<iostream>
using namespace std;
#include"spritesAndStructs.h"
#include"button.h"

class FloatingText{
 protected:
  Position pos;
  Color color;
  int DelayTimer;
  bool isDamage;
  string Message;

 public:
  FloatingText();
  FloatingText(string s);
  FloatingText(string s, Position p);

  void DrawFText();
  void ChangePos(int x,int y){pos.x+=x; pos.y+=y;}
  void ChangeColorAlpha(double a){color.alpha-=a;}
  void operator--(){DelayTimer--;}
  int CheckTimer(){return DelayTimer;}
  bool IsDamage(){return isDamage;}
};



#endif
