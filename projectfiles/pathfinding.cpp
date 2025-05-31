#include "pathfinding.h"

// calculating the manhattan distance heuristic
int Heuristic(int x1, int y1, int x2, int y2)
{
    int heuristic = abs(x1 - x2) + abs(y1 - y2);
    return heuristic;
}

// check if the position (coordinates) is available and walkable
bool IsWalkable(int x, int y)
{
    bool walkableX = x >= 0 && x < GRID_SIZE;
    bool walkableY = y >= 0 && y < GRID_SIZE;
    bool towerPlaced = gridMap[y][x] == 0;

    return walkableX && walkableY && towerPlaced;
    // if it returns true, it's walkable
    // if it returns false, it's not

}

// this is the *meat* of the a star algo
// it looks for a path from the starting position (startX, startY) to the goal position (endX, endY)
// returns the path of Nodes for the enemy to walk through :) 
std::vector<Node> AStarSearch(int startX, int startY, int endX, int endY)
{
    std::vector<Node> opened; // "open" tiles to explore
    std::vector<Node> closed; // tiles that have already been explored

    Node start(startX, startY); // start pos
    Node end(endX, endY); // goal pos (end)

    // start the exploration from the start pos :)
    opened.push_back(start);

    // loops while there are still nodes to explore
    while (!opened.empty())
    {
        // sorts from smallest F val to largest
        std::sort(opened.begin(),opened.end(), [](Node& a, Node& b)
        {
            return a.costF < b.costF || (a.costF == b.costF && a.costH < b.costH);
        });

        // processes node
        Node current = opened.front();
        opened.erase(opened.begin());
        closed.push_back(current);

        // if reached the end goal
        if (current == end)
        {
            // this just traces back the path (as mentioned earlier in pathfinding.h)
            std::vector<Node> path;
            Node* step = new Node(current);

            while (step != nullptr)
            {
                path.push_back(*step);
                step = step ->parent;
            }

            // puts the list back in order for the enemy to trace pathhh
            std::reverse(path.begin(), path.end());

            return path;
        }

        std::cout << "Checking node at (" << current.x << "," << current.y << ")\n";
        std::cout << "gridMap[" << current.y << "][" << current.x << "] = " << gridMap[current.y][current.x] << "\n";

        // this checks all 4 directions
        std::vector<std::pair<int, int>> directions =
        {
            {0, -1}, // up
            {0, 1}, // down
            {-1, 0}, // left
            {1, 0} // right
        };

        // will repeat following proccess for each neighbor tile (of current)
        for (auto& dir : directions)
        {
            int newX = current.x + dir.first;
            int newY = current.y + dir.second;

            // checks if said neighbor is available 
            // (as of rn that "neighbor" tile is just two positions, not a real node)
            if (!IsWalkable(newX, newY))
            {
                continue;
            }

            // here it becomes a node
            Node neighbor(newX, newY);

            // if tile already closed then SKIP !!
            if (std::find(closed.begin(), closed.end(), neighbor) != closed.end())
            {
                continue;
            }

            // calculates possible g cost 
            int tentativeG = current.costG + 1;

            // find the neighbor in the opened list
            auto openNode = std::find(opened.begin(), opened.end(), neighbor);

            // if it's not in the list, then...
            if (openNode == opened.end())
            {
                // do all this
                neighbor.costG = tentativeG;
                neighbor.costH = Heuristic(newX, newY, endX, endY);
                neighbor.calculateFCost();
                neighbor.parent = new Node(current); // this will keep track of the path
                opened.push_back(neighbor);
            }

            // if it is, and a* found a better path, then replace the old stuff
            else if (tentativeG < openNode -> costG)
            {
                openNode -> costG = tentativeG;
                openNode -> calculateFCost();
                openNode -> parent = new Node(current); // rebuilds path
            }
        }
    }

    // no path found :(
    return {};
}
