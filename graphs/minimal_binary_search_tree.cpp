/* Given a sorted (increasing order) array with unique integer elements, write an algorithm
to create a binary search tree with minimal height */

#include <iostream>
#include <initializer_list>
#include <memory>
#include <deque>

struct Node {
    int value;
    std::unique_ptr<Node> left, right;

};

std::unique_ptr<Node> makeMinimalBinaryTree(const int* const input, size_t start, size_t end) {
    auto middle = start + (end - start) / 2;
    std::unique_ptr<Node> left, right;
    if (middle > start) {
        left = makeMinimalBinaryTree(input, start, middle);
    }
    if (middle + 1 < end) {
        right = makeMinimalBinaryTree(input, middle + 1, end);
    }
    return std::unique_ptr<Node>(new Node{ input[middle], std::move(left), std::move(right) });
}

struct Visit {
    const Node* node;
    const size_t depth;

};

void printTree(const std::unique_ptr<Node>& root) {
    std::deque<Visit> bfs;
    bfs.emplace_back(Visit{ root.get(), 0 });
    size_t lastDepth = 0;
    while (!bfs.empty()) {
        auto visit = bfs.front();
        bfs.pop_front();
        if (visit.depth != lastDepth) {
            std::cout << std::endl;
            lastDepth = visit.depth;
        }
        std::cout << visit.node->value << " ";
        if (visit.node->left != nullptr)
            bfs.emplace_back(Visit{ visit.node->left.get(), visit.depth + 1 });
        if (visit.node->right != nullptr)
            bfs.emplace_back(Visit{ visit.node->right.get(), visit.depth + 1 });
    }
}

void test(const char* name, const std::initializer_list<int>& input) {
    auto root = makeMinimalBinaryTree(input.begin(), 0, input.size());
    std::cout << name << ": " << std::endl;
    printTree(root); 
    std::cout << std::endl;
}

int main() {
    test("one number", { 1 });
    test("two numbers", { 1, 2 });
    test("three numbers", { 1, 2, 3 });
    test(
        "twenty non sequential numbers", 
        { 
            1, 3, 8, 9, 11, 13, 15, 20, 23, 26,
            32, 35, 37, 38, 45, 46, 50, 62, 73
        }
    );
    return 0;
}