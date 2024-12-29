
#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include "exception.h"
#include "renderer.h"
#include "plot.h"
#include "fill.h"

//#define DEBUG_FILL
//#define DEBUG_PLOT

Renderer::Renderer(const Plot &plot)
  : m_plot(plot)
  , m_img(nullptr) {
}

Renderer::~Renderer() {
  // Note: the Renderer object does not "own" the Image object,
  // since the render() member function transfers ownership of
  // the Image object to the caller (in the main function)
}

Image *Renderer::render() {
  int width = m_plot.get_width();
  int height = m_plot.get_height();

  // the unique_ptr will take care of deleting the Image object
  // if an exception is thrown
  std::unique_ptr<Image> img(new Image(width, height));
  m_img = img.get();

  Color* img_pixels = m_img->get_pixels();
  Bounds* bounds = m_plot.get_bounds();

  //SET ALL PIXELS TO BLACK INITIALLY
  Color black(0,0,0);
  for(int i = 0; i < width*height; i++){
    img_pixels[i] = black;
  }


  //iterates over the fill commands stored in m_plot object; each fill command calls the fills_color function
 
  std::vector<Fill*> fill_directives = m_plot.get_fills();
  for(std::vector<Fill*>::const_iterator it = fill_directives.cbegin(); it != fill_directives.cend(); ++it){
    (*it)->fill_color(img_pixels, bounds);
  }

  //iterate over function directives stored in m_plot object, call draw command on each function
  std::vector<Function*> all_functions = m_plot.get_functions();
  for(std::vector<Function*>::const_iterator it = all_functions.cbegin(); it != all_functions.cend(); ++it){
    (*it)->draw(img_pixels,bounds);
  }
  
  return img.release();
}
