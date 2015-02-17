#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "trie.h"

void assertTrue(bool value, std::string errorMsg) {
    if(!value) {
        std::cerr << "FAIL: " << errorMsg;
        exit(-1);
    }
}

void assertFalse(bool value, std::string errorMsg) {
    assertTrue(!value, errorMsg);
}

void matchedStringPrinter(Trie &trie, std::string s) {
    std::cout << std::endl << "getStrings(\"" + s + "\")" << std::endl;
    std::vector<std::string> strings = trie.getStrings(s);
        for(auto &str : strings) {
        std::cout << str << std::endl;
    }
}

int main() {
    Trie trie;
    const std::vector<const std::string> insertStrings =
        {"test", "a", "ab", "bb", "bb2", "CAPS", "CA", "ABC", "mIxEd", "MIxed2"};
    const std::vector<const std::string> noInsertStrings = {"test2", "aa", "foo", "bbb", "b"};

    for(auto &str : insertStrings) {
        trie.insertString(str);
    }

    std::vector<std::string> testStrings;
    for(auto &str : insertStrings) {
        testStrings.push_back(str);

        std::string upper = str;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        testStrings.push_back(upper);

        std::string lower = str;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        testStrings.push_back(lower);
    }

    for(auto &str : testStrings) {
        assertTrue(trie.hasString(str), str + " was not found in trie");
    }

    for(auto &str : noInsertStrings) {
        assertFalse(trie.hasString(str), str + " was found in trie");
    }
    std::cout << std::endl << "SUCCESS" << std::endl;

    std::cout << "getStrings()" << std::endl;
    std::vector<std::string> strings = trie.getStrings();
    for(auto &str : strings) {
        std::cout << str << std::endl;
    }

    matchedStringPrinter(trie, "a");
    matchedStringPrinter(trie, "BB");
    matchedStringPrinter(trie, "");
    return 0;
}
