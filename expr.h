
#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <string>
#include <cmath>
#include <exception>
#include <deque>
class Expr {
private:
  // value semantics are prohibited
  Expr(const Expr &);
  Expr &operator=(const Expr &);
  
protected:
  Expr* e1;
  Expr* e2;
public:
  Expr();
  virtual ~Expr();
  virtual double eval(double x) const = 0;
  void setLeft(Expr* e);
  void setRight(Expr* e);
  Expr* getLeft();
  Expr* getRight();
  virtual void addOperand(Expr* operand) = 0;
  virtual char type() = 0;
  void clearChild();
  
};


class Literal : public Expr {
  public: 
    Literal(double val) : val(val) {}
    double eval(double) const override { return val; }
    void addOperand(Expr*)  override {}; //not relevant 
    char type() override {return 'l';}
  private:
    double val;
};

class Variable : public Expr {
  public: 
    Variable(const std::string& varName) : name(varName) { }
    double eval(double x) const override;
    void addOperand(Expr*)  override {}; //not relevant 
    char type() override {return 'v';}
  private:
  std::string name;
  
};

class BinaryOperation : public Expr {
  public: 
    BinaryOperation(const char c) : op(c) {}
    double eval(double x) const override;
    void addOperand(Expr* operand)  override; 
    char type() override {return 'b';}
  private:
    char op; // operation 
};

class addOperation : public Expr {
  public: 
    addOperation(const char c) : op(c) {}
    double eval(double x) const override;
    void addOperand(Expr* operand)  override; 
    char type() override {return 'a';}
    ~addOperation() {
       for (std::deque<Expr*>::iterator it = expressions.begin();
        it!=expressions.end(); ++it){
            delete *it;
        }
    }
  private:
    char op; // operation 
    std::deque<Expr *> expressions;
};

class multOperation : public Expr {
  public: 
    multOperation(const char c) : op(c) {}
    double eval(double x) const override;
    void addOperand(Expr* operand)  override; 
    char type() override {return 'm';}
    ~multOperation(){ //couldn't get it to work within expr.cpp
        for (std::deque<Expr*>::iterator it = expressions.begin();
        it!=expressions.end(); ++it){
            delete *it;
        }
    }
  private:
    char op; // operation 
     std::deque<Expr *> expressions;
};

class UnaryOperation : public Expr {
private:
    std::string op;
public:
    UnaryOperation(const std::string& oper) : op(oper) {}
    char type() override {return 'u';}
    double eval(double x) const override;
    void addOperand(Expr* operand)  override;
};
#endif // EXPR_H
