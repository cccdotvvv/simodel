#include "EulerSolver.h"

#include "SimodelBase.h"

namespace simodel {

EulerSolver::EulerSolver(SolverOption option) : SolverBase(option){};

void EulerSolver::advanceOneStep(Simodel *model) {
  auto executionOrder = model->getExecutionOrder();
  auto units = model->getUnits();
  for (const auto &_unitID : executionOrder) {
    auto curUnitInstance = units[_unitID];
    for (const auto &_port : curUnitInstance.inPort) {
      curUnitInstance.unit->setInput(
          _port.first,
          units[_port.second.first].unit->getOutput(_port.second.second));
    }
    auto curUnit = curUnitInstance.unit;
    if (curUnit->isNeedSolver()) {
      curUnit->odeCalculator();
      auto k0 = curUnit->getYPrime();
      double h = this->option.h;
      auto y0 = curUnit->getOutput(0);
      auto y1 = y0 + h * k0;
      curUnit->setSolution(y1);
    }
    curUnit->update();
  }
}

}  // namespace simodel
