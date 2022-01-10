/*
Given two (singly) linked lists, determine if the two intersect.
Return the intersecting node. Note that the intersection is defined based on reference,
not value. That is, if the kth node of the first linked list is the exact same node (by reference),
as the jth node of the second linked list, then they are intersecting.
*/

#include <cstddef>
#include <iostream>
#include <type_traits>
#include <cmath>

struct Node {
    Node* next;
    size_t idx;
};

struct Bubble {
    size_t pos;
    bool left;
};

bool getNewHeads(const Node* const leftCurr, const Node* const rightCurr, const Node** const leftHead, const Node** const rightHead, Bubble& bubble, const size_t leftCurrPos = 0, const size_t rightCurrPos = 0) {
    if (leftCurr == nullptr || rightCurr == nullptr) {
        return false;
    }
    const Node* leftNext, *rightNext;
    size_t leftNextPos, rightNextPos;
    if (leftCurr->next != nullptr) {
        leftNext = leftCurr->next;
        leftNextPos = leftCurrPos + 1;
    }
    else {
        leftNext = leftCurr;
        leftNextPos = leftCurrPos;
    }
    if (rightCurr->next != nullptr) {
        rightNext = rightCurr->next;
        rightNextPos = rightCurrPos + 1;
    }
    else {
        rightNext = rightCurr;
        rightNextPos = rightCurrPos;
    }
    if (leftCurr->next == nullptr && rightCurr->next == nullptr) {
        if (leftCurr != rightCurr)
            return false;
        bubble.pos = abs(leftCurrPos - rightCurrPos);
        bubble.left = leftCurrPos > rightCurrPos;
        return true;
    }
    if (!getNewHeads(leftNext, rightNext, leftHead, rightHead, bubble, leftNextPos, rightNextPos)) {
        return false;
    }
    if (bubble.left) {
        if (bubble.pos == leftCurrPos) {
            *leftHead = leftCurr;
        }
        if (rightCurrPos == 0) {
            *rightHead = rightCurr;
        }
    } 
    else {
        if (bubble.pos == rightCurrPos) {
            *rightHead = rightCurr;
        }
        if (leftCurrPos == 0) {
            *leftHead = leftCurr;
        }
    }
    return true;
}

bool getNewHeads(const Node* const leftCurr, const Node* const rightCurr, const Node** const newLeftHead, const Node** newRightHead) {
    Bubble bubble;
    return getNewHeads(leftCurr, rightCurr, newLeftHead, newRightHead, bubble);
}

const Node* findEqual(const Node* leftCurr, const Node* rightCurr) {
    if (leftCurr == rightCurr) {
        return leftCurr;
    }
    return findEqual(leftCurr->next, rightCurr->next);
}

bool intersect(const Node* const leftHead, const Node* const rightHead, const Node** const intersection) {
    const Node* newLeftHead, *newRightHead;
    if (!getNewHeads(leftHead, rightHead, &newLeftHead, &newRightHead)) {
        return false;
    }
    *intersection = findEqual(newLeftHead, newRightHead);
    return true;
}

int main() {
    Node n[9];

    for (size_t i = 0; i < std::extent<decltype(n)>::value; ++i) {
        n[i].idx = i;
        n[i].next = nullptr;
    }

    for (size_t i = 0; i < 6; ++i) {
        n[i].next = &n[i + 1];
    }
    n[7].next = &n[3];

    const Node* intersection;

    std::cout << "intersect(n0, n7) = " << (intersect(&n[0], &n[7], &intersection) ? std::to_string(intersection->idx) : "null") << std::endl;
    std::cout << "intersect(n2, n7) = " << (intersect(&n[2], &n[7], &intersection) ? std::to_string(intersection->idx) : "null") << std::endl;
    std::cout << "intersect(n3, n7) = " << (intersect(&n[3], &n[7], &intersection) ? std::to_string(intersection->idx) : "null") << std::endl;
    std::cout << "intersect(n0, n0) = " << (intersect(&n[0], &n[0], &intersection) ? std::to_string(intersection->idx) : "null") << std::endl;
    std::cout << "intersect(n0, n8) = " << (intersect(&n[0], &n[8], &intersection) ? std::to_string(intersection->idx) : "null") << std::endl;

    return 0;
}