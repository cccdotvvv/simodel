#ifndef SIMODEL_SIMODEL_H
#define SIMODEL_SIMODEL_H

#include <map>
#include <vector>
#include "typedefine.h"

namespace simodel
{
    struct unitInstance
    {
        std::shared_ptr<UnitBase> unit;
        std::map<int, int> inport;
        std::map<int, int> outport;
        
        unitInstance(const std::shared_ptr<UnitBase>& unitIns)
        {
            unit = unitIns;
        }
    };

    class Simodel
    {
    private:
        int maxUnitID;
        std::unordered_map<int, unitInstance> units;

    public:
        Simodel();
        void addUnit(const std::shared_ptr<UnitBase>& newUnit);
        void deleteUnit(const int& unitID);
    };
}

#endif