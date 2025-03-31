#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <stack>
#include "Isle.h"

struct MapNode
{
    Isle *isle;
    MapNode *left, *right;
    int height = 1;

    MapNode(Isle *isle) : isle(isle), left(nullptr), right(nullptr), height(1) {}
    ~MapNode()
    {
        if (isle != nullptr)
        {
            delete isle;
        }
    }
};

class Map
{
private:
    MapNode *root; // Root node of the tree
    int rebalanceCount = 0;
    // Height of a node
    int height(MapNode *node);

    // AVL Rotations
    MapNode *rotateRight(MapNode *current);
    MapNode *rotateLeft(MapNode *current);

    // Helper functions for recursive AVL insertion and deletion
    // USE THEM
    MapNode *insert(MapNode *node, Isle *isle);
    MapNode *remove(MapNode *node, Isle *isle);

    // Item drop helper functions
    void preOrderItemDrop(MapNode *current, int &count);
    void postOrderItemDrop(MapNode *current, int &count);

public:
    // Constructor declaration
    Map();
    // Destructor
    ~Map();

    // Calculation of minumum depth a player can access at the map
    int calculateMinMapDepthAccess(int playerDepth, int totalShaperTreeHeight, int totalMapDepth);

    // Tree operations
    void insert(Isle *isle);
    void remove(Isle *isle);
    /// Search
    Isle *findIsle(Isle isle);
    Isle *findIsle(std::string name);
    MapNode *findNode(Isle isle);
    MapNode *findNode(std::string name);

    // Initilize tree from a vector
    void initializeMap(std::vector<Isle *> isles);

    MapNode *findFirstEmptyIsle(MapNode *node);

    int getDepth(MapNode *node);  // Determines the depth of a node within the tree.
    int getIsleDepth(Isle *isle); // Determines the depth of a isle within the tree.
    int getDepth();               // Total level of the tree

    // Display tree in terminal
    void display(MapNode *current, int depth, int state);
    void displayMap();

    // Item drop api
    void populateWithItems();
    void dropItemBFS();

    // Helper functions to write the avl tree
    void writeLevelOrder(MapNode *node, std::ofstream &oFile)
    {
        int h = height(node);
        for (int i = 1; i <= h; i++)
            writeCurrentLevel(root, i, oFile);
    }
    //  Write nodes at a current level
    void writeCurrentLevel(MapNode *node, int level, std::ofstream &oFile)
    {
        if (node == nullptr)
            return;
        if (level == 1)
            oFile << node->isle->getName() << " ";
        else if (level > 1)
        {
            writeCurrentLevel(node->left, level - 1, oFile);
            writeCurrentLevel(node->right, level - 1, oFile);
        }
    }

    // helper function to preorder traversal and adding it to a isles vector
    void collectIsles(MapNode *node, std::vector<Isle *> &isles)
    {
        if (node != nullptr)
        {
            isles.push_back(node->isle);
            collectIsles(node->left, isles);
            collectIsles(node->right, isles);
        }

        return;
    }
    // Write the AVL tree to a file with levels
    void writeToFile(const std::string &filename);
    // Write current Isles to file in alphabetical order
    void writeIslesToFile(const std::string &filename);
};

#endif