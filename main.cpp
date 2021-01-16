#include <iostream>
#include "multiTypeTree.h"
#include <fstream>

std::unique_ptr<MultiTypeTree> createTestTree() {
    std::unique_ptr<MultiTypeTree> tree = std::make_unique<IntegerNumberType>(8);
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

int main(int argc, char *argv[]) {
    if (argc < 5) {
        std::cout << "too few command line arguments" << std::endl;
        std::cout << "example of use: app.exe -i inputFile -o outputFile" << std::endl;
        return 0;
    }

    if (std::string(argv[1]) != "-i" || std::string(argv[3]) != "-o") {
        std::cout << "wrong command line keys" << std::endl;
        std::cout << "example of use: app.exe -i inputFile -o outputFile" << std::endl;
        return 0;
    }

//    std::unique_ptr<MultiTypeTree> tree = createTestTree();

    std::fstream inputStream;
    inputStream.open(argv[2], std::fstream::in | std::fstream::binary);
    auto treeFromFile = getTreeRootFromFile(inputStream);
    treeFromFile->deserialize(inputStream);
    inputStream.close();

    printTree("", treeFromFile.get(), false);

    std::fstream outputStream;
    outputStream.open(argv[4], std::fstream::out | std::fstream::binary);
    treeFromFile->serialize(outputStream);
    outputStream.close();

    return 0;
}
