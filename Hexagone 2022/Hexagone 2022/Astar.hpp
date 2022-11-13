#pragma once

#include "SFML/System/Vector3.hpp"
#include "Tilemap.hpp"

#include <vector>
#include <functional>
#include <set>

struct Node
{
    unsigned G, H;
    sf::Vector3i coordinates;
    Node* parent;

    Node(sf::Vector3i coord, Node* parent_ = nullptr)
    {
        coordinates = coord;
        parent = parent_;
    }

    unsigned GetScore()
    {
        return G + H;
    }
};

class Astar
{
    private:
        static unsigned Heuristic(sf::Vector3i a, sf::Vector3i b);
        static Node* FindNodeOnList(std::vector<Node*>& nodes, sf::Vector3i coordinates);

    public:
        static std::vector<sf::Vector3i> FindPath(sf::Vector3i source, sf::Vector3i target, Party party);
};
