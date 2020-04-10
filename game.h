#ifndef _GAME_
#define _GAME_
#include "texture.h"
#include "minion.h"
#include "tower.h"
#include "wave.h"
#include "menu.h"
#include "defeat.h"
#include "victory.h"
#include "button.h"
#include "FloatingText.h"

extern int STATE, WIDTH, HEIGHT;
extern Button pause;

bool mouseIsDragging = false;
double startTime;
int PLAY;
int wavenum = 0;
int mapT;
int mX=0, mY=0;
int counter = 0, t = 0, animcount = 0, towerTime = 0, waveCounter=0;
Sprite bIcon, CharIcon, KhanIcon, JiggIcon, RapidIcon;
int bIconT, CharIconT, KhanIconT, JiggIconT, RapidIconT, RattIconT, TaurIconT;

Position trainer(576, 160);
Node trainerNode(trainer);
Trainer gary (trainerNode, 3, 150);
Tower* tNodep;

Position Startp(-30, 200), p1(80, 200), p2(80,80), p3(200,80), p4(200, 235), p5(360,235), p6(360,160), pt(575,160), ptt(576,160), pt3(577,160);
Position bPosArr[4]={Position(167,310), Position(132,310), Position(97,310), Position(62,310)};
Button tPallArr[4]={Button(bPosArr[0]),Button(bPosArr[1]),Button(bPosArr[2]),Button(bPosArr[3])};
Node nt2(pt3), ntt(ptt, nt2), nt(pt, ntt), n6(p6, nt), n5(p5, n6), n4(p4, n5), n3(p3, n4), n2(p2, n3), n1(p1, n2), Start(Startp, n1);
Position tPosArr[7]={Position(145,125),Position(250,125),Position(415,210), Position(145,200), Position(315,200), Position(250, 200), Position(360, 95)};
Button tButtArr[7]={Button(tPosArr[0]),Button(tPosArr[1]),Button(tPosArr[2]),Button(tPosArr[3]),Button(tPosArr[4]), Button(tPosArr[5]), Button(tPosArr[6])};
Node tNodeArr[7]={Node(tPosArr[0]),Node(tPosArr[1]),Node(tPosArr[2]),Node(tPosArr[3]),Node(tPosArr[4]), Node(tPosArr[5]), Node(tPosArr[6])};
Tower* tpArr[7];

Wave* currWave;
ifstream g("Wave1.txt");
Wave wave1(g, Start);

unsigned int getTValue(ID poke){
  switch(poke){
  case CHAR:
    return 75;
  case KANG:
    return 100;
  case JIGG:
    return 50;
  case RAPID:
    return 200;
  default:
    return 0;
   }
}

//**************************** DRAWING FUNCTIONS ******************************

//drawText draws text at location x,y; the text is a c-style string
void drawText(float x, float y, const char* text) {
  glRasterPos2f(x, y);
  int length = strlen(text);
  for (int i = 0; i < length; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

//drawNumber draws a number at location x,y
void drawNumber(double x, double y, double num) {
  stringstream oss;
  oss << num; oss.flush();
  drawText(x, y, oss.str().c_str());
}

//animate minions (switches sprite depending on direction and steps)
void animateMinion(Minion* m) {
  int spritecount = 0;
  if (m->getHealth() > 0) {
    if (m->getAxis() == NORTH) {
      if (animcount%2 != 0)
	spritecount++;
      if (spritecount%2 != 0)
	(m->getSprite()).tex=loadTexture(("./Sprites/"+m->getName()+"/N1.pam").c_str());
      else
	(m->getSprite()).tex=loadTexture(("./Sprites/"+m->getName()+"/N2.pam").c_str());
    }
    else if (m->getAxis() == EAST) {
      if (animcount%2 == 0)
	spritecount++;
      if (spritecount%2 != 0)
	(m->getSprite()).tex=loadTexture(("./Sprites/"+m->getName()+"/E1.pam").c_str());
      else
	(m->getSprite()).tex=loadTexture(("./Sprites/"+m->getName()+"/E2.pam").c_str());
    }
    else if (m->getAxis() == SOUTH) {
      if (animcount%2 == 0)
	spritecount++;
      if (spritecount%2 != 0)
	(m->getSprite()).tex=loadTexture(("./Sprites/"+m->getName()+"/S1.pam").c_str());
      else
	(m->getSprite()).tex=loadTexture(("./Sprites/"+m->getName()+"/S2.pam").c_str());
    }
    else if (m->getAxis() == WEST) {
      if (animcount%2 == 0)
	spritecount++;
      if (spritecount%2 != 0)
	(m->getSprite()).tex=loadTexture(("./Sprites/"+m->getName()+"/W1.pam").c_str());
      else
	(m->getSprite()).tex=loadTexture(("./Sprites/"+m->getName()+"/W2.pam").c_str());
    }
  }
}

// animates the towers, changing the direction as the pokemon walk by
void animateTower(Tower& t) {
  switch(t.getAxis()) {
  case NORTH:
    (t.getSprite()).tex=loadTexture(("./Sprites/"+t.getName()+"/N1.pam").c_str());
    break;

  case EAST:
    (t.getSprite()).tex=loadTexture(("./Sprites/"+t.getName()+"/E1.pam").c_str());
    break;

  case SOUTH:
    (t.getSprite()).tex=loadTexture(("./Sprites/"+t.getName()+"/S1.pam").c_str());
    break;

  case WEST:
    (t.getSprite()).tex=loadTexture(("./Sprites/"+t.getName()+"/W1.pam").c_str());
    break;
  }
}

/*checks to see if minions are dead or reach the end of the path, then stops drawing them*/
void animateWave(Wave& w, int time) {
  for(int i=0; i < w.getSize(); ++i){
    if (!w[i]->isDead()){
      if (w[i]->getHealth() > 0) {
	animateMinion(w[i]);
	if (w[i]->IsPathDone()){
	  w[i]->drawPokemon();
	}
	else{ 
	  if (!w[i]->isDead()){
	  gary.setHealth(gary.getHealth()-1);
	  w[i]->setDead(true);
	  }
	}
      }
    }
  }
}

//draws a rectangle
void drawBox(double x, double y, double w, double h) {
  glBegin(GL_POLYGON);
  glVertex2f(x,y); //upper left
  glVertex2f(x, y + h); //lower left
  glVertex2f(x + w, y + h); //lower right
  glVertex2f(x + w, y); //upper right
  glEnd();
}

void drawBox(double *pos) {
  drawBox(pos[0], pos[1], pos[2], pos[3]);
}

//****************************** DRAWING WINDOW ******************************

void gameDrawWindow() {
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  //load textures
  mapT = loadTexture("map.pam");
  CharIconT = loadTexture("./Sprites/Charmander/S1.pam");
  KhanIconT = loadTexture("./Sprites/Kangaskhan/S1.pam");
  JiggIconT = loadTexture("./Sprites/Jigglypuff/S1.pam");
  RapidIconT = loadTexture("./Sprites/Rapidash/S1.pam");
  bIconT = loadTexture("./Sprites/Charmander/S1.pam");
  RattIconT = loadTexture("./Sprites/Rattata/S1.pam");
  TaurIconT = loadTexture("./Sprites/Tauros/S1.pam");
  
  //draw map
  drawTexture(mapT,   0,0,   600,400); //texID, x,y, width,height

  //draw tower buttons
  for(int i=0; i<7; i++){
    if (tpArr[i]==0)
      tButtArr[i].drawButton();
    tPallArr[i].drawButton();
  }

  //draw start button
  if (PLAY == 0) {
    glColor3f(1,1,1);
    drawText(450, 330, "Start Game: ");
    pause.drawButton();
  }
  
  //draw clock
  glColor3f(1,1,1);
  drawText(480, 20, "Time:");
  if (counter < 59)
    drawNumber(570, 20, t);
  else {
    int min = t/60;
    int sub = t - (min*60);
    if (sub < 10) {
      drawNumber(553, 20, min);
      drawText(564, 20, ":");
      drawNumber(570, 20, 0);
      drawNumber(580, 20, sub);
    }
    else {
      drawNumber(553, 20, min);
      drawText(564, 20, ":");
      drawNumber(570, 20, sub);
    }
  }

  //draw money
  glColor3f(1,1,1);
  drawText(480, 40, "Money: ");
  drawNumber(553, 40, gary.getMoney());

  //draw hp
  glColor3f(1,1,1);
  drawText(480, 60, "HP: ");
  drawNumber(553, 60, gary.getHealth());

  //draw wave counter
  drawText(235, 20, "Wave ");
  if (wavenum <= wave1.getWavetotal())
    drawNumber(290, 20, wavenum);
  else
    drawNumber(290, 20, wave1.getWavetotal());
  drawText (318, 20, "of ");
  drawNumber(343, 20, wave1.getWavetotal());

  //draw tower icons
  for (int i=1; i<14; i++){
    if (gary.IsSeen((ID)i)){
	switch(ID(i)){
	case CHAR:
	  drawTexture(CharIconT, 168, 315, 25, 25, 1, 0);
	  break;
	case JIGG:
	  drawTexture(JiggIconT, 99, 315, 25, 25, 1, 0);
	  break;
	case KANG:
	  drawTexture(KhanIconT, 134, 315, 25, 25, 1, 0);
	  break;
	case RAPID:
	  drawTexture(RapidIconT, 67, 315, 25, 25, 1, 0);
	  break;
	default:
	  break;
	}
    }
  }
    
  //draw tower values under tower
  drawText (100, 305, "Towers");
  drawNumber(62, 360, getTValue(RAPID));
  drawNumber(102, 360, getTValue(JIGG));
  drawNumber(130, 360, getTValue(KANG));
  drawNumber(172, 360, getTValue(CHAR));

  //draw pokemon when placing towers
  for (int i=0; i<4; ++i)
    if (mouseIsDragging && tPallArr[i].IsPressed())
      drawTexture(tPallArr[i].getSprite().tex, tPallArr[i].getSprite().pos.x, tPallArr[i].getSprite().pos.y, tPallArr[i].getSprite().width,tPallArr[i].getSprite().height);
  
  //draw trainer
  (gary.getSprite()).tex=loadTexture("./Sprites/TrainerM1/W1.pam");
  gary.drawTrainer();

  //draw & animate minions
  animateWave(wave1, t);

  //draw & animate towers
  for (int i=0; i<7; i++){
    if (tpArr[i]!=0){
      tpArr[i]->drawPokemon();
      animateTower(*tpArr[i]);
    }
  }
  //tell gfx card to draw
  glutSwapBuffers();
}

//***************************** IDLE ************************************

//returns time in seconds
double getCurrentTime() {
  struct timeval tv = {0,0};
  struct timezone tz;
  gettimeofday(&tv, &tz);
  return tv.tv_sec + tv.tv_usec/(double)1000000.;
}

//idle is called when nothing else is happening
void idle() {
  if (PLAY == 1) {
    //when to change time? we want elapsed time to be same time as elapsed rdown
    double elapsedTime = getCurrentTime() - startTime;
    if (elapsedTime > t) {
      //enough time has passed, increase counter
      ++t;

      if (t%2==0)
	++wave1.waveTime;
      
      //allows counting of waves
      if (t >= wave1.getWavetimer(wavenum))
	++wavenum;
      
      //checks to see if you've lost the game
      if (gary.getHealth() <= 0){
	STATE = 2;
	PLAY = 0;
      }

      //checks to see if you've won the game
      if (wave1[wave1.getSize() - 1]->getHealth() <= 0){
	PLAY=0;
	STATE = 3;
      }
      else if ((!wave1[wave1.getSize() - 1]->IsPathDone()) && (gary.getHealth() > 0)){
	PLAY=0;
	STATE = 3;
      }
    }
    
    if (elapsedTime * 3 > animcount) {
      //enough time has passed, increase counter
      ++animcount;

      //updates tower if ready to attack new minion
      for (int i=0; i<7; ++i)
	if (tpArr[i]!=0) {
	  tpArr[i]->update(wave1, true);
	  if(tpArr[i]->getAttacked()){
	  }
	}
      
      /*checks to see if minion has died, giving you money and potentially unlocking a new tower*/
      for (int i = 0; i < wave1.getSize(); ++i) {
	if (wave1[i]->getHealth() <= 0){
	  if (!wave1[i]->isDead()) {
	    gary.setMoney(gary.getMoney() + (wave1[i]->getValue()));
	    wave1[i]->setDead(true);
	    gary.ChangeSeen(wave1[i]->getID());
	  }
	}
      }
    }
    
    if (elapsedTime * 30 > towerTime) {
      //enough time has passed, increase counter
      ++towerTime;

      //updates tower if not ready to attack a minion
      for (int i=0; i<7; ++i)
	if (tpArr[i]!=0)
	  tpArr[i]->update(wave1, false);
    }
    if (elapsedTime * 30 > waveCounter){
      //enough time has passed, increase counter

      //updates the wave
      ++waveCounter;
      wave1.update();
    }
    if (elapsedTime * 200 > counter) {
      //enough time has passed, increase counter

      //attacks minions
      ++counter;
      for (int i=0; i<7; i++){
	if (tpArr[i]!=0)
	  if (tpArr[i]->getAttack()!=0)
	    tpArr[i]->getAttack()->update();
      }
    }
    glutPostRedisplay();
  }
}

//**************************** KEYBOARD & MOUSE ***************************

//mouse function called when mouse button pressed down or released
void gameMouse(int button, int state, int x, int y) {
  if ( GLUT_LEFT_BUTTON == button) {
    if ( GLUT_DOWN == state) {
      mouseIsDragging = true;
      // the user just pressed down on the mouse, do something
      if (pause.checkOver(x,y)) {
	if (pause.getPlaypause() == 0) {
	  //starts the game when you press the start button
	  pause.setPress(true);
	  PLAY = 1;
	  startTime = getCurrentTime();
	  pause.setPlaypause(1);
	}
      }
      else
	pause.setPress(false);
	
      for (int i=0; i<4; ++i){
	//checks if you're clicking on an unlocked tower
	if (tPallArr[i].checkOver(x,y) && 
	    gary.IsSeen((ID)tPallArr[i].getSprite().id))
	  {
	    tPallArr[i].setPress(true);
	  }
	else
	  tPallArr[i].setPress(false);
      }
    }
    else {
      // the user let go of the mouse, do something
      mouseIsDragging = false;
      for (int i=0; i<7; ++i){
	for (int n=0; n<4; ++n){
	  //places a tower, subtracts money, etc.
	  if (tButtArr[i].IsOver() && 
	      tPallArr[n].IsPressed() && 
	      tpArr[i]==0 && 
	      (getTValue(tPallArr[n].getSprite().id)<=gary.getMoney()) && 
	      gary.IsSeen(tPallArr[n].getSprite().id))
	    {
	      gary.setMoney(gary.getMoney()-getTValue(tPallArr[n].getSprite().id));
	      tpArr[i]=new Tower (tNodeArr[i], tPallArr[n].getSprite().id);
	    }
	  //doesn't place tower if you don't have enough money
	  else if (tButtArr[i].IsOver() && 
		   tPallArr[n].IsPressed() && 
		   tpArr[i]==0 && 
		   getTValue(tPallArr[n].getSprite().id)>gary.getMoney())
	    {
	      cout << "not enough money for that tower\n";
	    }
	}
      }
	  
    }
    }
  
  else if ( GLUT_RIGHT_BUTTON == button) {
  }
  glutPostRedisplay();
}

/* mouse_motion function called when mouse is being dragged and gives current location of mouse */
void gameMouseMotion(int x, int y) {
  for (int i=0; i<4;i++)
    //creates the draggable tower
    if (tPallArr[i].IsPressed()){
      tPallArr[i].getSprite().pos.x=x-15;
      tPallArr[i].getSprite().pos.y=y-20;
    }
  
  for (int i=0; i<7; i++){
    if (tButtArr[i].checkOver(x,y))
      tButtArr[i].setOver(true);
    else
      tButtArr[i].setOver(false);
  }
  
  //mouse button is pressed and mouse is moving
  glutPostRedisplay();
}


//****************************** GAME INIT ********************************
void gameInit() {
  Sprite RattIcon,TaurIcon;
  CharIcon.tex=loadTexture("./Sprites/Charmander/S1.pam");
  KhanIcon.tex=loadTexture("./Sprites/Kangaskhan/S1.pam");
  JiggIcon.tex=loadTexture("./Sprites/Jigglypuff/S1.pam");
  RapidIcon.tex=loadTexture("./Sprites/Rapidash/S1.pam");
  bIcon.tex=loadTexture("./Sprites/Charmander/S1.pam");
  RattIcon.tex=loadTexture("./Sprites/Rattata/S1.pam");
  TaurIcon.tex=loadTexture("./Sprites/Tauros/S1.pam");
  CharIcon.id=CHAR;
  KhanIcon.id=KANG;
  JiggIcon.id=JIGG;
  RapidIcon.id=RAPID;
  RattIcon.id=RATT;
  TaurIcon.id=TAUR;
  tPallArr[0].getSprite()=CharIcon;
  tPallArr[1].getSprite()=KhanIcon;
  tPallArr[2].getSprite()=JiggIcon;
  tPallArr[3].getSprite()=RapidIcon;
  tPallArr[0].setFcolor(.6,.09,.17,.5);
  tPallArr[0].setTcolor(.6,.2,0,.5);
  tPallArr[1].setFcolor(.44,.26,.26,.5);
  tPallArr[1].setTcolor(.45,.29,.07,.5);
  tPallArr[2].setFcolor(.71,.19,.42,.5);
  tPallArr[2].setTcolor(.71,.31,.61,.5);
  tPallArr[3].setFcolor(.55,0,0,.5);
  tPallArr[3].setTcolor(.55,.28,.36,.5);
}

#endif
