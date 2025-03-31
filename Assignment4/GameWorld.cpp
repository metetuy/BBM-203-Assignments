#include "GameWorld.h"

GameWorld::GameWorld() : mapTree(), shaperTree() {}

void GameWorld::initializeGame(std::vector<Isle *> places, std::vector<RealmShaper *> players)
{
    shaperTree.initializeTree(players);
    mapTree.initializeMap(places);
}

Map &GameWorld::getMapTree()
{
    return mapTree;
}
ShaperTree &GameWorld::getShaperTree()
{
    return shaperTree;
}

bool GameWorld::hasAccess(RealmShaper *realmShaper, Isle *isle)
{
    bool hasAccess = false;
    /*

    // TODO: Check if the realmShaper has access to explore the isle
    if (realmShaper == nullptr)
    {

        std::cout << "[Access Control] " << "RealmShaper not found!" << std::endl;
    }
    int playerDepth = shaperTree.getDepth(realmShaper);
    int totalShaperDepth = shaperTree.getDepth();
    int totalMapDepth = mapTree.getDepth();
    // Get necessary depth values
    int maxDepthAccess = mapTree.calculateMinMapDepthAccess(playerDepth, totalShaperDepth, totalMapDepth);

    int isleDepth = mapTree.getIsleDepth(isle);

    if (isleDepth <= maxDepthAccess)
    {
        hasAccess = true;
    }

    */
    return hasAccess;
}

void GameWorld::exploreArea(RealmShaper *realmShaper, Isle *isle)
{
    /*
    // TODO:
    // Check if realmShaper has access
    if (!hasAccess(realmShaper, isle))
    {
        std::cout << "[Explore Area] " << realmShaper->getName() << " does not have access to explore area " << *isle << std::endl;
        return;
    }
    // Use // std::cout << "[Explore Area] " << realmShaper->getName() << " does not have access to explore area " << *isle << std::endl;
    // If realmShaper has access
    if (hasAccess(realmShaper, isle))
    {
        std::cout << "[Explore Area] " << realmShaper->getName() << " visited " << isle->getName() << std::endl;
        // Visit isle,
        // collect item,
        Item item = isle->getItem();
        realmShaper->collectItem(item);
        std::cout << "[Energy] " << realmShaper->getName() << "'s new energy level is " << realmShaper->getEnergyLevel() << std::endl;
        // check overcrowding for Isle,
        bool isOvercrowded = isle->getShaperCount();

        if (isOvercrowded)
        {
            std::cout << "[Owercrowding] " << isle->getName() << " self-destructed, it will be removed from the map" << std::endl;
            mapTree.remove(isle);
        }
        */
}
// delete Isle if necessary

// Use // std::cout << "[Explore Area] " << realmShaper->getName() << " visited " << isle->getName() << std::endl;
// Use // std::cout << "[Energy] " << realmShaper->getName() << "'s new energy level is " << realmShaper->getEnergyLevel() << std::endl;
// Use // std::cout << "[Owercrowding] " << isle->getName() << " self-destructed, it will be removed from the map" << std::endl;

// You will need to implement a mechanism to keep track of how many realm shapers are at an Isle at the same time
// There are more than one ways to do this, so it has been left completely to you
// Use shaperCount, but that alone will not be enough,
// you will likely need to add attributes that are not currently defined
// to RealmShaper or Isle or other classes depending on your implementation

void GameWorld::craft(RealmShaper *shaper, const std::string &isleName)
{
    /*
    // TODO: Check energy and craft new isle if possible
    std::string shaperName = shaper->getName();
    int shaperEnergyLevel = shaper->getEnergyLevel();
    if (shaper->hasEnoughEnergy())
    {
        std::cout << "[Energy] " << shaperName << " has enough energy points: " << shaperEnergyLevel << std::endl;
        Isle *newIsle = new Isle(isleName);
        mapTree.insert(newIsle);
        std::cout << "[Craft] " << shaperName << " crafted new Isle " << isleName << std::endl;
    }
    else
    {
        std::cout << "[Energy] " << shaperName << " does not have enough energy points: " << shaperEnergyLevel << std::endl;
    }
    // Use std::cout << "[Energy] " << shaperName << " has enough energy points: " << shaperEnergyLevel << std::endl;
    // Use std::cout << "[Craft] " << shaperName << " crafted new Isle " << isleName << std::endl;
    // Use std::cout << "[Energy] " << shaperName << " does not have enough energy points: " << shaperEnergyLevel << std::endl;
    */
}

void GameWorld::displayGameState()
{

    mapTree.displayMap();
    shaperTree.displayTree();
}

// TODO: Implement functions to read and parse Access and Duel logs

void GameWorld::processGameEvents(const std::string &accessLogs, const std::string &duelLogs)
{
    /*
    // TODO:
    // Read logs
    std::ifstream accessFile(accessLogs);
    std::ifstream duelFile(duelLogs);

    std::string accessLine;
    std::string duelLine;

    // For every 5 access, 1 duel happens
    int accessCount = 0;
    // If there are still duel logs left after every access happens duels happens one after other
    while (std::getline(accessFile, accessLine))
    {
        std::istringstream acs(accessLine);
        std::string shaperName;
        std::string isleName;

        if (acs >> shaperName >> isleName)
        {
            RealmShaper *shaper = shaperTree.findPlayer(shaperName);
            Isle *isle = mapTree.findIsle(isleName);
            if (shaper && isle)
            {
                exploreArea(shaper, isle);
                accessCount++;
                if (accessCount % 5 == 0 && std::getline(duelFile, duelLine))
                {
                    std::istringstream dss(accessLine);
                    std::string challengerName;
                    std::string parentName;

                    bool result;

                    if (dss >> challengerName >> parentName >> result)
                    {
                        RealmShaper *challenger = shaperTree.findPlayer(challengerName);
                        RealmShaper *parent = shaperTree.findPlayer(parentName);
                        if (challenger && parent)
                        {
                            shaperTree.duel(challenger, result);
                        }
                    }
                }
            }
        }
    }
    // Process remaining duels
    while (std::getline(duelFile, duelLine))
    {
        std::istringstream duelStream(duelLine);
        std::string challengerName, parentName;
        bool result;
        if (duelStream >> challengerName >> parentName >> result)
        {
            RealmShaper *challenger = shaperTree.findPlayer(challengerName);
            RealmShaper *parent = shaperTree.findPlayer(parentName);
            if (challenger && parent)
            {
                shaperTree.duel(challenger, result);
            }
        }
    }
    // This function should call exploreArea and craft functions

    */
    displayGameState();
}

void GameWorld::saveGameState(const std::string &currentIsles, const std::string &currentWorld, const std::string &currentShapers, const std::string &currentPlayerTree)
{
    mapTree.writeIslesToFile(currentIsles);
    mapTree.writeToFile(currentWorld);
    shaperTree.writeToFile(currentPlayerTree);
    shaperTree.writeShapersToFile(currentShapers);
}