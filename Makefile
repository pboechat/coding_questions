CXXFLAGS := -g -I. -std=c++14
LDFLAGS := -lstdc++

%.question:
	$(CC) $(CXXFLAGS) -o ./$* ./$*.cpp $(LDFLAGS)

integer_string_conversions: strings/integer_string_conversions.question

string_rotation: strings/string_rotation.question

sum_lists: linked_lists/sum_lists.question

palindrome: linked_lists/palindrome.question

intersection: linked_lists/intersection.question

strings: \
	integer_string_conversions \
	string_rotation

linked_lists: \
	sum_lists \
	palindrome \
	intersection

all: \
	strings \
	linked_lists
