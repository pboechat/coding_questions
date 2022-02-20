CXXFLAGS := -g -O0 -I. -std=c++14
LDFLAGS := -lstdc++

%.question:
	$(CC) $(CXXFLAGS) -o ./$* ./$*.cpp $(LDFLAGS)

integer_string_conversions: strings/integer_string_conversions.question

string_rotation: strings/string_rotation.question

sum_lists: linked_lists/sum_lists.question

palindrome: linked_lists/palindrome.question

intersection: linked_lists/intersection.question

route: graphs/route.question

minimal_binary_search_tree: graphs/minimal_binary_search_tree.question

build_order: graphs/build_order.question

first_common_ancestor: graphs/first_common_ancestor.question

bst_sequences: graphs/bst_sequences.question

sparse_search: sorting_and_searching/sparse_search.question

strings: \
	integer_string_conversions \
	string_rotation

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


all: \
	strings \
	linked_lists \
	graphs \
	sorting_and_searching
