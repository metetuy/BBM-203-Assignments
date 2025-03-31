#include "Map.h"

Map::Map()
{
    // Initialize all distances to a value representing no direct connection
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            distanceMatrix[i][j] = -1; // No connection
        }
    }
    // Initialize all provinces as unvisited
    for (int i = 0; i < MAX_SIZE; i++)
    {
        visited[i] = false;
    }
}

// Loads distance data from a file and fills the distanceMatrix
void Map::loadDistanceData(const std::string &filename)
{
    // Read each line in the CSV file
    std::ifstream file(filename);
    std::string line;

    int row = 0;
    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string value;
        int col = 0;
        // Read each cell separated by a comma
        while (getline(iss, value, ','))
        {

            // Convert cell to an integer and store in distanceMatrix
            distanceMatrix[row][col] = std::stoi(value);
            col++;
        }
        row++;
    }
    file.close();
}

// Checks if the distance between two provinces is within the allowed maxDistance
bool Map::isWithinRange(int provinceA, int provinceB, int maxDistance) const
{
    if (distanceMatrix[provinceA][provinceB] <= maxDistance && distanceMatrix[provinceA][provinceB] != -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Marks a province as visited
void Map::markAsVisited(int province)
{
    visited[province] = true;
}

// Checks if a province has already been visited
bool Map::isVisited(int province) const
{
    if (province >= 0 && province < MAX_SIZE)
    {
        return visited[province];
    }
    else
    {
        return false;
    }
}

// Resets all provinces to unvisited
void Map::resetVisited()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        visited[i] = false;
    }
}

// Function to count the number of visited provinces
int Map::countVisitedProvinces() const
{
    int count = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (visited[i])
        {
            count++;
        }
    }
    return count;
}

// Function to get the distance between two provinces
int Map::getDistance(int provinceA, int provinceB) const
{
    return distanceMatrix[provinceA][provinceB];
}