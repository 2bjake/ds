#include "trie.h"
#include <algorithm>

void Trie::insertStringInternal(std::shared_ptr<Node> node, std::string s, std::size_t strIdx){
    if(strIdx < s.length()) {
        std::shared_ptr<Node> &child = node->children[s[strIdx]];
        if(!child) {
            child.reset(new Node());
        }
        this->insertStringInternal(child, s, ++strIdx);
    } else {
        node->value = true;
    }
}

void Trie::insertString(const std::string &s) {
    if(s.empty()) return;
    std::string str = s;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    this->insertStringInternal(this->head, str, 0);
}

bool Trie::hasStringInternal(std::shared_ptr<Node> node, std::string s, std::size_t strIdx) const {
    std::shared_ptr<Node> matchingNode = this->getMatchingNode(node, s, strIdx);
    return matchingNode != NULL && matchingNode->value;
}

std::shared_ptr<Trie::Node> Trie::getMatchingNode(std::shared_ptr<Node> node, std::string s, std::size_t strIdx) const {
    if(strIdx < s.length()) {
        auto it = node->children.find(s[strIdx]);
        if(it == node->children.end()) {
            return std::shared_ptr<Node>();
        } else {
            return this->getMatchingNode(it->second, s, ++strIdx);
        }
    } else {
        return node;
    }
}

bool Trie::hasString(const std::string &s) const {
    if(s.empty()) return false;
    std::string str = s;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return this->hasStringInternal(this->head, str, 0);
}

void Trie::getStringsInternal(std::shared_ptr<Node> node, std::vector<char> &trail, std::vector<std::string> &results) const {
    if(node->value) {
        results.push_back(std::string(trail.begin(), trail.end()));
    }

    for(auto kv : node->children) {
        trail.push_back(kv.first);
        this->getStringsInternal(kv.second, trail, results);
        trail.pop_back();
    }
}

std::vector<std::string> Trie::getStrings() const {
    return this->getStrings("");
}

std::vector<std::string> Trie::getStrings(const std::string &startsWith) const {
    std::shared_ptr<Node> matchingNode = this->getMatchingNode(this->head, startsWith, 0);

    std::vector<std::string> results;
    if(matchingNode == NULL) {
        return results;
    }

    std::vector<char> trail;
    this->getStringsInternal(matchingNode, trail, results);
    if(!startsWith.empty()) {
        std::transform(results.begin(), results.end(), results.begin(), [startsWith] (std::string &str) { return str.insert(0, startsWith); });
    }
    return results;
}
