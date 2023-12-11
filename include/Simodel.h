#ifndef SIMODEL_SIMODEL_H
#define SIMODEL_SIMODEL_H

#include <map>
#include <vector>
#include "typedefine.h"

namespace simodel
{
    struct ioInfo
    {
        std::vector<int> inportInfo;
        std::vector<int> outportInfo;
    };

    class Simodel
    {
    private:
        int maxUnitID;
        std::unordered_map<int, std::shared_ptr<UnitBase>> units;
        std::map<int, ioInfo> calcInfo;

    public:
        Simodel();
        void addUnit(const std::shared_ptr<UnitBase>& newUnit);
        void deleteUnit(const int& unitID);
    };
}

#endif