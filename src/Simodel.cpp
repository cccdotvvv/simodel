#include "Simodel.h"

namespace simodel {

Simodel::Simodel() { maxUnitID = 0; }

void Simodel::addUnit(const std::shared_ptr<UnitBase> &newUnit) {
  units.emplace(maxUnitID, unitInstance(newUnit));
  newUnit->setUnitID(maxUnitID);
  maxUnitID += 1;
}

void Simodel::deleteUnit(const int &unitID) {
  units.erase(unitID);
  for (int i = unitID + 1; i <= maxUnitID; ++i) {
    auto it = units.find(i);
    if (it != units.end()) {
      auto value = std::move(it->second);
      value.unit->setUnitID(i - 1);
      units.erase(it);
      units.emplace(i - 1, std::move(value));
    }
  }
  maxUnitID -= 1;
}

void Simodel::connectUnit(const std::pair<int, int> &outPort,
                          const std::pair<int, int> &inPort) {
  auto it1 = units.find(outPort.first);
  auto it2 = units.find(inPort.first);
  if (it1 != units.end() && it2 != units.end()) {
    it1->second.outPort.emplace(outPort.second, inPort);
    it2->second.inPort.emplace(inPort.second, outPort);
  }
}

void Simodel::calculateExecutionOrder() {
  while (executionOrder.size() < units.size()) {
    for (const auto &_unit : units) {
      if (std::find(executionOrder.begin(), executionOrder.end(),
                    _unit.first) != executionOrder.end()) {
        continue;
      }
      auto _depends = _unit.second.getDpendsUnitIDs();
      bool isAllDpendsOK = false;
      for (const auto &_depend : _depends) {
        isAllDpendsOK = std::find(executionOrder.begin(), executionOrder.end(),
                                  _depend) != executionOrder.end();
      }
      if (_depends.empty() || isAllDpendsOK) {
        executionOrder.push_back(_unit.first);
      }
    }
  }
}

void Simodel::setStepSize(const double &step) { this->stepSize = step; }

void Simodel::doStep() {
  this->calculateExecutionOrder();
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
      double h = this->stepSize;
      double y0 = curUnit->getOutput(0).at(0);
      double y1 = y0 + h * k0;
      curUnit->setOutput(0, mat(1, 1, arma::fill::value(y1)));
    } else {
      curUnit->update();
    }
    curUnitInstance.unit->update();
  }
}

}  // namespace simodel