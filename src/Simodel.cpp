#include "SimodelBase.h"

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

void Simodel::doStep() {
  this->calculateExecutionOrder();
  this->solver->solveOneStep(this);
}

std::vector<int> Simodel::getExecutionOrder() { return this->executionOrder; }

std::unordered_map<int, unitInstance> Simodel::getUnits() {
  return this->units;
}

void Simodel::setSolver(const std::shared_ptr<SolverBase> &slvr) {
  this->solver = slvr;
}

}  // namespace simodel