//
// Created by Developer on 13.01.2021.
//

#ifndef MULTITYPETREE_MULTITYPETREE_H
#define MULTITYPETREE_MULTITYPETREE_H

#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

class MultiTypeTree {
    std::vector<std::shared_ptr<MultiTypeTree>> nodes;

    virtual bool writeData(std::fstream &fs) = 0;

    virtual bool readData(std::fstream &fs) = 0;

public:
    bool serialize(std::fstream &fs);

    bool deserialize(std::fstream &fs);

    void initNode(int32_t data);

    void initNode(double_t data);

    void initNode(const std::string &data);

    virtual void printData() = 0;

    std::vector<std::shared_ptr<MultiTypeTree>> &getNodes();
};

std::unique_ptr<MultiTypeTree> getTreeRootFromFile(std::fstream &fs);

void printTree(const std::string &prefix, MultiTypeTree *node, bool isLast);

class IntegerNumberType : public MultiTypeTree {
    int32_t data;

    bool writeData(std::fstream &fs);

    bool readData(std::fstream &fs);

public:
    IntegerNumberType(int32_t data);

    IntegerNumberType() {};

    void printData();
};

class RealNumberType : public MultiTypeTree {
    double_t data;

    bool writeData(std::fstream &fs);

    bool readData(std::fstream &fs);

public:
    RealNumberType(double_t data);

    RealNumberType() {};

    void printData();
};

class StringType : public MultiTypeTree {
    std::string data;

    bool writeData(std::fstream &fs);

    bool readData(std::fstream &fs);

public:
    StringType(std::string data);

    StringType() {};

    void printData();
};

#endif //MULTITYPETREE_MULTITYPETREE_H
