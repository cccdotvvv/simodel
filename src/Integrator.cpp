#include "Integrator.h"

#include <any>

namespace simodel {

Integrator::Integrator() {
  this->odeInfo.hasODE = true;
  this->inputs[0];
  this->parameters["init"] = mat(1, 1, arma::fill::value(0));
  this->outputs[0] = std::any_cast<mat>(parameters["init"]);
}

void Integrator::update() {
  this->odeInfo.yPrime = this->inputs[0];
  this->outputs[0] = this->odeInfo.solution;
}

void Integrator::updateFromPara() {
  this->outputs[0] = std::any_cast<mat>(this->parameters["init"]);
}

}  // namespace simodel