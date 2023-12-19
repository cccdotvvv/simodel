#include "Add.h"

#include <any>

namespace simodel {

Add::Add() {
  this->unitType = "Add";
  this->odeInfo.hasODE = false;
  this->inputs[0];
  this->inputs[1];
  this->outputs[0];
  this->parameters["operators"] = "++";
}

void Add::update() {
  auto ops = std::any_cast<std::string>(parameters["operators"]);
  mat res = inputs[0];
  res.zeros();
  for (int i = 0; i < ops.length(); ++i) {
    if (ops[i] == '-') {
      res -= inputs[i];
    } else if (ops[i] == '+') {
      res += inputs[i];
    }
  }
  outputs[0] = res;
}

void Add::initFromPara() {
  auto operators = std::any_cast<std::string>(parameters["operators"]);
  for (int i = 0; i < operators.length(); ++i) {
    inputs[i];
  }
}

}  // namespace simodel