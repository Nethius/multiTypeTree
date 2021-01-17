#include <iostream>
#include "source/multiTypeTree.h"
#include "source/tests/testTrees.h"
#include <fstream>
#include "source/tests/tests.h"

const size_t productionKeysCount = 5;
const size_t testKeysCount = 2;
const char expectedInputKey[] = "-i";
const char expectedOutputKey[] = "-o";
const char expectedTestKey[] = "-t";

void runProduction(const std::string &inputFile, const std::string &outputFile) {
    std::fstream inputStream;
    inputStream.open(inputFile, std::fstream::in | std::fstream::binary);
    auto treeFromFile = getTreeRootFromFile(inputStream);
    if (treeFromFile == nullptr) {
        std::cout << "Input file has the wrong structure or is empty" << std::endl;
        return;
    }
    if (!treeFromFile->deserialize(inputStream)) {
        std::cout << "Deserialization error" << std::endl;
        return;
    }
    inputStream.close();

    printTree("", treeFromFile.get(), false);

    std::fstream outputStream;
    outputStream.open(outputFile, std::fstream::out | std::fstream::binary);
    if (!treeFromFile->serialize(outputStream)) {
        std::cout << "Serialization error" << std::endl;
        return;
    }
    outputStream.close();
}

void runTests() {
    std::unique_ptr<MultiTypeTree> testTree1 = test::createTestTree1();

    std::fstream outputStream;
    outputStream.open("tempOutputFile", std::fstream::out | std::fstream::binary);
    if (!testTree1->serialize(outputStream)) {
        std::cout << "Serialization error" << std::endl;
        return;
    }
    outputStream.close();

    std::fstream inputStream;
    inputStream.open("tempOutputFile", std::fstream::in | std::fstream::binary);
    auto treeFromFile = getTreeRootFromFile(inputStream);
    if (treeFromFile == nullptr) {
        std::cout << "Input file has the wrong structure or is empty" << std::endl;
        return;
    }
    if (!treeFromFile->deserialize(inputStream)) {
        std::cout << "Deserialization error" << std::endl;
        return;
    }
    inputStream.close();

    std::unique_ptr<MultiTypeTree> testTree2 = test::createTestTree2();

    //in the first test the trees are the same
    auto test1Result = test::isTreeNodesEqual(testTree1.get(), treeFromFile.get());
    //in the second test no
    auto test2Result = test::isTreeNodesEqual(testTree2.get(), treeFromFile.get());
    if (test1Result && !test2Result)
        std::cout << "Tests completed successfully" << std::endl;
    else
        std::cout << "Tests failed" << std::endl;
}

int main(int argc, char *argv[]) {
    try {
        if (argc == productionKeysCount) {
            std::string inputKey = argv[1];
            std::string outputKey = argv[3];
            std::string inputFile = argv[2];
            std::string outputFile = argv[4];

            if (inputKey != expectedInputKey || outputKey != expectedOutputKey) {
                std::cout << "wrong command line keys" << std::endl;
                std::cout << "example of use: app.exe -i inputFile -o outputFile" << std::endl;
                return 0;
            }

            runProduction(inputFile, outputFile);
            return 0;
        } else if (argc == testKeysCount) {
            std::string testKey = argv[1];
            if (testKey != expectedTestKey) {
                std::cout << "wrong command line keys" << std::endl;
                std::cout << "example of use: app.exe -t" << std::endl;
                return 0;
            }
            runTests();
            return 0;
        } else {
            std::cout << "too few command line arguments" << std::endl;
            std::cout << "example of use: app.exe -i inputFile -o outputFile" << std::endl;
            return 0;
        }
    }
    catch (...) {
        std::cout << "Unhandled exception caught. The application will be closed" << std::endl;
        return 0;
    }
}
