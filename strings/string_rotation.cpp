/*
Assume you have a method isSubstring which checks if one word is a substring
of another. Given two strings, s1 and s2, write code to check if s1 is a rotation
of s1 using only one call to isSubstring(e.g. "waterbottle" is a rotation of "erbottlewat")
*/
#include <cstring>
#include <iostream>
#include <string>

bool isSubstring(const std::string& s1, const std::string& s2) {
    return strstr(s1.c_str(), s2.c_str()) != nullptr;
}

bool isRotation1(const std::string& s1, const std::string& s2) {
    if (s1.size() != s2.size()) {
        return false;
    }
    auto it1 = s1.begin();
    for (auto it2 = s2.begin(); it2 != s2.end();) {
        if (*it1 == *it2) {
            auto savedIt2 = it2;
            do {
                it1++;
                it2++;
            } while (*it1 == *it2 && it2 != s2.end());
            if (it2 == s2.end()) {
                return strcmp(
                    s1.substr(std::distance(s1.begin(), it1)).c_str(),
                    s2.substr(0, std::distance(s2.begin(), savedIt2)).c_str()
                ) == 0;
            }
            it1 = s1.begin();
        }
        else
        {
            it2++;
        }
    }
    return false;
}

bool isRotation(const std::string& s1, const std::string& s2) {
    return s1.size() == s2.size() && isSubstring(s2 + s2, s1);
}

int main() {
    std::cout << "isRotation(waterbottle, erbottlewat) = " << isRotation("waterbottle", "erbottlewat") << std::endl;
    std::cout << "isRotation(waterbottle, bottlewater) = " << isRotation("waterbottle", "bottlewater") << std::endl;
    std::cout << "isRotation(waterbottle, winebottle) = " << isRotation("waterbottle", "winebottle") << std::endl;
    std::cout << "isRotation(waterbottle, waterbattle) = " << isRotation("waterbottle", "waterbattle") << std::endl;
    std::cout << "isRotation(waterbottle, watwatwater) = " << isRotation("waterbottle", "watwatwater") << std::endl;
    return 0;
}