
#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <cassert>
#include <math.h>

//creating a class for Color objects
class Color {
  private:
    uint8_t r;
    uint8_t g;
    uint8_t b;

  public:
  //default constructor creates black pixel
  Color(int r = 0, int g = 0, int b = 0) : r(r),g(g),b(b){}

  //default destructor
  ~Color(){}

  // member functions for doing operations on Color values
  // could be helpful

  //member function to blend the new Color (passed in as parameter fill_color) with this and save the resulting color components into this
  void blend_colors(float opacity, const Color* fill_color){
    r = floor((1-opacity)*this->r + opacity*fill_color->r);
    g = floor((1-opacity)*this->g + opacity*fill_color->g);
    b = floor((1-opacity)*this->b + opacity*fill_color->b);
  }
};

#endif // COLOR_H
