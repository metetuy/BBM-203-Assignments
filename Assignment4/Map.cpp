#include "Map.h"

Map::Map()
{
    this->root = nullptr;
}
Map::~Map()
{
    // TODO: Free any dynamically allocated memory if necessary
    if (root == nullptr)
    {
        return;
    }

    std::stack<MapNode *> nodeStack;
    MapNode *current = root;
    MapNode *lastVisited = nullptr;

    while (!nodeStack.empty() || current != nullptr)
    {
        if (current != nullptr)
        {
            nodeStack.push(current);
            current = current->left; // Go to the left child
        }
        else
        {
            MapNode *peekNode = nodeStack.top();
            // If the right child exists and has not been visited, go right
            if (peekNode->right != nullptr && lastVisited != peekNode->right)
            {
                current = peekNode->right;
            }
            else
            {
                // Visit this node (delete it)
                nodeStack.pop();
                delete peekNode;
                lastVisited = peekNode;
            }
        }
    }
}

void Map::initializeMap(std::vector<Isle *> isles)
{
    // TODO: Insert innitial isles to the tree
    for (Isle *isle : isles)
    {
        insert(isle);
    }
    // Then populate with Goldium and Einstainium items
    populateWithItems();
}

MapNode *Map::rotateLeft(MapNode *current)
{
    if (current == nullptr || current->right == nullptr)
    {
        std::cerr << "[Left Rotation] Called on invalid node!" << std::endl;
        return current;
    }

    MapNode *newRoot = current->right;
    MapNode *temp = newRoot->left;

    newRoot->left = current;
    current->right = temp;

    // Update heights
    current->height = std::max(height(current->left), height(current->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;

    rebalanceCount++; // Increment rebalancing counter
    if (rebalanceCount % 3 == 0)
    {
        populateWithItems();
        dropItemBFS();
    }

    return newRoot;
}

MapNode *Map::rotateRight(MapNode *current)
{
    if (current == nullptr || current->left == nullptr)
    {
        std::cerr << "[Right Rotation] Called on invalid node!" << std::endl;
        return current;
    }

    MapNode *newRoot = current->left;
    MapNode *temp = newRoot->right;

    newRoot->right = current;
    current->left = temp;

    // Update heights
    if (current != nullptr)
        current->height = std::max(height(current->left), height(current->right)) + 1;
    if (current != nullptr)
        newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;

    rebalanceCount++; // Increment rebalancing counter
    if (rebalanceCount % 3 == 0)
    {

        populateWithItems();
        dropItemBFS();
    }

    return newRoot;
}

int Map::calculateMinMapDepthAccess(int playerDepth, int totalShaperTreeHeight, int totalMapDepth)
{
    return (int)totalMapDepth * ((double)playerDepth / totalShaperTreeHeight);
}

int Map::height(MapNode *node)
{
    // TODO: Return height of the node
    if (node != nullptr)
    {
        return node->height;
    }
    return 0;
}

MapNode *Map::insert(MapNode *node, Isle *isle)
{
    MapNode *newNode = nullptr;

    if (isle == nullptr)
    {
        std::cerr << "[Insert Error] Isle is null!" << std::endl;
        return newNode;
    }

    if (node == nullptr)
    {
        newNode = new MapNode(isle);
        if (newNode == nullptr)
        {
            std::cerr << "[Insert Error] Memory allocation for new node failed!" << std::endl;
        }
        return newNode;
    }

    if (*isle < *(node->isle))
    {
        newNode = insert(node->left, isle);
        node->left = newNode;
    }
    else if (*isle > *(node->isle))
    {
        newNode = insert(node->right, isle);
        node->right = newNode;
    }
    else
    {
        return newNode;
    }

    // Update height: max(left, right) + 1
    node->height = std::max(height(node->left), height(node->right)) + 1;

    // Check for imbalance
    int balance = height(node->left) - height(node->right);

    // Perform rotations if needed
    if (balance > 1 && *isle < *(node->left->isle))
    {
        return rotateRight(node);
    }
    if (balance < -1 && *isle > *(node->right->isle))
    {
        return rotateLeft(node);
    }
    if (balance > 1 && *isle > *(node->left->isle))
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && *isle < *(node->right->isle))
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void Map::insert(Isle *isle)
{
    if (isle == nullptr)
    {
        std::cerr << "[Insert Error] Cannot insert a null Isle!" << std::endl;
        return;
    }

    if (findIsle(*(isle)) != nullptr) // Check for duplicates
    {
        std::cerr << "[Insert Error] Duplicate Isle: " << isle->getName() << " already exists!" << std::endl;
        return;
    }

    try
    {
        MapNode *prevRoot = root;
        root = insert(root, isle);

        if (root == nullptr)
        {
            std::cerr << "[Insert Error] Insertion failed for Isle: " << isle->getName() << std::endl;
        }
        else if (root == prevRoot)
        {
            std::cerr << "[Insert Debug] Isle " << isle->getName() << " inserted, root unchanged." << std::endl;
        }
        else
        {
            std::cerr << "[Insert Success] Isle " << isle->getName() << " inserted successfully." << std::endl;
        }
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "[Insert Error] Memory allocation failed: " << e.what() << std::endl;
    }
}
// you might need to insert some checks / functions here depending on your implementation

MapNode *Map::remove(MapNode *node, Isle *isle)
{
    // TODO: Recursively delete isle from the tree
    // Will be called if there is overcrowding
    // returns node
    

    // Use std::cout << "[Remove] " << "Tree is Empty" << std::endl;

    return node;
}

void Map::remove(Isle *isle)
{
    root = remove((root), isle);
    // you might need to insert some checks / functions here depending on your implementation
}

void Map::preOrderItemDrop(MapNode *current, int &count)
{
    // TODO: Drop EINSTEINIUM according to rules
    if (current == nullptr)
    {
        return;
    }

    count++;
    // Every fifth Isle (according to Pre-Order Traversal) is populated with ITEM::EINSTEINIUM.
    if (count % 5 == 0)
    {
        current->isle->setItem(EINSTEINIUM);
        std::cout << "[Item Drop] " << "EINSTEINIUM dropped on Isle: " << current->isle->getName() << std::endl;
    }
    preOrderItemDrop(current->left, count);  // left
    preOrderItemDrop(current->right, count); // right
}

// to Display the values by Post Order Method .. left - right - node
void Map::postOrderItemDrop(MapNode *current, int &count)
{
    // Every third Isle (according to Post-Order Traversal) is populated with ITEM::GOLDIUM.
    if (current == nullptr)
    {
        return;
    }
    postOrderItemDrop(current->left, count);  // left
    postOrderItemDrop(current->right, count); // right
    count++;
    if (count % 3 == 0)
    {
        current->isle->setItem(GOLDIUM);
        std::cout << "[Item Drop] " << "GOLDIUM dropped on Isle: " << current->isle->getName() << std::endl;
    }
}

// Finding the first empty isle by BFS traversal
MapNode *Map::findFirstEmptyIsle(MapNode *node)
{
    // TODO: Find first Isle with no item
    if (node == nullptr)
    {
        return nullptr;
    }

    std::queue<MapNode *> q;

    q.push(node);

    while (!q.empty())
    {
        MapNode *newNode = q.front();
        q.pop();
        if (newNode->isle->getItem() == EMPTY)
        {
            return newNode;
        }
        if (newNode->left != nullptr)
        {
            q.push(newNode->left);
        }

        if (newNode->right != nullptr)
        {
            q.push(newNode->right);
        }
    }
    return nullptr;
}

void Map::dropItemBFS()
{
    /*Every 3rd re-balancing of the AVL tree causes the rare and most valuable ITEM::AMAZONITE to
   drop to first Isle that has no existing item. This helps more valuable items to stay in the lower
   depths.*/
    // TODO: Drop AMAZONITE according to rules

    MapNode *targetNode = findFirstEmptyIsle(root);

    if (targetNode != nullptr)
    {
        targetNode->isle->setItem(AMAZONITE);
        std::cout << "[BFS Drop] " << "AMAZONITE dropped on Isle: " << targetNode->isle->getName() << std::endl;
    }
    else
    {
        std::cout << "[BFS Drop] " << "No eligible Isle found for AMAZONITE drop." << std::endl;
    }
    // Use std::cout << "[BFS Drop] " << "AMAZONITE dropped on Isle: " << targetNode->isle->getName() << std::endl;
    // Use std::cout << "[BFS Drop] " << "No eligible Isle found for AMAZONITE drop." << std::endl;
}

void Map::displayMap()
{
    std::cout << "[World Map]" << std::endl;
    display(root, 0, 0);
}

int Map::getDepth(MapNode *node)
{
    if (root == nullptr || node == nullptr)
    {
        return -1; // Tree is empty or input node is invalid
    }

    std::stack<std::pair<MapNode *, int>> nodeStack; // Pair of node and depth
    nodeStack.push({root, 0});                       // Start from the root

    while (!nodeStack.empty())
    {
        MapNode *current = nodeStack.top().first;
        int currentDepth = nodeStack.top().second;
        nodeStack.pop();

        if (current == node)
        {
            return currentDepth; // Found the node, return its depth
        }

        if (current->right != nullptr)
        {
            nodeStack.push({current->right, currentDepth + 1});
        }
        if (current->left != nullptr)
        {
            nodeStack.push({current->left, currentDepth + 1});
        }
    }

    return -1; // Node not found in the tree
}

// Function to calculate the depth of a specific node in the AVL tree
int Map::getIsleDepth(Isle *isle)
{
    MapNode *current = root;

    if (isle == nullptr)
    {
        return -1;
    }
    int depth = 0;

    while (current != nullptr)
    {
        if (*(current->isle) == *isle)
        {
            return depth;
        }

        if (*isle < *(current->isle))
        {
            current = current->left;
        }
        else if (*isle > *(current->isle))
        {
            current = current->right;
        }

        depth++;
    }

    return -1;
}

int Map::getDepth()
{
    // TODO: Return max|total depth of tree
    std::queue<MapNode *> nodesInLevel;
    int depth = 0;
    int nodeCount = 0;    // Calculate  number of nodes in a level.
    MapNode *currentNode; // Pointer to store the address of a
                          // node in the current level.
    if (root == NULL)
    {
        return 0;
    }
    nodesInLevel.push(root);
    while (!nodesInLevel.empty())
    {
        depth++;
        nodeCount = nodesInLevel.size();
        while (nodeCount--)
        {
            currentNode = nodesInLevel.front();

            // Check if the current nodes has left child and
            // insert it in the queue.

            if (currentNode->left != NULL)
            {
                nodesInLevel.push(currentNode->left);
            }

            // Check if the current nodes has right child
            // and insert it in the queue.
            if (currentNode->right != NULL)
            {
                nodesInLevel.push(currentNode->right);
            }

            // Once the children of the current node are
            // inserted. Delete the current node.

            nodesInLevel.pop();
        }
    }
    return depth - 1;
}

void Map::populateWithItems()
{
    // TODO: Distribute fist GOLDIUM than EINSTEINIUM
    int count = 0;

    postOrderItemDrop(root, count);

    count = 0;

    preOrderItemDrop(root, count);
}

Isle *Map::findIsle(Isle isle)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    std::queue<MapNode *> q;

    q.push(root);

    while (!q.empty())
    {
        MapNode *newNode = q.front();
        q.pop();
        if (*(newNode->isle) == isle)
        {
            return newNode->isle;
        }
        if (newNode->left != nullptr)
        {
            q.push(newNode->left);
        }

        if (newNode->right != nullptr)
        {
            q.push(newNode->right);
        }
    }
    return nullptr;
}

Isle *Map::findIsle(std::string name)
{
    // TODO: Find isle by name
    if (root == nullptr)
    {
        return nullptr;
    }

    std::queue<MapNode *> q;

    q.push(root);

    while (!q.empty())
    {
        MapNode *newNode = q.front();
        q.pop();
        if (newNode->isle->getName() == name)
        {
            return newNode->isle;
        }
        if (newNode->left != nullptr)
        {
            q.push(newNode->left);
        }

        if (newNode->right != nullptr)
        {
            q.push(newNode->right);
        }
    }
    return nullptr;
}

MapNode *Map::findNode(Isle isle)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    std::queue<MapNode *> q;

    q.push(root);

    while (!q.empty())
    {
        MapNode *newNode = q.front();
        q.pop();
        if (*(newNode->isle) == isle)
        {
            return newNode;
        }
        if (newNode->left != nullptr)
        {
            q.push(newNode->left);
        }

        if (newNode->right != nullptr)
        {
            q.push(newNode->right);
        }
    }
    return nullptr;
}

MapNode *Map::findNode(std::string name)
{

    return nullptr;
}

void Map::display(MapNode *current, int depth, int state)
{
    // SOURCE:

    if (current->left)
        display(current->left, depth + 1, 1);

    for (int i = 0; i < depth; i++)
        printf("     ");

    if (state == 1) // left
        printf("   ┌───");
    else if (state == 2) // right
        printf("   └───");

    std::cout << "[" << *current->isle << "] - (" << current->height << ")\n"
              << std::endl;

    if (current->right)
        display(current->right, depth + 1, 2);
}

void Map::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output level by level
    std::ofstream outFile(filename);

    writeLevelOrder(root, outFile);
    outFile.close();
}

void Map::writeIslesToFile(const std::string &filename)
{
    // TODO: Write Isles to output file in alphabetical order
    std::ofstream outFile(filename);

    std::vector<Isle *> isles;
    collectIsles(root, isles);

    std::sort(isles.begin(), isles.end(), [](Isle *a, Isle *b)
              {
                  return a->getName() < b->getName(); // Compare Isles by their name
              });

    for (Isle *isle : isles)
    {
        outFile << isle->getName() << std::endl;
    }
    std::cout << "[Output] " << "Isles have been written to " << filename << " in in alphabetical order." << std::endl;
    outFile.close();
    // Use std::cout << "[Output] " << "Isles have been written to " << filename << " in in alphabetical order." << std::endl;
}