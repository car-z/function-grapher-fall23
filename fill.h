
#ifndef FILL_H
#define FILL_H

#include <string>
#include "image.h"
#include "bounds.h"
#include "func.h"
//enum representing the three types of fills allowed
enum fill_type{ABOVE,BELOW,BETWEEN};

class Fill {
private:
  fill_type type;
  float opacity;
  Color* color;
  Function* func1;
  Function* func2;

public:
  //non-default constructor which has a default value for func2 pointing to nullptr
Fill(fill_type type, float opacity, Color* color, Function* func1, Function* func2 = nullptr) : type(type), opacity(opacity), color(color),func1(func1), func2(func2){}

  ~Fill();

  //method to perform the fill operation, filling in the pixels as according to which type of directive this fill is.
  //Takes a pointer to the array of pixels and a pointer to the bounds of the plot as parameters
  void fill_color(Color* img_pixels, Bounds* bounds) const;

};

#endif // FILL_H
