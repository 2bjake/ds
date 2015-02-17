#ifndef TRIE_H
#define TRIE_H

#include <map>
#include <vector>
#include <string>
#include <memory>

/*
 * An ordered collection of case-insensitive strings which supports searching based on prefix string.
 */
class Trie {
private:
    /*
     * A node in the tree.
     * If value is true, the characters in the path from root to the node represents an inserted string.
     * The children map contains characters (keys) and Nodes (values) of inserted words which start with the value of the current node.
     * example:
     *
     *  [F] -a-> [F] -n-> [F] -t-> [T] : ant
     *            |        |  -d-> [T] : and
     *            |
     *            |  -r-> [F] -t-> [T] : art
     */
    struct Node {
        std::map<char, std::shared_ptr<Node>> children;
        bool value;
    };

    std::shared_ptr<Node> root;

    void insertStringInternal(std::shared_ptr<Node> node, std::string s, std::size_t strIdx);
    bool hasStringInternal(std::shared_ptr<Node> node, std::string s, std::size_t strIdx) const;
    std::shared_ptr<Node> getMatchingNode(std::shared_ptr<Node> node, std::string s, std::size_t strIdx) const;
    void getStringsInternal(std::shared_ptr<Node> node, std::vector<char> &trail, std::vector<std::string> &results) const;

public:
    Trie() : root(new Node()) {}

    /*
     * Inserts the specified string into the Trie.
     */
    void insertString(const std::string &s);

    /*
     * Checks whether the specified string is in the Trie.
     */
    bool hasString(const std::string &s) const;

    /*
     * Gets a vector of all strings in the Trie.
     */
    std::vector<std::string> getStrings() const;

    /*
     * Gets a vector of all strings in the Trie that start with the specified string.
     */
    std::vector<std::string> getStrings(const std::string &startsWith) const;
};

#endif
