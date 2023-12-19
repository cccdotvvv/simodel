#ifndef SIMODEL_TYPEDIFINE_H
#define SIMODEL_TYPEDIFINE_H

#include <any>
#include <armadillo>
#include <map>
#include <memory>
#include <string>

// #include "Simodel.h"

typedef arma::mat mat;
typedef std::map<int, mat> unitIO;
typedef std::map<std::string, std::any> keyAnyMap;
typedef std::map<std::string, mat> keyMatMap;

namespace simodel {
struct UnitMemento {
  keyMatMap states;
  unitIO inputs;
  unitIO outputs;
};

/*----------------------计算单元基类定义开始----------------------*/
class UnitBase {
 private:
  int unitID{};
  double t{};
  std::unordered_map<std::string, UnitMemento> mementors;

 protected:
  std::string unitType;
  unitIO inputs;
  unitIO outputs;
  keyMatMap states;
  keyAnyMap parameters;
  struct {
    bool hasODE{};
    mat yPrime;
    mat solution;
  } odeInfo;

 public:
  inline UnitBase();
  inline ~UnitBase();
  virtual void update() = 0;
  virtual inline void odeCalculator();
  [[nodiscard]] inline bool isNeedSolver() const;
  [[nodiscard]] inline mat getYPrime() const;
  inline void setYPrime(const mat &yPrime);
  [[nodiscard]] inline mat getSolution() const;
  inline void setSolution(const mat &solution);
  inline void setUnitType(const std::string &typeName);
  [[nodiscard]] inline std::string getUnitType() const;
  inline mat getInput(const int &inputPortID);
  inline mat getOutput(const int &outputPortID);
  inline mat getState(const std::string &stateName);
  inline void setInput(const int &inputPortID, const mat &inputValue);
  inline void setOutput(const int &inputPortID, const mat &outputValue);
  inline void setState(const std::string &stateName, const mat &stateValue);
  template <typename T>
  inline void setParameter(const std::string &parameterName, const T &value);
  virtual inline void initFromPara();
  inline void setUnitID(const int &curUnitID);
  inline void setCurrentTime(const double &currentTime);
  inline void saveMementor(const std::string &name);
  inline void restoreFromMementor(const std::string &name);
};

UnitBase::UnitBase() = default;

UnitBase::~UnitBase() {}

inline void UnitBase::odeCalculator() {}

bool UnitBase::isNeedSolver() const { return odeInfo.hasODE; }

inline mat UnitBase::getYPrime() const { return odeInfo.yPrime; }

inline void UnitBase::setYPrime(const mat &yPrime) { odeInfo.yPrime = yPrime; }

inline mat UnitBase::getSolution() const { return odeInfo.solution; }

inline void UnitBase::setSolution(const mat &solution) {
  odeInfo.solution = solution;
}

void UnitBase::setUnitType(const std::string &typeName) { unitType = typeName; }

std::string UnitBase::getUnitType() const { return unitType; }

inline mat UnitBase::getInput(const int &inputPortID) {
  return inputs.at(inputPortID);
}
inline mat UnitBase::getOutput(const int &outputPortID) {
  return outputs.at(outputPortID);
}
inline mat UnitBase::getState(const std::string &stateName) {
  return states.at(stateName);
}
inline void UnitBase::setInput(const int &inputPortID, const mat &inputValue) {
  inputs.at(inputPortID) = inputValue;
}
inline void UnitBase::setOutput(const int &inputPortID,
                                const mat &outputValue) {
  outputs.at(inputPortID) = outputValue;
}
inline void UnitBase::setState(const std::string &stateName,
                               const mat &stateValue) {
  states.at(stateName) = stateValue;
}
template <typename T>
inline void UnitBase::setParameter(const std::string &parameterName,
                                   const T &value) {
  this->parameters[parameterName] = value;
    initFromPara();
}
inline void UnitBase::initFromPara(){};
inline void UnitBase::setUnitID(const int &curUnitID) {
  this->unitID = curUnitID;
}

inline void UnitBase::setCurrentTime(const double &currentTime) {
  this->t = currentTime;
}

inline void UnitBase::saveMementor(const std::string &name) {
  this->mementors[name].inputs = this->inputs;
  this->mementors[name].states = this->states;
  this->mementors[name].outputs = this->outputs;
}

inline void UnitBase::restoreFromMementor(const std::string &name) {
  this->inputs = this->mementors[name].inputs;
  this->states = this->mementors[name].states;
  this->outputs = this->mementors[name].outputs;
}
/*----------------------计算单元基类定义结束----------------------*/

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

/*----------------------模型类的定义开始----------------------*/
class SolverBase;
class Simodel {
 private:
  int maxUnitID;
  std::unordered_map<int, unitInstance> units;
  std::vector<int> executionOrder;
  std::vector<int> odeUnitIDs;
  std::shared_ptr<SolverBase> solver;
  void calculateExecutionOrder();
  void findOdeUnitIDsAndSaveIt();

 public:
  Simodel();
  void addUnit(const std::shared_ptr<UnitBase> &newUnit);
  void deleteUnit(const int &unitID);
  void connectUnit(const std::pair<int, int> &outPort,
                   const std::pair<int, int> &inPort);
  void preparedToRun();
  void doStep();
  std::vector<int> getExecutionOrder();
  std::unordered_map<int, unitInstance> getUnits();
  void setSolver(const std::shared_ptr<SolverBase> &slvr);
};
/*----------------------模型类的定义结束----------------------*/

struct SolverOption {
  double h;
  double tInit;
  double tFinal;
  double hMax;
  double hMin;
  double tol;
};

/*----------------------求解器基类的定义开始----------------------*/
class SolverBase {
 protected:
  SolverOption option{};

 public:
  explicit SolverBase(SolverOption option) { this->option = option; };
  virtual void solveOneStep(Simodel *model) = 0;
};
/*----------------------求解器基类的定义结束----------------------*/

}  // namespace simodel

#endif