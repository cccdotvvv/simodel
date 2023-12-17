#include "EulerSolver.h"

namespace simodel {

void EulerSolver::solveOneStep(Simodel *model) {
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
      curUnit->update();
      double k0 = curUnit->getYPrime().at(0);
      double h = model->getStepSize();
      double y0 = curUnit->getOutput(0).at(0);
      double y1 = y0 + h * k0;
      curUnit->setOutput(0, mat(1, 1, arma::fill::value(y1)));
    }
    curUnit->update();
  }
}

}  // namespace simodel
