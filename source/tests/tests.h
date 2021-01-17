//
// Created by Astan on 17.01.2021.
//

#ifndef MULTITYPETREE_TESTS_H
#define MULTITYPETREE_TESTS_H

#include "multiTypeTree.h"

namespace test {
    /*!
     * Recursively check the hash of each node
     * @param node1 - pointer to the root of the first tree
     * @param node2 - pointer to the root of the second tree
     * @return true if the payload of the nodes are equal else false
     */
    bool isTreeNodesEqual(MultiTypeTree *node1, MultiTypeTree *node2);
}
#endif //MULTITYPETREE_TESTS_H
