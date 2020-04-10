#ifndef _SPRITE_
#define _SPRITE_

enum Direction  {NORTH=1, EAST, SOUTH, WEST};
enum ID  {CHAR=1, RATT, JIGG, POLY, RAPID, KANG, TAUR, GYAR, ARB, DIG, HAUNT, RHY, ZU, SEA};

struct Position {
  int x, y;
  Position(int a, int b) {x = a; y = b;}
  Position() {x = 0; y = 0;}
};

struct Sprite{
  int tex;
  int width;
  int height;
  ID id;
  Position pos;
  Sprite(){tex=1; width=30; height=30;}
  Sprite(int i){ cout << "here?\n"; tex=i; width=30; height=30;}
};


struct Node {
  Position pos;
  Node* next;
  Node(Position p) { pos=p; next=0;}
  Node(Position p, Node& n){ pos=p; next=&n;}
};



#endif
