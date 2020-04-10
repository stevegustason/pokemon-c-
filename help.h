#ifndef _HELP_
#define _HELP_
#include "button.h"
#include "game.h"

extern int STATE;
void drawBox(double, double, double, double);

extern Button mainmenu; //(245, 200);

int helpT;

//draws window menu
void helpDrawWindow()
{
  helpT = loadTexture("help.pam");
  drawTexture (helpT, 0,0, 600,400);

  //draws button
  mainmenu.drawButton();

  //adding button text
  glColor3f(0, 0, 0);
  drawText(400, 190, "<-Back to Main Menu!");
}

//The mouse function for this screen
void helpMouse(int button, int state, int x, int y)
{
  if (GLUT_LEFT_BUTTON == button) {
    if(GLUT_DOWN == state) {
      //checks if you're pressing the main menu button
      if(mainmenu.checkOver(x,y)) {
	mainmenu.setPress(true);
	STATE = 0;
      }
    else {
      mainmenu.setPress(false);
    }
    }
    else {
      if((mainmenu.IsOver()) && mainmenu.IsPressed()) {
	mainmenu.setPress(false);
      }
    }
  }
  else if (GLUT_RIGHT_BUTTON == button){}
}

//The mouse motion function for this screen
void helpMouseMotion(int x, int y)
{
  if(mainmenu.IsPressed()){}
  else
    {  
      if(mainmenu.checkOver(x,y))
	{  
	  mainmenu.setOver(true);
	}
      else 
	{  
	  mainmenu.setOver(false);
	}
    }
}

#endif
