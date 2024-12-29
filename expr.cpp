
#include <cmath>
#include "exception.h"
#include "expr.h"
#include <iostream>
// Expr (base class)
Expr::Expr() {
 e1 = nullptr;
 e2 = nullptr;
};

void Expr::setLeft(Expr* e) {
    e1 = e;
 }
void Expr::setRight(Expr* e) {
    e2 = e;
}
Expr* Expr::getLeft() {
    return e1;
}
Expr* Expr::getRight() {
    return e2;
}
void Expr::clearChild(){
    delete e1;
    delete e2;
    e1 = nullptr;
    e2 = nullptr;
}
Expr::~Expr() {
    delete e1;
    delete e2;
    e1 = nullptr;
    e2 = nullptr;
}
//evaluation of var
double Variable::eval(double x) const {
    if (name == "x") {
        return x;
    } 
    else {
        throw PlotException("Invalid variable");
        return 0.0;
    }
}


//eval binary 
double BinaryOperation::eval(double x) const {
  
  if (e1 == nullptr || e2 == nullptr) {
        std::cerr << "Error: Binary operation has missing operands" << std::endl;
        std::cerr << "e1: " << e1->eval(1.0) << ", e2: " << e2->eval(1.0) << std::endl;
        throw PlotException("Binary operation has missing operands");
    }
  
    double lv = e1->eval(x);
    double rv = e2->eval(x);
    switch (op) {
        case '+':
            return lv + rv;
        case '-':
            return lv - rv;
        case '*':
            return lv * rv;
        case '/':
            if (rv != 0.0) {
                return lv / rv;
            } else {
                throw PlotException("Invalid Operation: Division by zero");
            }
        default:
            throw PlotException("Invalid binary operation");
    }
}





//eval unary 
double UnaryOperation::eval(double x) const {
    double operandValue = e1->eval(x); // if its x, pi, etc. 
    if (op == "sin") {
         return std::sin(operandValue);
    } else if (op == "cos") {
        return std::cos(operandValue);
    } else {
        throw PlotException("Unknown unary operator: " + op);
    }
}
// adding left and right side for binary 

//adding left and right side for operand 
void BinaryOperation::addOperand(Expr* operand)  {
    if (e1 == nullptr) {
        e1 = operand;
    } else if (e2 == nullptr) {
        e2 = operand;
    } else {
        throw PlotException("Binary operation already has two operands");
    }
}
//adding left and right side for operand 
void UnaryOperation::addOperand(Expr* operand) {
    if (e1 == nullptr) {
        e1 = operand;
    } else {
        throw PlotException("Unary operation already has an operand");
    }
}
//adds operands to deque
void addOperation::addOperand(Expr* operand)  {
    expressions.push_back(operand);
}
//iterates through the deque to return result
double addOperation::eval(double x) const {
    double result = 0;
    for (std::deque<Expr*>::const_iterator it = expressions.cbegin();
         it!=expressions.cend(); ++it){
        result += (*it)->eval(x);
    }
    return result;
}
//adds operands to deque
void multOperation::addOperand(Expr* operand)  {
    expressions.push_back(operand);
}
//iterates through the deque to return result
double multOperation::eval(double x) const {
    double result = 1;
    for (std::deque<Expr*>::const_iterator it = expressions.cbegin();
         it!=expressions.cend(); ++it){
        result = result * (*it)->eval(x);
    }
    return result;
}

 
