CXXFLAGS := -g -I. -std=c++20
LDFLAGS := -lstdc++

%.question:
	$(CC) $(CXXFLAGS) -o ./$* ./$*.cpp $(LDFLAGS)

integer_string_conversions: strings/integer_string_conversions.question

string_rotation: strings/string_rotation.question

strings: \
	integer_string_conversions \
	string_rotation

all: strings
