/* A binary search tree was created by traversing through an array from left to right
and inserting each element. Given a binary search tree with distinct elements, print all
possible arrays that could have left to this tree. */

#include <memory>
#include <iostream>
#include <vector>
#include <string>

struct Node {
    const char* value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(const char* value, std::unique_ptr<Node>&& left, std::unique_ptr<Node>&& right) : value(value), left(std::move(left)), right(std::move(right)) {}
    Node(const char* value) : value(value) {}

};

void generateSequences(const std::unique_ptr<Node>& node, std::vector<std::string>& sequences) {
    std::vector<std::string> leftSequences;
    if (node->left != nullptr) {
        generateSequences(node->left, leftSequences);
    }
    std::vector<std::string> rightSequences;
    if (node->right != nullptr) {
        generateSequences(node->right, rightSequences);
    }
    for (auto& leftSequence : leftSequences) {
        for (auto& rightSequence : rightSequences) {
            sequences.emplace_back(std::string(node->value) + ", " + leftSequence + ", " + rightSequence);
        }
    }
    for (auto& rightSequence : rightSequences) {
        for (auto& leftSequence : leftSequences) {
            sequences.emplace_back(std::string(node->value) + ", " + rightSequence + ", " + leftSequence);
        }
    }
    if (sequences.empty()) {
        sequences.emplace_back(node->value);
    }
}

void test(const char* name, const std::unique_ptr<Node>& root) {
    std::cout << name << ": " << std::endl;
    std::vector<std::string> sequences;
    generateSequences(root, sequences);
    for (auto& sequence : sequences) {
        std::cout << "{ " << sequence << " }" << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    test(
        "book example",
        std::make_unique<Node>(
            "2",
            std::make_unique<Node>("1"),
            std::make_unique<Node>("3")
        )
    );
    test(
        "more complex example",
        std::make_unique<Node>(
            "8",
            std::make_unique<Node>(
                "4",
                std::make_unique<Node>("2"),
                std::make_unique<Node>("6")
            ),
            std::make_unique<Node>(
                "12",
                std::make_unique<Node>("10"),
                std::make_unique<Node>("14")
            )
        )
    );
    return 0;
}