#include "Const.h"
#include "typedefine.h"

simodel::Const::Const()
{
    unitType = "const";
    odeInfo.hasODE = false;
    outputs[0];
    mat constant = {1};
    parameters["constant"] = constant;
}

void simodel::Const::update()
{
    outputs[0] = parameters["constant"];
}
