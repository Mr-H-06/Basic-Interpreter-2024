#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "EvalVisitor.h"
#include <iostream>

int main(int argc, const char* argv[]) {
  std::ifstream stream;
  stream.open("../testcases/example.in");
  if (!stream.is_open()) {
    std::cerr << "Could not open file" << std::endl;
    return 1;
  }
  antlr4::ANTLRInputStream input(stream);

  ExprLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);

  ExprParser parser(&tokens);

  antlr4::tree::ParseTree *tree = parser.calc();

  EvalVisitor eval;
  //eval.visit(tree);

  std::cout << std::any_cast<int> (eval.visit(tree));

  return 0;
}