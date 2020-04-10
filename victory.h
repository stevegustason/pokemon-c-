#ifndef _VICTORY_
#define _VICTORY_
#include "button.h"
#include "game.h"

extern int STATE;
void drawBox(double, double, double, double);
void drawText(float, float, const char *);

//draws window menu
void victoryDrawWindow()
{
  //draw text
  glColor3f(1., 1., 1.);
  drawText(265, 50, "Victory!");
  drawText(240, 85, "You're the best");
}

//The mouse function for this screen
void victoryMouse(int button, int state, int x, int y)
{

}

//The mouse motion function for this screen
void victoryMouseMotion(int x, int y)
{

}

#endif
