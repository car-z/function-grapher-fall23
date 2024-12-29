
#ifndef FUNC_H
#define FUNC_H

#include <string>
#include "expr.h"
#include "color.h"
#include "bounds.h"
#include "image.h"
#include <deque>

class Function {
private:
  // a function has a name and an expression computing its value (given x) and color
  std::string m_name;
  Expr *m_expr;
  Color *m_color;

  // value semantics prohibited
  Function(const Function &);
  Function &operator=(const Function &);

public:
  Function(const std::string &name, Expr *expr);
  ~Function();

  //accessor functions
  std::string get_name() const { return m_name; }
  Expr *get_expr() const       { return m_expr; }

  //member function to change the color associated with the function
  void set_color(Color* newColor);

  //member function to draw the function within the plot image. Takes a pointer to the array of image pixels and pointer to the plot bounds object as parameters 
  void draw(Color* img_pixels, Bounds* bounds) const;
};

#endif // FUNC_H
