#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include "raylib.h"

// decided to use a struct instead of a class due to the default public variables and members
struct Node
{
    int x, y;
    int costG = 0;
    int costH = 0;
    int costF = 0;

    // this is going to trace our path by pointing back to previous tile (parent)
    // basically path gets created backwards
    Node* parent = nullptr;

    Node(int _x, int _y) : 
        x(_x), // sets x value to x val from inst.
        y(_y) // same for y
    {}

    void calculateFCost()
    {
        // f = g + h 
        costF = costG = costH;
    }

    // this allows us to compare two nodes, given that c++ wouldn't know what to do with them otherwise
    bool operator == (const Node& other) const
    {
        return x == other.x && y == other.y;
    }

};

// functions for pathfinding system

int Heuristic(int x1, int y1, int x2, int y2); 
bool IsWalkable(int x, int y);
std::vector<Node> AStarSearch(int startX, int startY, int endX, int endY);

#endif