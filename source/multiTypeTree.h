//
// Created by Developer on 13.01.2021.
//

#ifndef MULTITYPETREE_MULTITYPETREE_H
#define MULTITYPETREE_MULTITYPETREE_H

#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <functional>

class MultiTypeTree {
    std::vector<std::shared_ptr<MultiTypeTree>> nodes; //array of pointers to sub nodes

    /*!
     * write payload of node and data type to file
     * @param fs - Open filestream for writing
     * @return - true if successfully else false
     */
    virtual bool writeData(std::fstream &fs) = 0;

    /*!
     * read payload of node from file
     * @param fs - Open filestream for reading
     * @return - true if successfully else false
     */
    virtual bool readData(std::fstream &fs) = 0;

public:
    /*!
     * recursively write the tree to a file
     * @param fs - Open filestream for writing
     * @return - true if successfully else false
     */
    bool serialize(std::fstream &fs);

    /*!
     * recursively read tree from file
     * @param fs - Open filestream for reading
     * @return - true if successfully else false
     */
    bool deserialize(std::fstream &fs);

    /*!
     * initialize a new node depending on the data type
     * @param data - payload of node
     */
    void initNode(int32_t data);

    void initNode(double_t data);

    void initNode(const std::string &data);

    /*!
     * print payload of node
     */
    virtual void printData() = 0;

    /*!
     * get hash of node payload
     */
    virtual size_t getDataHash() = 0;

    /*!
     * get reference to array of subnodes
     */
    std::vector<std::shared_ptr<MultiTypeTree>> &getNodes();
};

/*!
 * read tree root from file
 * @param fs - Open filestream for reading
 * @return - pointer on the tree root if exist else nullptr
 */
std::unique_ptr<MultiTypeTree> getTreeRootFromFile(std::fstream &fs);

/*!
 * recursively print a tree to the console
 * @param prefix - for tree structure in console
 * @param node - current node to print
 * @param isLast -
 */
void printTree(const std::string &prefix, MultiTypeTree *node, bool isLast);

class IntegerNumberType : public MultiTypeTree {
    int32_t data{};

    bool writeData(std::fstream &fs) override;

    bool readData(std::fstream &fs) override;

public:
    explicit IntegerNumberType(int32_t data);

    IntegerNumberType() = default;

    size_t getDataHash() override;

    void printData() override;
};

class RealNumberType : public MultiTypeTree {
    double_t data{};

    bool writeData(std::fstream &fs) override;

    bool readData(std::fstream &fs) override;

public:
    explicit RealNumberType(double_t data);

    RealNumberType() = default;

    size_t getDataHash() override;

    void printData() override;
};

class StringType : public MultiTypeTree {
    std::string data;

    bool writeData(std::fstream &fs) override;

    bool readData(std::fstream &fs) override;

public:
    explicit StringType(std::string data);

    StringType() = default;

    size_t getDataHash() override;

    void printData() override;
};

#endif //MULTITYPETREE_MULTITYPETREE_H
