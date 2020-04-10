#include <iostream>
#include <fstream>
using namespace std;
#include "wave.h"
#include "pokemon.h"

Position start1(0, 125);
Node Start1(start1);

//changes a string to an id
ID string2ID(const std::string & s)
{
  static std::pair<const char*, ID> pairs[] = { {"CHAR", CHAR}, {"RATT", RATT}, {"JIGG", JIGG}, {"POLY", POLY}, {"RAPID", RAPID}, {"KANG", KANG}, {"TAUR", TAUR}, {"GYAR", GYAR}, {"ARB",ARB}, {"DIG",DIG}, {"HAUNT",HAUNT}, {"RHY",RHY}, {"ZU",ZU}, {"SEA",SEA}};
  for (unsigned int i = 0; i < sizeof pairs/sizeof pairs[0]; ++i)
    {
      if (s == pairs[i].first)
	return pairs[i].second;
    }
  return ID(777); // or any other value that doesn't represent a known ID
};

Wave::Wave(ifstream& is, Node& n) {
  done = false;
  is >> size;
  is >> wavetotal;
  for (int i = 0; i < wavetotal; ++i)
    is >> wavebreaks[i];
  waveTime=0;
  minions = new Minion*[size];
  for(int i=0; i<size; ++i) {
    ID poke;
    string s;
    int stag;
    is >> s >> stag;
    poke=string2ID(s);
    minions[i] = new Minion (poke, n, stag);
  }
};

Wave::~Wave() {
  for(int i=0; i<size; ++i) {
    if (minions[i]!=0)
    delete minions[i];
  }
  
  delete[] minions;
};

//updates wavetime
void Wave::update(){
  for(int i=0; i<(*this).getSize(); ++i) {
    if ((*this)[i]->getHealth() > 0) {
      if ((*this)[i]->IsPathDone()) {
	if ((*this)[i]->getStagger()<=waveTime)
	  (*this)[i]->update(waveTime);
      }
    }
  }
};
