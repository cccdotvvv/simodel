#ifndef SIMODEL_TYPEDIFINE_H
#define SIMODEL_TYPEDIFINE_H

#include <any>
#include <armadillo>
#include <map>
#include <string>

typedef arma::mat mat;
typedef std::map<int, mat> unitIO;
typedef std::map<std::string, std::any> keyAnyMap;
typedef std::map<std::string, mat> keyMatMap;

namespace simodel {
// 计算单元基类
class UnitBase {
 private:
  int unitID{};

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
  virtual inline void updateFromPara();
  inline void setUnitID(const int &curUnitID);
};

UnitBase::UnitBase() = default;

UnitBase::~UnitBase() {}

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
  updateFromPara();
}
inline void UnitBase::updateFromPara(){};
inline void UnitBase::setUnitID(const int &curUnitID) {
  this->unitID = curUnitID;
}
}  // namespace simodel

#endif