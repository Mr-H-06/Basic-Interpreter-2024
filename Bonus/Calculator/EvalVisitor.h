#include "ExprParser.h"
#include "ExprVisitor.h"

#include <iostream>

class EvalVisitor : public ExprVisitor {
public:

  std::any visitCalc(ExprParser::CalcContext *ctx) override {
    /// TODO
    return std::any_cast<int>(ctx->expr()->accept(this));
  }

  std::any visitMulDiv(ExprParser::MulDivContext *ctx) override {
    /// TODO
    int left = std::any_cast<int>(ctx->expr(0)->accept(this));
    int right = std::any_cast<int>(ctx->expr(1)->accept(this));
    if (ctx->op->getType() == ExprParser::MUL) {
      return left * right;
    } else {
      if (right == 0) {
        throw std::runtime_error("Division by zero.");
      }
      return left / right;
    }
  }

  std::any visitAddSub(ExprParser::AddSubContext *ctx) override {
    /// TODO
    int left = std::any_cast<int>(ctx->expr(0)->accept(this));
    int right = std::any_cast<int>(ctx->expr(1)->accept(this));
    if (ctx->op->getType() == ExprParser::ADD) {
      return left + right;
    } else {
      return left - right;
    }
  }

  std::any visitInt(ExprParser::IntContext *ctx) override {
    /// TODO
    return std::stoi(ctx->INT()->getText());
  }

  std::any visitParens(ExprParser::ParensContext *ctx) override {
    /// TODO
    return ctx->expr()->accept(this);
  }

};