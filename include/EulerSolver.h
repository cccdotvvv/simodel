#ifndef _SIMODEL_EULER_SOLVER_H
#define _SIMODEL_EULER_SOLVER_H

#include "SimodelBase.h"

namespace simodel {

class EulerSolver : public SolverBase {
 public:
  explicit EulerSolver(SolverOption option);
  void advanceOneStep(Simodel* model) override;
};

}  // namespace simodel

#endif