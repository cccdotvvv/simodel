#include <memory>
#include <utility>

#include "Add.h"
#include "Const.h"
#include "Simodel.h"

using namespace arma;

int main() {
  auto const1 = std::make_shared<simodel::Const>();
  const1->setParameter("constant", mat(1, 1, fill::value(1)));

  auto const2 = std::make_shared<simodel::Const>();
  const2->setParameter("constant", mat(1, 1, fill::value(2)));

  auto const3 = std::make_shared<simodel::Const>();
  const3->setParameter("constant", mat(1, 1, fill::value(3)));

  auto add = std::make_shared<simodel::Add>();
  add->setParameter("operators", std::string("+-+"));

  auto sm = std::make_shared<simodel::Simodel>();
  sm->addUnit(const1);
  sm->addUnit(const2);
  sm->addUnit(const3);
  sm->connectUnit(std::make_pair(0, 1), std::make_pair(3, 0));
  sm->connectUnit(std::make_pair(1, 1), std::make_pair(3, 1));
  sm->connectUnit(std::make_pair(2, 1), std::make_pair(3, 2));

  const1->update();
  const2->update();
  const3->update();
  add->setInput(0, const1->getOutput(0));
  add->setInput(1, const2->getOutput(0));
  add->setInput(2, const3->getOutput(0));
  add->update();

  add->getOutput(0).print();
}
