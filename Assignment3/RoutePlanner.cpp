#include "RoutePlanner.h"
#include <iostream>
#include <fstream>

// Array to help you out with name of the cities in order
const std::string cities[81] = {
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik",
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne",
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta",
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya",
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya",
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat",
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir",
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce"};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string &distance_data, const std::string &priority_data, const std::string &restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0)
{

    // Load map data from file
    map.loadDistanceData(distance_data);

    // Mark all provinces as unvisited initially
    map.resetVisited();

    // Load priority provinces
    loadPriorityProvinces(priority_data);

    // Load restricted provinces
    loadWeatherRestrictedProvinces(restricted_data);
}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;
    int count = 0;
    while (getline(file, line))
    {
        int o = line.find('(');
        int c = line.find(')');
        int priorityProvinceIndice;

        // Check if the line contains parenthesis
        if (o != std::string::npos && c != std::string::npos && o < c)
        {
            // Extract the number
            std::string number = line.substr(o + 1, c - o - 1);
            priorityProvinceIndice = std::stoi(number);
        }
        else
        {
            // If no parenthesis
            priorityProvinceIndice = std::stoi(line);
        }

        // Store the province ID
        priorityProvinces[count] = priorityProvinceIndice;

        count++;
    }
    numPriorityProvinces = count;
}

// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string &filename)
{

    std::ifstream file(filename);
    std::string line;
    int count = 0;
    while (getline(file, line))
    {
        int o = line.find('(');
        int c = line.find(')');
        int weatherRestrictedProvinceIndice;

        if (o != std::string::npos && c != std::string::npos && o < c)
        {
            // Extract the number between the parenthesis
            std::string number = line.substr(o + 1, c - o - 1);
            weatherRestrictedProvinceIndice = std::stoi(number);
        }
        else
        {
            weatherRestrictedProvinceIndice = std::stoi(line);
        }

        weatherRestrictedProvinces[count] = weatherRestrictedProvinceIndice;

        count++;
    }
    numWeatherRestrictedProvinces = count;
}

// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const
{
    for (int i = 0; i < numPriorityProvinces; i++)
    {

        if (priorityProvinces[i] == province)
        {
            return true;
        }
    }
    return false;
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const
{
    for (int i = 0; i < numWeatherRestrictedProvinces; i++)
    {
        if (weatherRestrictedProvinces[i] == province)
            return true;
    }
    return false;
}

void RoutePlanner::exploreRoute(int startingCity)
{
    // Push the starting city to the stack
    stack.push(startingCity);
    map.markAsVisited(startingCity);

    // Add it to the route vector
    route.push_back(startingCity);

    // if exploration is not complete always start exploring from top of the stack
    while (!isExplorationComplete())
    {
        exploreFromProvince(stack.peek());
    }
}

void RoutePlanner::exploreFromProvince(int province)
{
    // For each current province on the journey, enqueue all reachable, unvisited neighboring provinces.
    enqueueNeighbors(province);

    while (!queue.isEmpty())
    {
        int nextProvince = queue.dequeue();

        if (map.isVisited(nextProvince))
        {
            continue;
        }

        if (isWeatherRestricted(nextProvince))
        {
            std::cout << "Province " << cities[nextProvince] << " is weather-restricted. Skipping." << std::endl;
            continue;
        }

        // Recurse to the next province
        exploreRoute(nextProvince);
        return;
    }

    backtrack();
}

void RoutePlanner::backtrack()
{
    if (stack.isEmpty())
    {
        return;
    }

    // Pop the current province to continue from the previous province
    int currentProvince = stack.pop();

    // If current province was the last one return
    if (stack.isEmpty())
    {
        return;
    }

    // Get the previous province from the stack
    int prevProvince = stack.peek();
}

void RoutePlanner::enqueueNeighbors(int province)
{

    for (int provinceB = 0; provinceB < 81; provinceB++)
    {
        // Queue the neighbors
        if (map.isWithinRange(province, provinceB, maxDistance) && !map.isVisited(provinceB))
        {
            if (isPriorityProvince(provinceB))
            {
                queue.enqueuePriority(provinceB);
            }
            else
            {
                queue.enqueue(provinceB);
            }
        }
    }
}

bool RoutePlanner::isExplorationComplete() const
{
    // if there are no neighbors and backtracking is complete then the explortation is complete
    return stack.isEmpty() && queue.isEmpty();
}

void RoutePlanner::displayResults() const
{
    int calculatedDistance = 0;
    for (int i = 0; i < route.size() - 1; i++)
    {
        int distance = map.getDistance(route[i], route[i + 1]);
        if (distance != -1)
        { // Ensure distance is valid
            calculatedDistance += distance;
        }
    }

    std::cout << "Journey Completed!" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Total Number of Provinces Visited: " << map.countVisitedProvinces() << std::endl;
    std::cout << "Total Distance Covered: " << calculatedDistance << " km" << std::endl;

    // Display the route in the order it was visited
    std::cout << "Route Taken: ";
    for (int i = 0; i < route.size(); i++)
    {
        std::cout << cities[route[i]];
        if (i != route.size() - 1)
        {
            std::cout << " -> ";
        }
        else
        {
            std::cout << " -> End";
        }
    }
    std::cout << std::endl;

    // Display priority province summary
    std::cout << "Priority Provinces Status:" << std::endl;
    int priorityVisited = 0;
    for (int i = 0; i < numPriorityProvinces; i++)
    {
        if (map.isVisited(priorityProvinces[i]))
        {
            std::cout << "- " << cities[priorityProvinces[i]] << " (Visited)" << std::endl;
            priorityVisited++;
        }
        else
        {
            std::cout << "- " << cities[priorityProvinces[i]] << " (Not Visited)" << std::endl;
        }
    }

    std::cout << "Total Priority Provinces Visited: " << priorityVisited << " out of " << numPriorityProvinces << std::endl;

    if (priorityVisited == numPriorityProvinces)
    {
        std::cout << "Success: All priority provinces were visited." << std::endl;
    }
    else
    {
        std::cout << "Warning: Not all priority provinces were visited." << std::endl;
    }
}
