/* You are given a list of projects and a list of dependencies (which is a list of pairs 
of projects, where the second project is dependent on the first project). All of a projects 
dependencies must be built before the project is. Find a build order that will allow the 
projects to be built. If there is no valid build order, return an error. */

#include <initializer_list>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <iostream>

struct Node 
{
    const char* value;
    std::vector<Node*> adjacencies;

};

template <typename V>
using NameMap = std::unordered_map<const char*, V>;

struct Graph
{
    std::vector<Node> nodes;

};

bool hasLoop(const Node& node, NameMap<bool> visitedNodes = {}) 
{
    auto it = visitedNodes.find(node.value);
    if (it != visitedNodes.end()) {
        return true;
    }
    visitedNodes.emplace(node.value, true);
    for (auto& adjacency : node.adjacencies) {
        if (hasLoop(*adjacency, visitedNodes)) {
            return true;
        }
    }
    return false;
}

void printGraph(const Node& node, NameMap<bool>& visitedNodes) {
    if (visitedNodes.find(node.value) != visitedNodes.end()) {
        return;
    }
    visitedNodes.emplace(node.value, true);
    for (auto& adjacency : node.adjacencies) {
        printGraph(*adjacency, visitedNodes);
    }
    std::cout << node.value;
}

void test(const char* name
    , const std::initializer_list<const char*>& projects
    , const std::initializer_list<std::pair<const char*, const char*>>& dependencies)
{
    std::cout << name << " = ";
    Graph graph;
    NameMap<Node*> nodeMap;
    NameMap<Node*> sourceMap;
    graph.nodes.reserve(projects.size());
    for (auto& project : projects) {
        graph.nodes.emplace_back(Node{ project });
        nodeMap.emplace(project, &graph.nodes.back());
        sourceMap.emplace(project, &graph.nodes.back());
    }
    for (auto& dependency : dependencies) {
        auto* src = nodeMap.find(dependency.second)->second;
        auto* dst = nodeMap.find(dependency.first)->second;
        src->adjacencies.emplace_back(dst);
        auto it = sourceMap.find(dependency.first);
        if (it != sourceMap.end())
            sourceMap.erase(it);
    }
    for (auto& node : graph.nodes) {
        if (hasLoop(node)) {
            std::cout << "no valid order" << std::endl;
            return;
        }
    }
    for (auto& entry : sourceMap) {
        NameMap<bool> visitedNodes;
        printGraph(*entry.second, visitedNodes);
    }
    std::cout << std::endl;
}

int main()
{
    test(
        "book example",
        { "a", "b", "c", "d", "e", "f" }, 
        { 
            { "a", "d" }, 
            { "f", "b" }, 
            { "b", "d" }, 
            { "f", "a" }, 
            { "d", "c" }, 
        }
    );
    test(
        "cyclic dependency",
        { "a", "b", "c" },
        { 
            { "b", "a" },
            { "c", "b" },
            { "a", "c" },
        }
    );
    return 0;
}