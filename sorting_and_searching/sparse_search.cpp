/* Given a sorted array of strings that is interspersed with empty strings,
write a method to find the location of a given string. */

#include <initializer_list>
#include <iostream>
#include <cstring>

int sparseSearch(const char* search, const char* const* strings, size_t begin, size_t end) {
    if (begin > end) {
        return -1;
    }
    auto mid = begin + (end - begin) / 2;
    if (strcmp(strings[mid], "") == 0) {
        size_t distance = 1;
        while (true) {
            if (begin + distance >= mid || mid + distance >= end) {
                return -1;
            }
            if (strcmp(strings[mid - distance], "") != 0) {
                mid -= distance;
                break;
            } else if (strcmp(strings[mid + distance], "") != 0) {
                mid += distance;
                break;
            }
            distance++;
        }
    }
    auto cmp = strcmp(search, strings[mid]);
    if (cmp < 0) {
        return sparseSearch(search, strings, begin, mid);
    } else if (cmp > 0) {
        return sparseSearch(search, strings, mid + 1, end);
    } else {
        return mid;
    }
}

void test(const char* name, const char* search, const std::initializer_list<const char*>& strings) {
    std::cout << name << " = " << sparseSearch(search, strings.begin(), 0, strings.size() - 1) << std::endl;
}

int main() {
    test(
        "book example", 
        "ball", 
        { "at", "", "", "", "ball", "", "", "car", "", "", "dad", "", "" }
    );
    test(
        "non-matching",
        "biscuit",
        { "at", "", "", "", "ball", "", "", "car", "", "", "dad", "", "" }
    );
    return 0;
}