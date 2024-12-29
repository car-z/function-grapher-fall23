
#include <iostream>
#include <map>
#include <sstream>
#include <cstdint>
#include "exception.h"
#include "plot.h"
#include "reader.h"
#include "expr_parser.h"
#include "fill.h"
using std::string;
using std::stringstream;
using std::ifstream;
//constructor
Reader::Reader() {
}

//destructor
Reader::~Reader() {
}

//reads input and fills Plot object
void Reader::read_input(std::istream &in, Plot &plot) {
  string line;
  bool found = false;
  int count = 0;
  //reads input line by line
  while(std::getline(in, line)){
    count++;
    stringstream ss(line);
    string command;
    ss >> command;

    if(count != 1 && !found){
      throw PlotException("Plot must be specified first");
    }

    if(command == "Plot"){
      //only one plot can be inputted
      if(count != 1){
        throw PlotException("No more than one Plot");
      }
      found = true;
      double xmin = 0;
      double ymin = 0;
      double xmax = 0;
      double ymax = 0;
      int width = 0;
      int height = 0;
      ss >> xmin >> ymin >> xmax >> ymax >> width >> height;
      //checks if stringstream has too many arguments
      if(!ss.eof()){ 
        throw PlotException("Too many arguments in Plot directive");
      }
      //plot bounds check
      if (xmin >= xmax || ymin >= ymax || width <= 0 || height <= 0) {
        throw PlotException("Invalid parameters");
      }

      Bounds* bounds = new Bounds(xmin,ymin,xmax,ymax,width,height);
      plot.add_bounds(bounds);

    } else if (command == "Function"){
      string name;
      string expression;
      ss >> name;
      Function* func = plot.find_function(name);
      if(func){
        throw PlotException("Creating multiple functions with the same name");
      }
      getline(ss, expression);
       //creating new ExprParser object
      ExprParser parser;
      //parse expression into expression tree
      Expr* ptr_expr = parser.parse(expression);
      //new Function object with parsed expression
      Function* newfunc = new Function(name, ptr_expr);
      //add new Function to Plot
      plot.add_function(newfunc);

    }else if (command == "Color"){ 
      string fn_name;
      int r, g, b = -1;
      ss >> fn_name >> r >> g >> b;

      if(!ss.eof()){ 
        throw PlotException("Invalid arguments in Color directive");
      }
      //check for r,g,b to be valid value
      if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255){
        throw PlotException("Invalid/Missing values for r,g,b");

      }
      //create new Color object
      Color* newColor = new Color(r,g,b);
      //finds corresponding Function object with function name
      Function* func = plot.find_function(fn_name);
      if(!func){
        throw PlotException("No valid Function specified for Color directive");
      }
      //sets colors with Function
      func->set_color(newColor);

    }else if (command == "FillAbove"){
      string fn_name;
      float opacity = -0.1;
      int r, g, b = -1;
      ss >> fn_name >> opacity >> r >> g >> b;

      if(!ss.eof()){ 
        throw PlotException("Invalid arguments in FillAbove directive");
      }

      if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255){
        throw PlotException("Invalid/Missing values for r,g,b");
      }
      //check for valid opacity value
      if(opacity < 0.0 || opacity > 1.0){
        throw PlotException("Invalid opacity value");
      }

      Color* newColor = new Color(r,g,b);
      Function* func = plot.find_function(fn_name);
      if(!func){
        throw PlotException("No valid Function specified for FillAbove directive");
      }
      //creates new Fill object with fil type ABOVE with specified opacity, color, and function
      Fill* newFill = new Fill(ABOVE,opacity,newColor,func);
      //adds new Fill object to Plot
      plot.add_fill(newFill);

    }else if (command == "FillBelow"){
      string fn_name;
      float opacity = -0.1;
      int r, g, b = -1;
      ss >> fn_name >> opacity >> r >> g >> b;

      if(!ss.eof()){ 
        throw PlotException("Invalid arguments in FillBelow directive");
      }

      if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255){
        throw PlotException("Invalid/Missing values for r,g,b");
      }
      if(opacity < 0.0 || opacity > 1.0){
        throw PlotException("Invalid opacity value");
      }

      Color* newColor = new Color(r,g,b);
      Function* func = plot.find_function(fn_name);
      if(!func){
        throw PlotException("No valid Function specified for FillBelow directive");
      }
      //creates new Fill object with fil type BELOW with specified opacity, color, and function
      Fill* newFill = new Fill(BELOW,opacity,newColor,func);
      plot.add_fill(newFill);

    }else if (command == "FillBetween"){
      string fn_name1;
      string fn_name2;
      float opacity = -0.1;
      int r, g, b = -1;
      ss >> fn_name1 >> fn_name2 >> opacity >> r >> g >> b;

      if(!ss.eof()){ 
        throw PlotException("Invalid arguments in FillBetween directive");
      }

      if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255){
        throw PlotException("Invalid/Missing values for r,g,b");
      }
      if(opacity < 0.0 || opacity > 1.0){
        throw PlotException("Invalid opacity value");
      }

      Color* newColor = new Color(r,g,b);
      Function* func1 = plot.find_function(fn_name1);
      if(!func1){
        throw PlotException("Invalid function specified for FillBetween directive");
      }
      Function* func2 = plot.find_function(fn_name2);
      if(!func2){
        throw PlotException("Invalid Function specified for FillBetween directive");
      }
      //creates new Fill object with fil type BETWEEN with specified opacity, color, and functions
      Fill* newFill = new Fill(BETWEEN,opacity,newColor,func1,func2);
      plot.add_fill(newFill);
      
    }else{
      throw PlotException("unknown directive");
    }
    
  } 
}
