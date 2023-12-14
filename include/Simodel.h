#ifndef SIMODEL_SIMODEL_H
#define SIMODEL_SIMODEL_H

#include <map>
#include <memory>
#include <vector>

#include "typedefine.h"

namespace simodel {
struct unitInstance {
  std::shared_ptr<UnitBase> unit;
  std::map<int, std::pair<int, int>> inPort;
  std::map<int, std::pair<int, int>> outPort;

  unitInstance() = default;
  explicit unitInstance(const std::shared_ptr<UnitBase> &unitIns) {
    unit = unitIns;
  }

  [[nodiscard]] std::vector<int> getDpendsUnitIDs() const {
    std::vector<int> res;
    res.reserve(this->inPort.size());
    for (const auto &_port : this->inPort) {
      res.push_back(_port.second.first);
    }
    return res;
  }
  [[nodiscard]] std::vector<int> getNextUnitIDs() const {
    std::vector<int> res;
    res.reserve(this->outPort.size());
    for (const auto &_port : this->outPort) {
      res.push_back(_port.second.first);
    }
    return res;
  }
};

class Simodel {
 private:
  int maxUnitID;
  std::unordered_map<int, unitInstance> units;
  std::vector<int> executionOrder;
  void calculateExecutionOrder();

 public:
  Simodel();
  void addUnit(const std::shared_ptr<UnitBase> &newUnit);
  void deleteUnit(const int &unitID);
  void connectUnit(const std::pair<int, int> &outPort,
                   const std::pair<int, int> &inPort);
  void doStep();
};

}  // namespace simodel

#endif