#include <iostream>
using namespace std;
#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "texture.h"
#include "trainer.h"

Trainer::Trainer(Node n, int h, int m) : health(h), money(m), sprite(), pos(n.pos) {
  DEX=new bool[14];
  for (int i=0; i<14; i++)
    DEX[i]=false;
  DEX[0]=true;
};

void Trainer::drawTrainer() {
  drawTexture(sprite.tex, pos.x, pos.y, sprite.width, sprite.height);
};
