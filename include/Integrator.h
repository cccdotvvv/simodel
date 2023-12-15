#ifndef SIMODEL_INTEGRATOR_H
#define SIMODEL_INTEGRATOR_H

#include "typedefine.h"

namespace simodel {

class Integrator : public UnitBase {
 public:
  Integrator();
  void update() override;
  void updateFromPara() override;
};

}  // namespace simodel

#endif