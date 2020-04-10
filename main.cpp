#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;
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
#include "minion.h"
#include "tower.h"
#include "wave.h"
#include "trainer.h"
#include "menu.h"
#include "game.h"
#include "defeat.h"
#include "victory.h"
#include "help.h"
#include "button.h"

int STATE = 0;
int WIDTH = 600;
int HEIGHT = 400;

Button newgame(Position(245, 230));
Button help(Position(245, 270));
Button mainmenu(Position(365, 170));
Button pause (Position(560, 310));

char programName[] = "Pokemon Mithril: Tower Defense";

void drawWindow() {
  //pick game screens
  switch(STATE) {
  case 0:
    menuDrawWindow();
    break;
  case 1:
    gameDrawWindow();
    break;
  case 2:
    defeatDrawWindow();
    break;
  case 3:
    victoryDrawWindow();
    break;
  case 4:
    helpDrawWindow();
    break;
  }

  //tell gfx card to draw
  glutSwapBuffers();
}

//process keyboard events
void keyboard( unsigned char c, int x, int y) {
  int win = glutGetWindow();
  switch(c) {
  case 'q':
  case 'Q':
  case 27:
    // get rid of the window
    glutDestroyWindow(win);
    exit(0);
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

//reshape handles when user changes window size
void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  WIDTH = w; HEIGHT = h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);
}

//mouse function called when mouse button pressed down or released
void mouse(int button, int state, int x, int y) {
  //mouse functions depending on game state
  switch(STATE) {
  case 0:
    menuMouse (button, state, x, y);
    break;
  case 1:
    gameMouse (button, state, x, y);
    break;
  case 2:
    defeatMouse (button, state, x, y);
    break;
  case 3:
    victoryMouse (button, state, x, y);
    break;
  case 4:
    helpMouse (button, state, x, y);
    break;
  }
  //

  glutPostRedisplay();
}

/* mouse_motion function called when mouse is being dragged and gives current location of mouse */
void mouse_motion(int x, int y) {
  //mouse motion functions depending on the game state
  switch(STATE) {
  case 0:
    menuMouseMotion (x, y);
    break;
  case 1:
    gameMouseMotion (x, y);
    break;
  case 2:
    defeatMouseMotion (x,y);
    break;
  case 3:
    victoryMouseMotion (x,y);
    break;
  case 4:
    helpMouseMotion (x,y);
    break;
  }
  //mouse button is pressed and mouse is moving
  glutPostRedisplay();
}
   

//init sets up gfx card to draw properly
void init(void) {
  //clear window to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  //set up coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);

  //allow blending
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  //welcome message
  cout << "Welcome to Pokemon Mithril: Tower Defense!" << endl;

  pause.setFcolor(.5,.5,.5,.5);
  pause.setTcolor(0,0,0,.5);

  newgame.setFcolor(.5, 0, 0, 1);
  newgame.setTcolor(.5, 0, 0, .5);

  help.setFcolor(.5, 0, 0, 1);
  help.setTcolor(.5, 0, 0, .5);

  mainmenu.setFcolor(1, 1, 1, 1);
  mainmenu.setTcolor(1, 1, 1, .5);

  gameInit();
}

//init_gl_window gets ball rolling
void init_gl_window() {
  char *argv[] = { programName };
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  glutInitWindowSize( WIDTH, HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(programName);
  init();

  glutDisplayFunc(drawWindow);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutIdleFunc(idle);
  glutMainLoop();
}

int main() {
  init_gl_window();

  return 0;
}
