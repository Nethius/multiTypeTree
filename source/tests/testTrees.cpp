//
// Created by Astan on 17.01.2021.
//

#include "testTrees.h"

namespace test {
    std::unique_ptr <MultiTypeTree> createTestTree1() {
        std::unique_ptr <MultiTypeTree> tree = std::make_unique<IntegerNumberType>(8);
        tree->initNode("bar");
        tree->initNode("baz");

        auto subNodes = tree->getNodes();
        subNodes[0]->initNode(2.015);
        subNodes[0]->initNode(2015);
        subNodes[0]->initNode("2015");

        subNodes[1]->initNode("foo");
        subNodes[1]->initNode(6.28318);

        auto subNodesLevel2 = subNodes[0]->getNodes();
        subNodesLevel2[0]->initNode(9);

        auto subNodesLevel3 = subNodes[1]->getNodes();
        subNodesLevel3[1]->initNode("hello");

        return tree;
    }

    std::unique_ptr<MultiTypeTree> createTestTree2() {
        std::unique_ptr <MultiTypeTree> tree = std::make_unique<IntegerNumberType>(8);
        tree->initNode("bar");
        tree->initNode("baz");

        auto subNodes = tree->getNodes();
        subNodes[0]->initNode(2.016);
        subNodes[0]->initNode(2016);
        subNodes[0]->initNode("2016");

        subNodes[1]->initNode("foo");
        subNodes[1]->initNode(6.28318);

        auto subNodesLevel2 = subNodes[0]->getNodes();
        subNodesLevel2[0]->initNode(9);

        auto subNodesLevel3 = subNodes[1]->getNodes();
        subNodesLevel3[1]->initNode("hello");

        return tree;
    }
}