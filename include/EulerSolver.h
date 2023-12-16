#ifndef _SIMODEL_EULER_SOLVER_H
#define _SIMODEL_EULER_SOLVER_H

#include "SimodelBase.h"

namespace simodel {

class EulerSolver : public SolverBase {
 public:
  void solveOneStep(Simodel* model) override;
};

}  // namespace simodel

#endif