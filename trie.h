#ifndef TRIE_H
#define TRIE_H

#include <map>
#include <vector>
#include <string>
#include <memory>

using std::string;
using std::map;
using std::vector;
using std::shared_ptr;

class Trie {
private:
    struct Node {
        map<char, shared_ptr<Node>> children;
        bool value;
    };

    shared_ptr<Node> head;

    void insertStringInternal(shared_ptr<Node> node, string s, size_t strIdx);
    bool hasStringInternal(shared_ptr<Node> node, string s, size_t strIdx) const;
    shared_ptr<Node> getMatchingNode(shared_ptr<Node> node, string s, size_t strIdx) const;
    void getStringsInternal(shared_ptr<Node> node, vector<char> &trail, vector<string> &results) const;

public:
    Trie() : head(new Node()) {}
    void insertString(const string &s);
    bool hasString(const string &s) const;

    vector<string> getStrings() const;
    vector<string> getStrings(const string &startsWith) const;
};

#endif
