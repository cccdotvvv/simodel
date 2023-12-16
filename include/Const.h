#ifndef SIMODEL_CONST_H
#define SIMODEL_CONST_H

#include "SimodelBase.h"

namespace simodel {
class Const : public UnitBase {
 public:
  Const();
  void update() override;
};
}  // namespace simodel

#endif