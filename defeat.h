#ifndef _DEFEAT_
#define _DEFEAT_
#include "button.h"
#include "game.h"

extern int STATE;
void drawBox(double, double, double, double);
void drawText(float, float, const char *);

//extern Button newgame; //(245, 260);

//draws window menu
void defeatDrawWindow()
{
  //Draw text
  drawText(245, 50, "GAME OVER");
  drawText(240, 85, "You're terrible");
}

//The mouse function for this screen
void defeatMouse(int button, int state, int x, int y)
{

}

//The mouse motion function for this screen
void defeatMouseMotion(int x, int y)
{

}

#endif
