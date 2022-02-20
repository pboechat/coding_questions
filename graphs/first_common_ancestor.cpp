/* Design an algorithm and write code to find the first common ancestor of two nodes.
Avoid storing additional nodes in a data structure. NOTE: This is not necessarily a
binary search tree. */

#include <memory>
#include <iostream>
#include <cstring>

struct Node
{
    const char* value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(const char* value, std::unique_ptr<Node>&& left, std::unique_ptr<Node>&& right) : value(value), left(std::move(left)), right(std::move(right)) {}
    Node(const char* value) : value(value) {}

};

unsigned char findCommonAncestor(const std::unique_ptr<Node>& node, const char* p, const char* q, const char*& value) {
    unsigned int descendents = 0;
    if (node->left != nullptr) {
        auto leftDescendents = findCommonAncestor(node->left, p, q, value);
        if (leftDescendents == 3) {
            if (value == nullptr) {
                value = node->value;
            }
            return 3;
        }
        descendents |= leftDescendents;
    }
    if (node->right != nullptr) {
        auto rightDescendents = findCommonAncestor(node->right, p, q, value);
        if (rightDescendents == 3) {
            if (value == nullptr) {
                value = node->value;
            }
            return 3;
        }
        descendents |= rightDescendents;
    }
    if (descendents == 3) {
        value = node->value;
        return 3;
    }
    unsigned char current = descendents;
    if (strcmp(node->value, p) == 0) {
        current |= 1;
    }
    else if (strcmp(node->value, q) == 0) {
        current |= 2;
    }
    return current;
}

const char* findCommonAncestor(const std::unique_ptr<Node>& root, const char* p, const char* q) {
    const char* value = nullptr;
    if (findCommonAncestor(root, p, q, value) != 3) {
        return nullptr;
    }
    return value;
}

void test(const char* name, const std::unique_ptr<Node>& root, const char* p, const char* q) {
    std::cout << name << " = " << findCommonAncestor(root, p, q) << std::endl;
}

int main() {
    test(
        "same parent",
        std::make_unique<Node>(
            "a", 
            std::make_unique<Node>("b"),
            std::make_unique<Node>("c")
        ),
        "b",
        "c"
    );
    test(
        "same branch",
        std::make_unique<Node>(
            "a", 
            std::make_unique<Node>(
                "b",
                std::make_unique<Node>(
                    "c",
                    std::make_unique<Node>("d"),
                    nullptr
                ),
                nullptr
            ),
            nullptr
        ),
        "c",
        "d"
    );
    test(
        "worst case",
        std::make_unique<Node>(
            "a", 
            std::make_unique<Node>(
                "b",
                std::make_unique<Node>("d"),
                std::make_unique<Node>("e")
            ),
            std::make_unique<Node>(
                "c",
                std::make_unique<Node>("f"),
                std::make_unique<Node>("g")
            )
        ),
        "d",
        "g"
    );

    return 0;
}