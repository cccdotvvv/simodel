#ifndef SIMODEL_INTEGRATOR_H
#define SIMODEL_INTEGRATOR_H

#include "SimodelBase.h"

namespace simodel {

class Integrator : public UnitBase {
 public:
  Integrator();
  void update() override;
  void odeCalculator() override;
  void updateFromPara() override;
};

}  // namespace simodel

#endif