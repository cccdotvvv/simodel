#include "Const.h"
#include "Simodel.h"
#include "typedefine.h"
#include <memory>

using namespace arma;

int main() {
  auto const1 = std::make_shared<simodel::Const>();
  const1->update();
  const1->getOutput(0).print();

  auto const2 = std::make_shared<simodel::Const>();
  const2->update();
  const2->getOutput(0).print();

  auto const3 = std::make_shared<simodel::Const>();
  const3->update();
  const3->getOutput(0).print();

  auto sm = std::make_shared<simodel::Simodel>();
  sm->addUnit(const1);
  sm->addUnit(const2);
  sm->addUnit(const3);

  sm->deleteUnit(2);
  sm->deleteUnit(1);
}
