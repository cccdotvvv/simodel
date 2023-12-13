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
}  // namespace simodel