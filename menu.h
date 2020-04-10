#ifndef _MENU_
#define _MENU_
#include "button.h"
#include "game.h"

extern int STATE;
void drawBox(double, double, double, double);

extern Button newgame; //(245, 260);
extern Button help; //(245, 300);

int menuT;

//draws window menu
void menuDrawWindow()
{
  //load & draw map
  menuT = loadTexture("pokemon.pam");
  drawTexture (menuT, 0,0, 600,400);

  //draw buttons
  glColor3f(.5, 1., 1.);
  newgame.drawButton();
  help.drawButton();

  //adding text
  glColor3f(1., 1., 1.);

  //Draw title
  drawText(245, 85, "Pokemon Mithril:");
  drawText(247, 120, "Tower Defense");

  //Draws words over button
  drawText(283, 252, "New Game");
  drawText(283, 293, "Help");
}

//The mouse function for this screen
void menuMouse(int button, int state, int x, int y)
{
  //checks if either button is being pressed
  if (GLUT_LEFT_BUTTON == button) {
    if(GLUT_DOWN == state) {
      if(newgame.checkOver(x,y)) {
	newgame.setPress(true);
	//changes to game screen
	STATE = 1;
      }
      else {
	newgame.setPress(false);
      }
      if(help.checkOver(x,y)) {
	help.setPress(true);
	//changes to help screen
	STATE = 4;
      }
      else {
	help.setPress(false);
      }
    }
    else {
      if((newgame.IsOver()) && newgame.IsPressed()) {
	newgame.setPress(false);
      }
      else if ((help.IsOver()) && help.IsPressed()) {
	help.setPress(false);
      }
    }
  }
  else if (GLUT_RIGHT_BUTTON == button){}
}

//The mouse motion function for this screen
void menuMouseMotion(int x, int y)
{
  if(newgame.IsPressed()){}
  else
    {  
      if(newgame.checkOver(x,y))
	{  
	  newgame.setOver(true);
	}
      else 
	{  
	  newgame.setOver(false);
	}
    }
  if(help.IsPressed()){}
  else
    {  
      if(help.checkOver(x,y))
	{  
	  help.setOver(true);
	}
      else 
	{  
	  help.setOver(false);
	}
    }
}

#endif
