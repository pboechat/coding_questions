/* A child is running up a staircase with n steps and can hop either 1 step, 2 steps, or 3 steps
at a time. Implement a method to count how many possible ways the child can run up the stairs */

#include <iostream>
#include <array>
#include <memory>
#include <deque>
#include <vector>

struct Node
{
    size_t hops;
    std::array<std::shared_ptr<Node>, 3> children;

    Node() : hops(0) {}
    Node(size_t hops) : hops(hops) {}
};

struct Visit
{
    const Node *node;
    size_t depth;
};

void makeDecisionTree(std::shared_ptr<Node> &node, size_t hops, size_t missingSteps, std::vector<std::array<std::shared_ptr<Node>, 3>> &missingStepsSubtrees)
{
    node = std::make_shared<Node>(hops);
    for (size_t i = 0; i < std::min(missingSteps, 3ul); ++i)
    {
        auto newHops = i + 1;
        auto &child = missingStepsSubtrees[missingSteps][i];
        if (child == nullptr)
        {
            makeDecisionTree(child, newHops, missingSteps - newHops, missingStepsSubtrees);
        }
        node->children[i] = child;
    }
}

void makeDecisionTree(std::shared_ptr<Node> &root, size_t step)
{
    std::vector<std::array<std::shared_ptr<Node>, 3>> missingStepsSubtrees;
    missingStepsSubtrees.resize(step + 1);
    makeDecisionTree(root, 0, step, missingStepsSubtrees);
}

void printTree(const std::shared_ptr<Node> &root)
{
    std::deque<Visit> bfs;
    bfs.push_back({root.get(), 1});
    size_t lastSeenDepth = 0;
    while (!bfs.empty())
    {
        auto visit = bfs.front();
        bfs.pop_front();
        auto *node = visit.node;
        std::cout << node->hops;
        if (visit.depth != lastSeenDepth)
        {
            std::cout << std::endl;
            lastSeenDepth = visit.depth;
        }
        for (size_t i = 0; i < 3; ++i)
        {
            auto &child = node->children[i];
            if (child != nullptr)
            {
                bfs.push_back({child.get(), visit.depth + 1});
            }
        }
    }
}

void test(size_t steps)
{
    std::cout << "steps: " << steps << std::endl;
    std::cout << "tree: " << std::endl;
    std::shared_ptr<Node> root;
    makeDecisionTree(root, steps);
    printTree(root);
    std::cout << std::endl;
}

int main()
{
    test(6);
    return 0;
}