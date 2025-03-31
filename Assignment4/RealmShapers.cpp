#include "RealmShapers.h"
#include <cmath>
#include <algorithm>

ShaperTree::ShaperTree()
{
}

ShaperTree::~ShaperTree()
{
    // TODO: Free any dynamically allocated memory if necessary
    for (RealmShaper *object : realmShapers)
    {
        delete object;
    }
    realmShapers.clear();
}

void ShaperTree::initializeTree(std::vector<RealmShaper *> shapers)
{
    // TODO: Insert initial shapers to the tree
    for (RealmShaper *player : shapers)
    {
        realmShapers.push_back(player);
    }
}

int ShaperTree::getSize()
{

    return realmShapers.size();
}

std::vector<RealmShaper *> ShaperTree::getTree()
{
    return realmShapers;
}

bool ShaperTree::isValidIndex(int index)
{
    bool isValid = false;

    if (realmShapers[index] != NULL && index < realmShapers.size())
    {
        isValid = true;
    }

    return isValid;
}

void ShaperTree::insert(RealmShaper *shaper)
{
    realmShapers.push_back(shaper);
}

int ShaperTree::remove(RealmShaper *shaper)
{
    if (realmShapers.empty())
    {
        return -1;
    }
    int index = findIndex(shaper);

    int lastIndex = realmShapers.size() - 1;
    if (index != -1)
    {
        // return index if found and removed
        realmShapers.erase(realmShapers.begin() + index);
    }

    return index;
}

int ShaperTree::findIndex(RealmShaper *shaper)
{
    // return index in the tree if found
    int index = -1;
    for (int i = 0; i < realmShapers.size(); i++)
    {
        if (realmShapers[i] == shaper)
        {
            // return index if found
            index = i;
        }
    }
    // else
    return index;
}

int ShaperTree::getDepth(RealmShaper *shaper)
{

    // return depth of the node in the tree if found
    int index = findIndex(shaper);

    if (index < 0)
    {
        return -1;
    }

    int shaperDepth = static_cast<int>(log2(index + 1));
    
    return shaperDepth;
}

int ShaperTree::getDepth()
{
    // return total|max depth|height of the tree
    if (realmShapers.empty())
    {
        return 0;
    }
    int totalShaperDepth = static_cast<int>(log2(realmShapers.size()));
    return totalShaperDepth;
}

RealmShaper ShaperTree::duel(RealmShaper *challenger, bool result)
{
    // TODO: Implement duel logic, return the victor
    int challengerIndex = findIndex(challenger);
    if (getParent(challenger))
    {

        RealmShaper *parent = getParent(challenger);
        int parentIndex = findIndex(parent);
        if (result)
        {
            std::cout << "[Duel] " << challenger->getName() << " won the duel" << std::endl;
            replace(challenger, parent);
            challenger->gainHonour();
            parent->loseHonour();
            std::cout << "[Honour] " << "New honour points: ";
            std::cout << challenger->getName() << "-" << challenger->getHonour() << " ";
            if (parent->getHonour() <= 0)
            {
                std::cout << parent->getName() << "-" << 0 << std::endl;
                std::cout << "[Duel] " << parent->getName() << " lost all honour, delete" << std::endl;
                remove(parent);
            }
            else
            {
                std::cout << parent->getName() << "-" << parent->getHonour() << std::endl;
            }
            return *challenger;
        }
        else
        {
            std::cout << "[Duel] " << parent->getName() << " won the duel" << std::endl;
            parent->gainHonour();
            challenger->loseHonour();
            std::cout << "[Honour] " << "New honour points: ";
            if (challenger->getHonour() <= 0)
            {
                std::cout << challenger->getName() << "-" << 0 << " ";
                std::cout << "[Duel] " << challenger->getName() << " lost all honour, delete" << std::endl;
                remove(challenger);
            }
            else
            {
                std::cout << challenger->getName() << "-" << challenger->getHonour() << " ";
            }
            std::cout << parent->getName() << "-" << parent->getHonour() << std::endl;
            return *parent;
        }
    }
    else
    {
        return *challenger;
    }

    // Use   std::cout << "[Duel] " << victorName << " won the duel" << std::endl;
    // Use   std::cout << "[Honour] " << "New honour points: ";
    // Use   std::cout << challengerName << "-" << challengerHonour << " ";
    // Use   std::cout << opponentName << "-" << opponentHonour << std::endl;
    // Use   std::cout << "[Duel] " << loserName << " lost all honour, delete" << std::endl;
}

RealmShaper *ShaperTree::getParent(RealmShaper *shaper)
{
    int index = findIndex(shaper);
    RealmShaper *parent = nullptr;
    if (index <= 0) // Root or null condition
    {
        return nullptr;
    }
    // TODO: return parent of the shaper

    int parent_index = (index - 1) / 2;

    parent = realmShapers[parent_index];

    return parent;
}

void ShaperTree::replace(RealmShaper *player_low, RealmShaper *player_high)
{

    int lowIndex = findIndex(player_low);
    int highIndex = findIndex(player_high);

    std::cerr << "Low Index: " << lowIndex << std::endl;
    std::cerr << "High Index: " << highIndex << std::endl;
    if (lowIndex == -1 || highIndex == -1)
    {
        std::cerr << "Error: One or both players not found in the Shaper Tree.\n";
        return;
    }

    RealmShaper *temp = realmShapers[lowIndex];
    realmShapers[lowIndex] = realmShapers[highIndex];
    realmShapers[highIndex] = temp;
}

RealmShaper *ShaperTree::findPlayer(RealmShaper shaper)
{
    RealmShaper *foundShaper = nullptr;

    // TODO: Search shaper by object
    // Return the shaper if found
    for (RealmShaper *player : realmShapers)
    {
        if (*player == shaper)
        {
            foundShaper = player;
            break;
        }
    }
    // Return nullptr if shaper not found
    return foundShaper;
}

// Find shaper by name
RealmShaper *ShaperTree::findPlayer(std::string name)
{
    RealmShaper *foundShaper = nullptr;

    // TODO: Search shaper by name
    for (RealmShaper *player : realmShapers)
    {
        if (player->getName() == name)
        {
            foundShaper = player;
            break;
        }
    }
    // Return nullptr if shaper not found

    return foundShaper;
}

std::vector<std::string> ShaperTree::inOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // Add all to a string vector
    // Return the vector

    recInorder(index, result);

    // Note: Since ShaperTree is not an binary search tree,
    // in-order traversal will not give rankings in correct order
    // for correct order you need to implement level-order traversal
    // still you are to implement this function as well
    return result;
}

std::vector<std::string> ShaperTree::preOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement preOrderTraversal in tree
    // Add all to a string vector
    // Return the vector
    recPreorder(index, result);

    // Define and implement as many helper functions as necessary for recursive implementation
    return result;
}

std::vector<std::string> ShaperTree::postOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement postOrderTraversal in tree
    // Add all to a string vector
    // Return the vector
    recPostorder(index, result);

    // Define and implement as many helper functions as necessary for recursive implementation
    return result;
}

void ShaperTree::preOrderTraversal(int index, std::ofstream &outFile)
{
    // TODO: Implement preOrderTraversal in tree
    // write nodes to output file
    recPreorder(index, outFile);
    // Define and implement as many helper functions as necessary for recursive implementation
}

void ShaperTree::breadthFirstTraversal(std::ofstream &outFile)
{
    // TODO: Implement level-order traversal
    // write nodes to output file

    for (RealmShaper *player : realmShapers)
    {
        outFile << player->getName() << std::endl;
    }

    // Define and implement as many helper functions as necessary
}

void ShaperTree::displayTree()
{
    std::cout << "[Shaper Tree]" << std::endl;
    printTree(0, 0, "");
}

// Helper function to print tree with indentation
void ShaperTree::printTree(int index, int level, const std::string &prefix)
{
    if (!isValidIndex(index))
        return;

    std::cout << prefix << (level > 0 ? "   └---- " : "") << *realmShapers[index] << std::endl;
    int left = index * 2 + 1;  // TODO: Calculate left index
    int right = index * 2 + 2; // TODO: Calculate right index

    if (isValidIndex(left) || isValidIndex(right))
    {
        printTree(left, level + 1, prefix + (level > 0 ? "   │   " : "")); // ╎
        printTree(right, level + 1, prefix + (level > 0 ? "   │   " : ""));
    }
}

void ShaperTree::writeShapersToFile(const std::string &filename)
{
    // TODO: Write the shapers to filename output level by level
    std::ofstream outputFile(filename);
    breadthFirstTraversal(outputFile);
    std::cout << "[Output] " << "Shapers have been written to " << filename << " according to rankings." << std::endl;
    outputFile.close();
    // Use std::cout << "[Output] " << "Shapers have been written to " << filename << " according to rankings." << std::endl;
}

void ShaperTree::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output pre-order
    std::ofstream outputFile(filename);
    preOrderTraversal(0, outputFile);
    std::cout << "[Output] " << "Tree have been written to " << filename << " in pre-order." << std::endl;
    outputFile.close();
    // Use std::cout << "[Output] " << "Tree have been written to " << filename << " in pre-order." << std::endl;
}
