integer_string_conversions:
	$(CC) -g -o ./strings/integer_string_conversions ./strings/integer_string_conversions.cpp -I. -lstdc++

all: integer_string_conversions
