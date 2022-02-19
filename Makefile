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
	build_order

all: \
	strings \
	linked_lists \
	graphs
