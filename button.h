#ifndef _BUTTON_
#define _BUTTON_

struct Color{
  float red;
  float green;
  float blue;
  float alpha;
  void setRGB(float r, float g, float b){blue=b; green=g; red=r;}
  void setRGBA(float r, float g, float b, float a){blue=b, alpha=a; red=r; green=g;}
  Color(){red=0; green=0; blue=0; alpha=0;}
Color(float r, float b, float g, float a): red(r), green(g), blue(b), alpha(a) {}
};


class Button {
 protected:
  Position pos;
  int width;
  int height;
  bool playpause;
  bool ButtonIsPressed;
  bool overButton;
  Color Fcolor;
  Color Tcolor;
  Sprite icon;

 public:
  Button(){pos.x=0; pos.y=0; height=1; width=1; playpause=0;}
  Button(ifstream& is);
  Button(Position p);
  Sprite& getSprite() {return icon;}

  bool getPlaypause () {return playpause;}
  Position getPosition(){return pos;}
  int getWidth(){return width;}
  int getHeight(){return height;}

  void setPlaypause (bool b) {playpause = b;}
  void setPress(bool p) {ButtonIsPressed = p;}
  void setOver(bool p) {overButton=p;}
  void setFcolor(float r, float g, float b, float a){Fcolor.setRGBA(r,g,b,a);}
  void setTcolor(float r, float g, float b, float a){Tcolor.setRGBA(r,g,b,a);}

  bool checkOver(int x, int y);
  bool IsPressed(){return ButtonIsPressed;}
  bool IsOver(){return overButton;}
  void drawButton();
  void drawDrag();
  void clickDrag();
};


#endif //_BUTTON_
