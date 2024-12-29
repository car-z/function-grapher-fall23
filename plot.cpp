
#include <cassert>
#include "plot.h"

//default constructor which sets bounds to nullptr and creates two empty vectors for all_functions and fill_directives
Plot::Plot(): bounds(nullptr), all_functions(), fill_directives(){
}

Plot::~Plot()
{
  // delete dynamically-allocated objects
  if(bounds != nullptr){
    delete bounds;
  }
  for(std::vector<Fill*>::iterator it = fill_directives.begin(); it != fill_directives.end(); ++it){
    delete *it;
  }
  for(std::vector<Function*>::iterator it = all_functions.begin(); it != all_functions.end(); ++it){
    delete *it;
  }
}


void Plot::add_bounds(Bounds* bounds){
  this->bounds = bounds;
}

void Plot::add_function(Function* f){
  all_functions.push_back(f);
}

Function* Plot::find_function(std::string name) const {
  Function* found = nullptr;
  //iterate through all_functions vector and see if any Function contains the name as specified by the parameter 
  for(std::vector<Function*>::const_iterator it = all_functions.cbegin(); it != all_functions.cend(); ++it){
    if(name == (*it)->get_name()){
      found = (*it);
      break;
    }
  }
  //returns pointer to the function with the name name if found, returns nullptr if not found
  return found;
}

void Plot::add_fill(Fill* new_fill){
  fill_directives.push_back(new_fill);
}

int Plot::get_width() const{
  return bounds->get_width();
}

int Plot::get_height() const{
  return bounds->get_height();
}

float Plot::get_xmin() const{
  return bounds->get_xmin();
}

float Plot::get_ymin() const{
  return bounds->get_ymin();
}

float Plot::get_xmax() const{
  return bounds->get_xmax();
}

float Plot::get_ymax() const{
  return bounds->get_ymax();
}

  
  
