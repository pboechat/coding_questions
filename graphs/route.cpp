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
    unsigned char visitors: 2;

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
        graph.nodes.emplace_back(Node{ nodeDeclr.name, {}, 0 });
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

struct Visit {
    Node* node;
    unsigned int visitor: 2;

};

bool hasRoute(Node& s, Node& e) {
    std::deque<Visit> bfs;
    bfs.emplace_back(Visit{ &s, 1 });
    bfs.emplace_back(Visit{ &e, 2 });
    while (!bfs.empty()) {
        auto visit = bfs.front();
        bfs.pop_front();
        auto* node = visit.node;
        if ((node->visitors & visit.visitor) != 0) {
            continue;
        }
        node->visitors |= visit.visitor;
        if (node->visitors == 3) {
            return true;
        }
        for (auto* adjacency : node->adjacencies) {
            bfs.emplace_back(Visit{ adjacency, visit.visitor });
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

    test(
        "no path with loop",
        { 
            { "a", { "b" } },
            { "b", { "c" } },
            { "c", { "a" } },
            { "d", { } },
        },
        "a",
        "d"
    );

    test(
        "path with loop",
        { 
            { "a", { "b" } },
            { "b", { "c" } },
            { "c", { "a" } },
            { "d", { "c" } },
            { "e", { "d" } },
            { "f", { "e" } },
        },
        "a",
        "f"
    );

    return 0;
} 