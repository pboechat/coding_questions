/* A child is running up a staircase with n steps and can hop either 1 step, 2 steps, or 3 steps
at a time. Implement a method to count how many possible ways the child can run up the stairs */

#include <iostream>
#include <array>
#include <memory>
#include <deque>
#include <vector>
#include <cmath>

template <size_t N>
struct Node
{
    static const size_t C = N;
    size_t hops;
    std::array<std::shared_ptr<Node>, _C> children;

    Node() : hops(0) {}
    Node(size_t hops) : hops(hops) {}
};

template <size_t C>
void makeDecisionTree(std::shared_ptr<Node<C>> &node, size_t hops, size_t missingSteps, std::vector<std::array<std::shared_ptr<Node<C>>, C>> &missingStepsSubtrees)
{
    node = std::make_shared<Node<C>>(hops);
    for (size_t i = 0; i < std::min(missingSteps, C); ++i)
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

template <size_t C>
void makeDecisionTree(std::shared_ptr<Node<C>> &root, size_t step)
{
    std::vector<std::array<std::shared_ptr<Node<C>>, C>> missingStepsSubtrees;
    missingStepsSubtrees.resize(step + 1);
    makeDecisionTree(root, 0, step, missingStepsSubtrees);
}

template <size_t C>
struct Visit
{
    const Node<C> *node;
    size_t depth;
};

template <size_t C, typename Visitor>
bool inOrderDfs(const std::shared_ptr<Node<C>> &node, Visitor visitor, size_t depth = 0)
{
    if (visitor(node, depth))
    {
        return true;
    }
    for (size_t i = 0; i < C; ++i)
    {
        auto &child = node->children[i];
        if (child != nullptr)
        {
            if (inOrderDfs(child, visitor, depth + 1))
            {
                return true;
            }
        }
    }
    return false;
}

template <size_t C>
size_t getMaxDepth(const std::shared_ptr<Node<C>> &root)
{
    size_t maxDepth = 0;
    inOrderDfs(root, [&maxDepth](const std::shared_ptr<Node<C>> &child, size_t depth) -> bool {
        if (depth > maxDepth)
        {
            maxDepth = depth;
        }
        return false;
    });
    return maxDepth;
}

template <size_t C>
void printTree(const std::shared_ptr<Node<C>> &root)
{
    std::deque<Visit<C>> bfs;
    bfs.push_back({root.get(), 0});
    auto maxDepth = getMaxDepth(root);
    size_t currDepth = 0;
    size_t prevIndent = 0;
    std::string spacing = "";
    while (!bfs.empty())
    {
        auto visit = bfs.front();
        bfs.pop_front();
        auto *node = visit.node;

        if (visit.depth > currDepth || currDepth == 0)
        {
            std::cout << std::endl;
            currDepth = visit.depth;
            auto currIndent = std::pow(C, maxDepth - currDepth) - 1;
            std::cout << std::string(currIndent, ' ');
            if (prevIndent > 0)
                spacing = std::string(prevIndent - currIndent - 1, ' ');
            prevIndent = currIndent;
        }
        std::cout << node->hops << spacing;
        for (size_t i = 0; i < C; ++i)
        {
            auto &child = node->children[i];
            if (child != nullptr)
            {
                bfs.push_back({child.get(), visit.depth + 1});
            }
        }
    }
}

using TernaryNode = Node<3>;

void test(size_t steps)
{
    std::cout << "steps: " << steps << std::endl;
    std::cout << "tree: " << std::endl;
    std::shared_ptr<TernaryNode> root;
    makeDecisionTree(root, steps);
    printTree(root);
    std::cout << std::endl;
}

int main()
{
    test(6);
    return 0;
}