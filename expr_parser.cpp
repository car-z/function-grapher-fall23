#include <string>
#include <sstream>
#include <memory>
#include <deque>
#include <fstream>
#include "exception.h"
#include "expr.h"
#include "expr_parser.h"

ExprParser::ExprParser() {
}

ExprParser::~ExprParser() {
}
//parsing tokens out of a string stream 
Expr* ExprParser::parse(const std::string& expression) {
    std::istringstream iss(expression);
    std::deque<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return parsePfxExpr(tokens);
}
//recurisve parsing function 
Expr* ExprParser::parsePfxExpr(std::deque<std::string>& tokens) {
    if (tokens.empty()) {
        throw PlotException("Unexpected end of expression");
    }

    std::string token = tokens.front();
    tokens.pop_front();
    Expr* temp = nullptr;
    //for all numbers 
    if (((token[0] >= '0') && (token[0] <= '9')) || (token[0] == '.'))
  {
    std::stringstream ss;
    double flt;
    ss << token;
    ss >> flt;
    temp = new Literal(flt);
    return temp;
  }
  else if(token == "x"){ //for variable 
     return new Variable("x");
  }
  else if (token == "pi") { //for pi
    return new Literal(M_PI);
  }
  else if (token[0] == '(') {
    token = tokens.front();
    tokens.pop_front();
    switch (token[0])
    {
      case 'c': 
      {
        temp = new UnaryOperation("cos");
        break;
      }
      case 's': 
      {
        temp = new UnaryOperation("sin");
        break;
      }
      case '/':
      case '-':
      {
         temp = new BinaryOperation(token[0]); 
         temp->addOperand(parsePfxExpr(tokens));
         temp->addOperand(parsePfxExpr(tokens));
         break;
      }
      case '+':
        temp = new addOperation(token[0]);
        break;
      case '*': 
      {
          temp = new multOperation(token[0]);
          break;
      }
      default: 
       throw PlotException("Invalid Prefix Expression");
       break;
    } 
    while(tokens[0] != ")"){
        Expr* temp2 = parsePfxExpr(tokens);
        if (temp->type() == 'a' || temp->type() == 'm') {
        temp->addOperand(temp2);
      }
      else {
        if (temp->getRight() == nullptr)
          temp->setLeft(temp2);
        else if (temp->getRight() == nullptr)
          temp->setRight(temp2);
        else{
          throw PlotException ("Queue error");
          return 0;
        }
      }
      }
    tokens.pop_front();
    return temp;
  }
    //should never get here 
    std::cout << tokens[0] << std::endl;
    throw PlotException("Issue With Parsing Prefix Expression"); 
 
}



/* testing for parser:
int main() {
    ExprParser parser;
    try {
      std::ifstream inputFile("input.txt");
      std::cout << "Enter the expression:" << std::endl;
      Expr* expression = parser.parse(inputFile);
      std::cout << "parsing done" << std::endl;
      // Evaluate the parsed expression doesn't work yet 
      double result = expression->eval(1.0);
       std::cout << "Result: " << result << std::endl;
      delete expression; // Don't forget to delete the allocated expression
    } 
    catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

*/

