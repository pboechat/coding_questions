/*
You have two numbers represented by a linked list, where each node contains a single digit.
The digits are stored in reverse order, such taht the 1's digit is at the head of the list.
Write a function that adds the two numbers and returns the sum as a linked list.
*/

#include <iostream>
#include <memory>
#include <vector>
#include <initializer_list>

struct LinkedList {
    struct Node {
        std::shared_ptr<Node> next{ nullptr };
        int data;

        Node() : data(0) {}
        Node(int data) : data(data) {}  

    };

    LinkedList() : head(nullptr) {}

    LinkedList(const std::initializer_list<int>& initializer)
    {
        std::shared_ptr<Node> curr, prev;
        std::vector<int> initialData(initializer);
        for (auto i = 0; i < initialData.size(); ++i) {
            curr = std::make_unique<Node>(initialData[i]);
            if (i == 0) {
                head = curr;
            }
            if (prev != nullptr) {
                prev->next = curr;
            }
            prev = curr;
        }
    }

    LinkedList(const LinkedList& other) : head(other.head) {}

    std::shared_ptr<Node> head;

};

std::ostream& operator<<(std::ostream& out, const LinkedList& ll) {
    auto c = ll.head;
    std::cout << "( ";
    while (true) {
        std::cout << c->data;
        if (c->next == nullptr) {
            break;
        }
        std::cout << " -> ";
        c = c->next;
    }
    std::cout << " )\n";
    return out;
}

LinkedList sumLists(const LinkedList& ll0, const LinkedList& ll1) {
    auto c0 = ll0.head, c1 = ll1.head;
    LinkedList r;
    typedef LinkedList::Node Node;
    std::shared_ptr<Node> cr, pr;
    int remainder = 0;
    do
    {
        auto sum = (c0 ? c0->data : 0) + (c1 ? c1->data : 0) + remainder;
        cr = std::make_shared<Node>(sum % 10);
        if (r.head == nullptr) {
            r.head = cr;
        }
        if (pr != nullptr) {
            pr->next = cr;
        }
        pr = cr;
        remainder = sum / 10;
        c0 = c0 ? c0->next : nullptr;
        c1 = c1 ? c1->next : nullptr;
    } while (c0 != nullptr || c1 != nullptr);
    if (remainder > 0) {
        cr->next = std::make_shared<Node>(remainder);
    }
    return r;
}

int main() {
    std::cout << "( 7 -> 1 -> 6 } + ( 5 -> 9 -> 2 ) = " << sumLists({ 7, 1, 6 }, { 5, 9, 2 }) << std::endl;
    std::cout << "( 9 -> 9 -> 9 ) + ( 1 ) = " << sumLists({ 9, 9, 9 }, { 1 }) << std::endl;
    return 0;
}