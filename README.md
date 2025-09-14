# Coding Questions

A curated set of programming problems I worked through while preparing for interviews. Each problem is a small, self-contained C++ program with quick usage examples in `main()`. The repository is organized by topic (strings, linked lists, graphs, etc.).

### Build and run

- Build everything: `make all`
- Build a topic group (e.g., strings): `make strings`
- Build a single problem (e.g., sparse_search): `make sparse_search`
- Run the produced binary (e.g., `./sorting_and_searching/sparse_search`).

If you hit compiler-version issues, the Makefile uses `-std=c++20`; lowering to `-std=c++17` often works too.

---

## Problems by topic

### Strings

- *Integer/String Conversions* - [code](strings/integer_string_conversions.cpp)
  - Problem: Implement `str_to_int` and `int_to_str` for signed integers (handle `-` and bounds).
  - Solution: Manual digit parsing and accumulation; for int -> string, emit digits, handle negative numbers and the `INT_MIN` edge case, then reverse.

- *String Rotation* - [code](strings/string_rotation.cpp)
  - Problem: Check if `s2` is a rotation of `s1` using only one call to `isSubstring`.
  - Solution: Validate equal lengths and test `isSubstring(s2 + s2, s1)`.

- *Scrambled Input* - [code](strings/scrambled_input.cpp)
  - Problem: Given a sentence with letters scrambled within each word, map each token back to a valid dictionary word.
  - Solution: Build an order-agnostic dictionary keyed by sorted letters; split the sentence, sort letters per token, and look up originals.

### Linked Lists

- *Sum Lists* - [code](linked_lists/sum_lists.cpp)
  - Problem: Add two numbers represented as reversed single linked lists; return the sum as a list.
  - Solution: Traverse both lists digit-by-digit, track carry, and build the result list; append a final node if carry remains.

- *Palindrome* - [code](linked_lists/palindrome.cpp)
  - Problem: Determine whether a singly linked list is a palindrome.
  - Solution: Recursively compare symmetric nodes using the length to find the middle and a moving "mirror" pointer on unwind.

- *Intersection* - [code](linked_lists/intersection.cpp)
  - Problem: Detect if two singly linked lists intersect by reference and return the intersecting node.
  - Solution: Recursively align heads based on length delta, then advance both pointers together to find the first shared node (by address).

### Heaps

- *K-th Smallest Element* - [code](heaps/kth_smallest_element.cpp)
  - Problem: Find the k-th smallest element in an array.
  - Solution: Maintain a fixed-size max-heap of the current K smallest; push/pop in O(log K) while scanning; the heap top is the answer.

### Graphs and Trees

- *Route Between Nodes* (Directed Graph) - [code](graphs/route.cpp)
  - Problem: Given a directed graph and nodes S and E, determine whether a route exists from S to E.
  - Solution: Bidirectional BFS with two visitor marks; if a node is visited by both frontiers, a route exists.

- *Minimal Height BST* - [code](graphs/minimal_binary_search_tree.cpp)
  - Problem: Build a minimal-height BST from a sorted array of unique ints.
  - Solution: Recursively pick the mid element as the root (divide-and-conquer) to balance height.

- *Build Order* (Topological Sort) - [code](graphs/build_order.cpp)
  - Problem: Given projects and dependency pairs, output a valid build order or report none if cyclic.
  - Solution: Detect cycles via DFS; then print a post-order traversal from source nodes (a form of topological ordering).

- *First Common Ancestor* (Binary Tree) - [code](graphs/first_common_ancestor.cpp)
  - Problem: Find the lowest common ancestor of two nodes in a binary tree without extra parent links.
  - Solution: Post-order DFS propagating a bitmask of findings; the first node where both targets are discovered is the LCA.

- *BST Sequences* - [code](graphs/bst_sequences.cpp)
  - Problem: Given a BST with distinct values, print arrays that could have produced it via left-to-right insertion.
  - Solution: Recursively gather sequences from left and right subtrees and combine them prefixed by the current value (left+right and right+left orderings in this implementation).

### Sorting and Searching

- *Sparse Search* - [code](sorting_and_searching/sparse_search.cpp)
  - Problem: In a sorted string array interspersed with empty strings, find the index of a target string.
  - Solution: Modified binary search: when mid is empty, expand outward to the nearest non-empty string before comparing.

### Recursion and Dynamic Programming

- *Max Subarray* (Kadane's Algorithm) - [code](recursion_and_dynamic_programming/kadanes_algorithm.cpp)
  - Problem: Find the contiguous subarray with the maximum sum, also tracking its bounds.
  - Solution: Linear scan maintaining a running sum and best seen sum/indices; reset when the running sum drops below zero.

- *Recursive Multiply* - [code](recursion_and_dynamic_programming/recursive_multiply.cpp)
  - Problem: Multiply two positive integers without using `*` or `/`; minimize operations.
  - Solution: Recursive doubling/halving (Russian peasant multiplication): add when the low bit is set, double the other operand each step.

- *Robot Grid* - [code](recursion_and_dynamic_programming/robot_grid.cpp)
  - Problem: In a grid with off-limit cells, find a path from top-left to bottom-right moving only right or down.
  - Solution: Recursive branching and backtracking, favoring the direction that reduces remaining steps; collects the path when successful.

- *Triple Step* - [code](recursion_and_dynamic_programming/triple_step.cpp)
  - Problem: Count/visualize the ways to climb n steps taking 1–3 hops at a time.
  - Solution: Build a decision tree with up to three children per node representing hop sizes; the sample prints the tree layout.

---

## Notes

- All examples print their results to stdout in `main()` for quick checks.
- The implementations favor clarity; many can be extended with unit tests or alternative approaches.
