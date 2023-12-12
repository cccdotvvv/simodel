#ifndef SIMODEL_SIMODEL_H
#define SIMODEL_SIMODEL_H

#include <map>
#include <memory>

#include "typedefine.h"

namespace simodel {
struct unitInstance {
  std::shared_ptr<UnitBase> unit;
  std::map<int, std::pair<int, int>> inPort;
  std::map<int, std::pair<int, int>> outPort;

  explicit unitInstance(const std::shared_ptr<UnitBase> &unitIns) {
    unit = unitIns;
  }
};

class Simodel {
 private:
  int maxUnitID;
  std::unordered_map<int, unitInstance> units;

 public:
  Simodel();
  void addUnit(const std::shared_ptr<UnitBase> &newUnit);
  void deleteUnit(const int &unitID);
  void connectUnit(const std::pair<int, int> &outPort,
                   const std::pair<int, int> &inPort);
};
}  // namespace simodel

#endif