/* Given a directed graph and two nodes (S and E), design an algorithm to find out
whether there is a route from S to E */

#include <vector>
#include <iostream>
#include <unordered_map>
#include <initializer_list>
#include <stdexcept>
#include <deque>
#include <string>

struct Node
{
    const char* name;
    std::vector<Node*> adjacencies;
    bool visited;

};

using NodeMap = std::unordered_map<const char*, Node*>;

struct Graph
{
    std::vector<Node> nodes;

};

struct NodeDecl 
{
    const char* name;
    std::initializer_list<const char*> adjacencies;

};

void initializeGraph(Graph& graph
    , NodeMap& nodeMap
    , const std::initializer_list<NodeDecl>& nodeDeclrs) {
    graph.nodes.reserve(nodeDeclrs.size());    
    for (auto& nodeDeclr : nodeDeclrs) {
        graph.nodes.emplace_back(Node{ nodeDeclr.name, {}, false });
        if (nodeMap.insert({ nodeDeclr.name, &graph.nodes.back() }).first == nodeMap.end()) {
            throw std::runtime_error(std::string("duplicated node (node=") 
                + nodeDeclr.name + ")");
        }
    }
    for (auto& nodeDeclr : nodeDeclrs) {
        auto* node = nodeMap.find(nodeDeclr.name)->second;
        for (auto& adjacencyName : nodeDeclr.adjacencies) {
            auto it2 = nodeMap.find(adjacencyName);
            if (it2 == nodeMap.end()) {
                throw std::runtime_error(std::string("invalid adjacency (node=") 
                    + nodeDeclr.name + ", adjacency=" + adjacencyName + ")");
            }
            node->adjacencies.emplace_back(it2->second);
        }
    }
}

bool hasRoute(Node& s, Node& e) {
    std::deque<Node*> bfs;
    bfs.emplace_back(&s);
    bfs.emplace_back(&e);
    while (!bfs.empty()) {
        auto* node = bfs.front();
        bfs.pop_front();
        if (node->visited) {
            return true;
        }
        node->visited = true;
        for (auto* adjacency : node->adjacencies) {
            bfs.emplace_back(adjacency);
        }
    }
    return false;
}

void test(
    const char* name,
    const std::initializer_list<NodeDecl>& nodeDeclrs
    , const char* s
    , const char* e) {
    Graph graph;
    NodeMap nodeMap;
    initializeGraph(
        graph
        , nodeMap
        , nodeDeclrs
    );
    auto it1 = nodeMap.find(s);
    if (it1 == nodeMap.end()) {
        throw std::runtime_error(std::string("invalid node (node=") + s + ")");
    }
    auto it2 = nodeMap.find(e);
    if (it2 == nodeMap.end()) {
        throw std::runtime_error(std::string("invalid node (node=") + e + ")");
    }
    std::cout << name << " = " << hasRoute(*it1->second, *it2->second) << std::endl;
}

int main() {
    test(
        "short path",
        {
            { "a", { "b" } },
            { "b", { "c" } },
            { "c", { } },
            { "d", { "c" } },
        },
        "a",
        "d"
    );

    test(
        "no path",
        {
            { "a", { } },
            { "b", { } },
        },
        "a",
        "b"
    );

    test(
        "long path",
        {
            { "a", { "b", "c", "d" } },
            { "b", { "e", "f", "g" } },
            { "c", { "h", "i", "j" } },
            { "d", { "k", "l", "m" } },
            { "e", { } },
            { "f", { } },
            { "g", { } },
            { "h", { } },
            { "i", { } },
            { "j", { } },
            { "k", { } },
            { "l", { } },
            { "m", { } },
            { "n", { } },
            { "o", { } },
            { "p", { } },
            { "q", { } },
            { "r", { } },
            { "s", { "j" } },
            { "t", { } },
            { "u", { } },
            { "v", { } },
            { "x", { "n", "o", "p" } },
            { "w", { "q", "r", "s" } },
            { "y", { "t", "u", "v" } },
            { "z", { "x", "w", "y" } },
        },
        "a",
        "z"
    );

    return 0;
} 