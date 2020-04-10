#ifndef _WAVE_
#define _WAVE_
#include <fstream>
#include "minion.h"
using namespace std;

class Wave{
  Minion** minions;
  int size;
  int wavetotal;
  int wavebreaks[50];
  bool done;

 public:
  Wave(ifstream& is, Node& n);
  ~Wave();

  int waveTime;

  int getWavetotal() {return wavetotal;}
  int getWavetimer(int i) {return wavebreaks[i];}
  int getSize() {return size;}
  bool getDone() {return done;}

  Minion* operator[](int i){return minions[i];}
  void update();
};

#endif
