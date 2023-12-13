#include "Const.h"

#include "typedefine.h"

simodel::Const::Const() {
  unitType = "const";
  odeInfo.hasODE = false;
  outputs[0];
  mat _constant = {1};
  parameters["constant"] = _constant;
}

void simodel::Const::update() {
  auto _constant = parameters["constant"];
  if (_constant.type() == typeid(mat)) {
    outputs[0] = std::any_cast<mat>(_constant);
  }
}
