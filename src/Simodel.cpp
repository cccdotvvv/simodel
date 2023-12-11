#include "Simodel.h"

namespace simodel
{
    Simodel::Simodel()
    {   
        maxUnitID = 0;
    }

    void Simodel::addUnit(const std::shared_ptr<UnitBase>& newUnit)
    {
        units.emplace(maxUnitID, unitInstance(newUnit));
        maxUnitID += 1;
    }

    void Simodel::deleteUnit(const int &unitID)
    {
        units.erase(unitID);
        for (int i = unitID+1; i <= maxUnitID; ++i)
        {
            auto it = units.find(i);
            if (it != units.end())
            {
                auto value = std::move(it->second);
                units.erase(it);
                units.emplace(i-1, std::move(value));
            }
        }
        maxUnitID -= 1;
    }
}