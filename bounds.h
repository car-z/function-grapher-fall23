#ifndef BOUNDS_H
#define BOUNDS_H

class Bounds {
private:
  float xmin;
  float ymin;
  float xmax;
  float ymax;
  int width;
  int height;

public:
  //constructor
  Bounds(float xmin, float ymin, float xmax, float ymax, int width, int height);
  //destructor
  ~Bounds() {}

  //accessor functions
  int get_width() const {return width;}

  int get_height() const{return height;}

  float get_xmin() const{return xmin;}

  float get_ymin() const{return ymin;}

  float get_xmax() const{return xmax;}

  float get_ymax() const{return ymax;}
};

#endif // BOUNDS_H
