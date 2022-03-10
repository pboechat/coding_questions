#include <string>
#include <unordered_map>
#include <algorithm>
#include <optional>
#include <iostream>
#include <vector>

void initializeOrderAgnosticDictionary(const std::vector<std::string>& dictionary, std::unordered_map<std::string, std::string>& orderAgnosticDictionary) {
    for (const auto& word : dictionary) {
        auto sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        auto it = orderAgnosticDictionary.find(sortedWord);
        if (it == orderAgnosticDictionary.end()) {
            orderAgnosticDictionary.emplace(sortedWord, word);
        }
    }
}

std::vector<std::string> splitIntoWords(const std::string& sentence) {
    std::vector<std::string> words;
    if (sentence.empty()) {
        return words;
    }
    auto* begin = &sentence[0];
    auto* end = &sentence[sentence.size()];
    for (; end > begin; --end) {
        if (*(end - 1) != ' ') {
            break;
        }
    }
    auto* it1 = begin, *it2 = begin;
    for (; it1 != end; ++it1) {
        if (*it1 == ' ') {
            if (it1 != it2) {
                words.emplace_back(std::string(it2, it1));
            } 
            it2 = it1;
        } else if (*it2 == ' ') {
            it2 = it1;
        }
    }
    if (it1 != it2) {
        words.emplace_back(std::string(it2, end));
    }
    return words;
}

std::optional<std::vector<std::string>> unscramble(const std::unordered_map<std::string, std::string>& orderAgnosticDictionary,
    const std::string& scrambled) {
    std::vector<std::string> output;
    auto words = splitIntoWords(scrambled);
    for (auto& word : words) {
        auto sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        auto it = orderAgnosticDictionary.find(sortedWord);
        if (it != orderAgnosticDictionary.end()) {
            output.emplace_back(it->second);
        } else {
            return std::nullopt;
        }
    }
    return output;
}

std::string concatenate(const std::optional<std::vector<std::string>>& words) {
    std::string sentence;
    if (words != std::nullopt) {
        for (auto& word : *words) {
            sentence += word + " ";
        }
    }
    return sentence;
}

void test(const char* name, const std::unordered_map<std::string, std::string>& orderAgnosticDictionary, const std::string& scrambled) {
    std::cout << name << " = " << concatenate(unscramble(orderAgnosticDictionary, scrambled)) << std::endl;
}

int main() {
    std::unordered_map<std::string, std::string> dict;
    initializeOrderAgnosticDictionary(
        {
            "this",
            "is",
            "a",
            "sample"
        }, 
        dict
    );

    test(
        "statement example",
        dict,
        "thsi si a emplas    "
    );
    
    return 0;
}