#include <iostream>
using namespace std;
#include"texture.h"
#include "pokemon.h"

Pokemon::Pokemon() : pos(0,200), axis(EAST), target(0), id(RATT), value(0) {}

Pokemon::Pokemon(Node t, ID ID) : pos(t.pos), axis(SOUTH), id(ID), sprite() {
  switch(ID) {
  case CHAR:
    name="Charmander";
    break;
  case RATT:
    name="Rattata";
    break;
  case JIGG:
    name="Jigglypuff";
    break;
  case POLY:
    name="Poliwhirl";
    break;
  case RAPID:
    name="Rapidash";
    break;
  case KANG:
    name="Kangaskhan";
    break;
  case TAUR:
    name="Tauros";
    break;
  case GYAR:
    name="Gyarados";
    break;
  case ARB:
    name = "Arbok";
    break;
  case DIG:
    name = "Diglet";
    break;
  case HAUNT:
    name = "Haunter";
    break;
  case RHY:
    name = "Rhydon";
    break;
  case ZU:
    name = "Zubat";
    break;
  case SEA:
    name = "Seadra";
    break;
  default:
    cout << "INVALID ID" << endl;
  }
}
