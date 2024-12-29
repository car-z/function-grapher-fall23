
#ifndef FN_PARSER_H
#define FN_PARSER_H

#include <iostream>
#include <deque>
#include "expr.h"

class ExprParser {
private:
  // value semantics are prohibited
  ExprParser(const ExprParser &);
  ExprParser &operator=(const ExprParser &);

public:
  ExprParser();
  ~ExprParser();
  Expr* parse(const std::string& expression);
  Expr* parsePfxExpr(std::deque<std::string>& tokens);
};

#endif // FN_PARSER_H
