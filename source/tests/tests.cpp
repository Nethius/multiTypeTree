//
// Created by Astan on 17.01.2021.
//

#include "tests.h"

namespace test {
    bool isTreeNodesEqual(MultiTypeTree *node1, MultiTypeTree *node2) {
        if (node1 == nullptr || node2 == nullptr)
            return false;
        if (node1->getDataHash() != node2->getDataHash())
            return false;
        auto subNodes1 = node1->getNodes();
        auto subNodes2 = node2->getNodes();
        if (subNodes1.size() != subNodes2.size())
            return false;
        for (size_t i = 0; i < subNodes1.size(); i++) {
            if (!isTreeNodesEqual(subNodes1[i].get(), subNodes2[i].get()))
                return false;
        }
        return true;
    }
}