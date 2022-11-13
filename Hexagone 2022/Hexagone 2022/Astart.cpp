#include "AStar.hpp"

#include <algorithm>
#include <map>
#include <math.h>

unsigned Astar::Heuristic(sf::Vector3i a, sf::Vector3i b)
{
    sf::Vector3i c = b - a;

    return c.x * c.x + c.y * c.y + c.z * c.z;
}

std::vector<sf::Vector3i> Astar::FindPath(const sf::Vector3i source, sf::Vector3i target, Party party)
{
    auto tiles = Tilemap::Tiles();

    Node* current = nullptr;
    std::vector<Node*> openSet, closedSet;

    openSet.push_back(new Node(source));

    while (!openSet.empty()) {
        auto current_it = openSet.begin();
        current = *current_it;

        for (auto it = openSet.begin(); it != openSet.end(); it++) {
            auto node = *it;
            if (node->GetScore() <= current->GetScore()) {
                current = node;
                current_it = it;
            }
        }

        if (Tilemap::GetTile(current->coordinates)->GetParty() == party)
            break;

        closedSet.push_back(current);
        openSet.erase(current_it);

        for (auto neighbour : tiles[Tilemap::Vector3ToArray(current->coordinates)]->SurroundingTiles())
        {
            if (neighbour->Obstacle() || neighbour->GetParty() != party || FindNodeOnList(closedSet, neighbour->Coordinates()))
                continue;

            unsigned totalCost = current->G + 10;

            Node* successor = FindNodeOnList(openSet, neighbour->Coordinates());
            if (successor == nullptr) {
                successor = new Node(neighbour->Coordinates(), current);
                successor->G = totalCost;
                successor->H = Heuristic(successor->coordinates, target);
                openSet.push_back(successor);
            }
            else if (totalCost < successor->G) {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }

    std::vector<sf::Vector3i> path;

    while (current != nullptr) {
        path.push_back(current->coordinates);
        current = current->parent;
    }

    path.pop_back();

    std::reverse(path.begin(), path.end());

    return path;
}

Node* Astar::FindNodeOnList(std::vector<Node*>& nodes, sf::Vector3i coordinates)
{
    for (auto node : nodes)
        if (node->coordinates == coordinates)
            return node;

    return nullptr;
}
