CXXFLAGS := -g -O0 -I. -std=c++20
LDFLAGS := -lstdc++ -lm

%.question:
	$(CC) $(CXXFLAGS) -o ./$* ./$*.cpp $(LDFLAGS)

integer_string_conversions: strings/integer_string_conversions.question

string_rotation: strings/string_rotation.question

scrambled_input: strings/scrambled_input.question

sum_lists: linked_lists/sum_lists.question

palindrome: linked_lists/palindrome.question

intersection: linked_lists/intersection.question

route: graphs/route.question

minimal_binary_search_tree: graphs/minimal_binary_search_tree.question

build_order: graphs/build_order.question

first_common_ancestor: graphs/first_common_ancestor.question

bst_sequences: graphs/bst_sequences.question

sparse_search: sorting_and_searching/sparse_search.question

triple_step: recursion_and_dynamic_programming/triple_step.question

robot_grid: recursion_and_dynamic_programming/robot_grid.question

recursive_multiply: recursion_and_dynamic_programming/recursive_multiply.question

strings: \
	integer_string_conversions \
	string_rotation \
	scrambled_input

linked_lists: \
	sum_lists \
	palindrome \
	intersection

graphs: \
	route \
	minimal_binary_search_tree \
	build_order \
	first_common_ancestor \
	bst_sequences

sorting_and_searching: \
	sparse_search

recursion_and_dynamic_programming: \
	triple_step \
	robot_grid \
	recursive_multiply

all: \
	strings \
	linked_lists \
	graphs \
	sorting_and_searching \
	recursion_and_dynamic_programming
