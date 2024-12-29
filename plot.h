
#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <map>
#include <string>
#include "bounds.h"
#include "image.h"
#include "func.h"
#include "fill.h"

using std::vector;
using std::map;
using std::string;

class Plot {
private:
  Bounds* bounds; //pointer to Bounds object which holds the bounds of the plot
  std::vector<Function*> all_functions; //vector to hold all functions to be graphed on this plot
  std::vector<Fill*> fill_directives; //vector to hold all fill directives to be performed on this plot

  // value semantics are prohibited
  Plot(const Plot &);
  Plot &operator=(const Plot &);

public:
  Plot();
  ~Plot();


  //member function to set the bounds of the plot
  void add_bounds(Bounds* bounds);

  //member function to add f (parameter) to the all_functions vector
  void add_function(Function* f);

  //member function to return the pointer to a Function object in this plot which has the name passed in as the parameter. If not found, returns nullptr 
  Function* find_function(std::string name) const;

  //member function to add new_fill (parameter) to fill_directives vector
  void add_fill(Fill* new_fill);

  //accessor functions to access values held within the bounds object which is pointed to within plot
  int get_width() const;

  int get_height() const;

  float get_xmin() const;

  float get_ymin() const;

  float get_xmax() const;

  float get_ymax() const;


  //accessor functions to access private instance variables of this plot
  std::vector<Fill*> get_fills() const {return fill_directives;}
  
  Bounds* get_bounds() const {return bounds;}

  std::vector<Function*> get_functions() const {return all_functions;}
};

#endif // PLOT_H
