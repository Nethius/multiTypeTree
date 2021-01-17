//
// Created by Developer on 13.01.2021.
//

#include "multiTypeTree.h"

#include <utility>
#include <iostream>

enum AvailableTypes : uint8_t {
    INTEGER = 0,
    REAL,
    STRING
};

//this function based on this answer https://stackoverflow.com/a/51730733
void printTree(const std::string &prefix, MultiTypeTree *node, bool isLast) {
    if (node == nullptr)
        return;

    std::cout << prefix;
    std::cout << (isLast ? "|--" : "|__");

    node->printData();

    auto nodes = node->getNodes();
    for (size_t i = 0; i < nodes.size(); i++) {
        printTree(prefix + (isLast ? "|   " : "    "), nodes[i].get(), i + 1 != nodes.size());
    }

}

std::unique_ptr<MultiTypeTree> initBlankNode(AvailableTypes dataType) {
    std::unique_ptr<MultiTypeTree> node = nullptr;

    switch (dataType) {
        case INTEGER: {
            node = std::make_unique<IntegerNumberType>();
            break;
        }
        case REAL: {
            node = std::make_unique<RealNumberType>();
            break;
        }
        case STRING: {
            node = std::make_unique<StringType>();
            break;
        }
    }
    return node;
}

std::unique_ptr<MultiTypeTree> getTreeRootFromFile(std::fstream &fs) {
    if (!fs.is_open())
        return nullptr;
    AvailableTypes dataType;
    fs.read(reinterpret_cast<char *>(&dataType), sizeof(AvailableTypes));

    return initBlankNode(dataType);
}

bool MultiTypeTree::serialize(std::fstream &fs) {
    if (!fs.is_open())
        return false;
    if (!writeData(fs))
        return false;
    std::vector<size_t> subNodePos;
    size_t subNodesCount = nodes.size();
    fs.write(reinterpret_cast<char *>(&subNodesCount), sizeof(size_t));

    if (!subNodesCount)
        return true;

    for (size_t i = 0; i < subNodesCount; i++) {
        subNodePos.push_back(fs.tellp());
        fs.seekp(subNodePos[i] + sizeof(size_t));
    }
    for (size_t i = 0; i < subNodesCount; i++) {
        size_t lastPos = fs.tellp();
        fs.seekp(subNodePos[i]);
        fs.write(reinterpret_cast<char *>(&lastPos), sizeof(size_t));
        fs.seekp(lastPos);
        nodes[i]->serialize(fs);
    }
    return true;
}

bool MultiTypeTree::deserialize(std::fstream &fs) {
    if (!fs.is_open())
        return false;
    if (!readData(fs))
        return false;

    size_t subNodesCount;
    fs.read(reinterpret_cast<char *>(&subNodesCount), sizeof(size_t));
    if (!subNodesCount)
        return true;

    std::vector<size_t> subNodePos(subNodesCount);
    for (size_t i = 0; i < subNodesCount; i++) {
        fs.read(reinterpret_cast<char *>(&subNodePos[i]), sizeof(size_t));
    }

    for (size_t i = 0; i < subNodesCount; i++) {
        fs.seekg(subNodePos[i]);
        AvailableTypes dataType;
        fs.read(reinterpret_cast<char *>(&dataType), sizeof(AvailableTypes));

        nodes.push_back(initBlankNode(dataType));
        nodes[i]->deserialize(fs);
    }
    return true;
}

std::vector<std::shared_ptr<MultiTypeTree>> &MultiTypeTree::getNodes() {
    return nodes;
}

void MultiTypeTree::initNode(int32_t data) {
    nodes.push_back(std::make_shared<IntegerNumberType>(data));
}

void MultiTypeTree::initNode(double_t data) {
    nodes.push_back(std::make_shared<RealNumberType>(data));
}

void MultiTypeTree::initNode(const std::string &data) {
    nodes.push_back(std::make_shared<StringType>(data));
}

IntegerNumberType::IntegerNumberType(int32_t data) : data(data) {

}

bool IntegerNumberType::writeData(std::fstream &fs) {
    if (!fs.is_open())
        return false;
    AvailableTypes dataType = INTEGER;
    fs.write(reinterpret_cast<char *>(&dataType), sizeof(AvailableTypes));
    fs.write(reinterpret_cast<char *>(&data), sizeof(int32_t));
    return true;
}

bool IntegerNumberType::readData(std::fstream &fs) {
    if (!fs.is_open())
        return false;
    fs.read(reinterpret_cast<char *>(&data), sizeof(int32_t));
    return true;
}

void IntegerNumberType::printData() {
    std::cout << data << std::endl;
}

size_t IntegerNumberType::getDataHash() {
    return std::hash<int32_t>{}(data);
}

RealNumberType::RealNumberType(double_t data) : data(data) {

}

bool RealNumberType::writeData(std::fstream &fs) {
    if (!fs.is_open())
        return false;
    AvailableTypes dataType = REAL;
    fs.write(reinterpret_cast<char *>(&dataType), sizeof(AvailableTypes));
    fs.write(reinterpret_cast<char *>(&data), sizeof(double_t));
    return true;
}

bool RealNumberType::readData(std::fstream &fs) {
    if (!fs.is_open())
        return false;
    fs.read(reinterpret_cast<char *>(&data), sizeof(double_t));
    return true;
}

void RealNumberType::printData() {
    std::cout << data << std::endl;
}

size_t RealNumberType::getDataHash() {
    return std::hash<double_t>{}(data);
}

StringType::StringType(std::string data) : data(std::move(data)) {

}

bool StringType::writeData(std::fstream &fs) {
    if (!fs.is_open())
        return false;
    AvailableTypes dataType = STRING;
    fs.write(reinterpret_cast<char *>(&dataType), sizeof(AvailableTypes));
    size_t strSize = data.size();
    fs.write(reinterpret_cast<char *>(&strSize), sizeof(size_t));
    fs.write(data.data(), strSize);
    return true;
}

bool StringType::readData(std::fstream &fs) {
    if (!fs.is_open())
        return false;
    size_t strSize = data.size();
    fs.read(reinterpret_cast<char *>(&strSize), sizeof(size_t));
    data.resize(strSize);
    fs.read(reinterpret_cast<char *>(data.data()), strSize);
    return true;
}

void StringType::printData() {
    std::cout << data << std::endl;
}

size_t StringType::getDataHash() {
    return std::hash<std::string>{}(data);
}
