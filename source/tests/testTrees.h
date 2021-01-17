//
// Created by Astan on 17.01.2021.
//

#ifndef MULTITYPETREE_TESTTREES_H
#define MULTITYPETREE_TESTTREES_H

#include "multiTypeTree.h"

namespace test {
    /*!
     * create a tree from prepared parameters
     * @return pointer on the tree root
     */
    std::unique_ptr<MultiTypeTree> createTestTree1();

    std::unique_ptr<MultiTypeTree> createTestTree2();
}

#endif //MULTITYPETREE_TESTTREES_H
