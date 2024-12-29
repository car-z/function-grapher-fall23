
#include "func.h"
#include "bounds.h"

//non-default constructor which sets name and expression of function equal to parameters. Color of function is set as white by default.
Function::Function(const std::string &name, Expr *expr)
  : m_name(name)
  , m_expr(expr) {
    m_color = new Color(255,255,255);
}

Function::~Function() {
  //deallocates the dynamically allocated expression and color associated with this function
  if(m_expr){
    delete m_expr;
  }
  m_expr = nullptr;
  if(m_color){
    delete m_color;
  }
}

//member function to change the color associated with the function to the color passed in as the parameter
void Function::set_color(Color* newColor){
  //delete previously associated color 
  if(m_color){
    delete m_color;
  }
  //set the m_color member field of this function to newColor in the parameter
  m_color = newColor;
}

//member function to draw the function onto the image plot
void Function::draw(Color* img_pixels, Bounds* bounds) const{
  //iterating over the pixel columns of the image
  for(int j = 0; j < bounds->get_width(); j++){
    //calculate the x position with respect to the pixel column
    double x = bounds->get_xmin() + (j/(double) bounds->get_width()) * (bounds->get_xmax() - bounds->get_xmin());
    //if the calculated x is beyond the bounds of the image, jump to next pixel in image
    if(x > bounds->get_xmax() || x < bounds->get_xmin()){
      continue;
    }
    //calculate the y value of the function given x
    double y = m_expr->eval(x);
    //if calculated y is beyond bounds of image, jump to next pixel in image
    if(y > bounds->get_ymax() || y < bounds->get_ymin()){
      continue;
    }
    //calculate the pixel row that is associated with the calculated y
    int i = bounds->get_height() - 1 - floor(((y - bounds->get_ymin())/(bounds->get_ymax() - bounds->get_ymin()))*bounds->get_height());
    //check if pixel position (i,j) and the four pixels around it are within the bounds of the image - if it is, plot it
  if(i >= 0 && i < bounds->get_height()){
    img_pixels[i*bounds->get_width()+j] = *m_color;
  }
  if(i-1 >= 0){
    img_pixels[(i-1)*bounds->get_width() + j] = *m_color;
  }
  if(i+1 < bounds->get_height()){
    img_pixels[(i+1)*bounds->get_width()+j] = *m_color;
  }
  if(j-1 >= 0){
    img_pixels[i*bounds->get_width()+j-1] = *m_color;
  }
  if(j+1 < bounds->get_width()){
    img_pixels[i*bounds->get_width()+j+1] = *m_color;
  }
}
}
