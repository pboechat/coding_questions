/*
Implement a function to check if a linked list is a palindrome
*/

#include <string>
#include <iostream>

struct Node {
    Node* next;
    char data;

};

Node* createLinkedList(const std::string& str) {
    if (str.empty())
        return nullptr;
    Node* curr, *prev = nullptr, *head = nullptr;
    size_t i = 0;
    do
    {
        curr = new Node();
        curr->data = str[i];
        if (head == nullptr)
            head = curr;
        if (prev != nullptr)
            prev->next = curr;
        prev = curr;
    } while (++i < str.size());
    return head;
}

void destroyLinkedList(Node* curr) {
    if (curr == nullptr) {
        return;
    }
    destroyLinkedList(curr->next);
    delete curr;
}

size_t getLength(Node* node, size_t pos = 1) {
    if (node == nullptr)
        return 0;
    if (node->next == nullptr)
        return pos;
    return getLength(node->next, pos + 1);
}

bool isPalindrome(Node* curr, const size_t length, const size_t pos = 0, Node** mirror = nullptr) {
    Node* next;
    if (pos == length / 2) {
        if (length % 2 == 0) {
            next = curr;
        } else {
            if (mirror != nullptr)
                next = curr->next;
        }
        if (mirror != nullptr)
            *mirror = next;
        return true;
    }
    if (!isPalindrome(curr->next, length, pos + 1, &next)) {
        return false;
    }
    if (curr->data == next->data) {
        if (mirror != nullptr)
            *mirror = next->next;
        return true;
    } else {
        return false;
    }
}

void test(const std::string& str) {
    auto* head = createLinkedList(str);
    std::cout << "isPalindrome(" << str << ") = " << isPalindrome(head, getLength(head)) << std::endl;
    destroyLinkedList(head);
}

int main() {
    test("tacocat");
    test("naan");
    test("palindrome");
    test("p");
    test("");
    return 0;
}