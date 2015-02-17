#ifndef TRIE_H
#define TRIE_H

#include <map>
#include <vector>
#include <string>
#include <memory>

class Trie {
private:
    struct Node {
        std::map<char, std::shared_ptr<Node>> children;
        bool value;
    };

    std::shared_ptr<Node> head;

    void insertStringInternal(std::shared_ptr<Node> node, std::string s, std::size_t strIdx);
    bool hasStringInternal(std::shared_ptr<Node> node, std::string s, std::size_t strIdx) const;
    std::shared_ptr<Node> getMatchingNode(std::shared_ptr<Node> node, std::string s, std::size_t strIdx) const;
    void getStringsInternal(std::shared_ptr<Node> node, std::vector<char> &trail, std::vector<std::string> &results) const;

public:
    Trie() : head(new Node()) {}
    void insertString(const std::string &s);
    bool hasString(const std::string &s) const;

    std::vector<std::string> getStrings() const;
    std::vector<std::string> getStrings(const std::string &startsWith) const;
};

#endif
