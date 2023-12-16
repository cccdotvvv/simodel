#ifndef SIMODEL_ADD_H
#define SIMODEL_ADD_H

#include "SimodelBase.h"

namespace simodel {
class Add : public UnitBase {
 public:
  Add();
  void update() override;
  void updateFromPara() override;
};
}  // namespace simodel

#endif