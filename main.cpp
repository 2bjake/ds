#include <iostream>
#include <vector>
#include <algorithm>
#include "trie.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;

void assertTrue(bool value, string errorMsg) {
    if(!value) {
        cerr << "FAIL: " << errorMsg;
        exit(-1);
    }
}

void assertFalse(bool value, string errorMsg) {
    assertTrue(!value, errorMsg);
}

void matchedStringPrinter(Trie &trie, string s) {
    cout << endl << "getStrings(\"" + s + "\")" << endl;
    vector<string> strings = trie.getStrings(s);
        for(auto &str : strings) {
        cout << str << endl;
    }
}

int main() {
    Trie trie;
    const vector<const string> insertStrings =
        {"test", "a", "ab", "bb", "bb2", "CAPS", "CA", "ABC", "mIxEd", "MIxed2"};
    const vector<const string> noInsertStrings = {"test2", "aa", "foo", "bbb", "b"};

    for(auto &str : insertStrings) {
        trie.insertString(str);
    }

    vector<string> testStrings;
    for(auto &str : insertStrings) {
        testStrings.push_back(str);

        string upper = str;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        testStrings.push_back(upper);

        string lower = str;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        testStrings.push_back(lower);
    }

    for(auto &str : testStrings) {
        assertTrue(trie.hasString(str), str + " was not found in trie");
    }

    for(auto &str : noInsertStrings) {
        assertFalse(trie.hasString(str), str + " was found in trie");
    }
    cout << endl << "SUCCESS" << endl;

    cout << "getStrings()" << endl;
    vector<string> strings = trie.getStrings();
    for(auto &str : strings) {
        cout << str << endl;
    }

    matchedStringPrinter(trie, "a");
    matchedStringPrinter(trie, "bb");
    matchedStringPrinter(trie, "");
    return 0;
}
