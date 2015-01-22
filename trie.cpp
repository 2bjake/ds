#include "trie.h"
#include <algorithm>

void Trie::insertStringInternal(shared_ptr<Node> node, string s, std::size_t strIdx){
    if(strIdx < s.length()) {
        shared_ptr<Node> &child = node->children[s[strIdx]];
        if(!child) {
            child.reset(new Node());
        }
        this->insertStringInternal(child, s, ++strIdx);
    } else {
        node->value = true;
    }
}

void Trie::insertString(const string &s) {
    if(s.empty()) return;
    string str = s;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    this->insertStringInternal(this->head, str, 0);
}

bool Trie::hasStringInternal(shared_ptr<Node> node, string s, std::size_t strIdx) const {
    shared_ptr<Node> matchingNode = this->getMatchingNode(node, s, strIdx);
    return matchingNode != NULL && matchingNode->value;
}

shared_ptr<Trie::Node> Trie::getMatchingNode(shared_ptr<Node> node, string s, std::size_t strIdx) const {
    if(strIdx < s.length()) {
        auto it = node->children.find(s[strIdx]);
        if(it == node->children.end()) {
            return shared_ptr<Node>();
        } else {
            return this->getMatchingNode(it->second, s, ++strIdx);
        }
    } else {
        return node;
    }
}

bool Trie::hasString(const string &s) const {
    if(s.empty()) return false;
    string str = s;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return this->hasStringInternal(this->head, str, 0);
}

void Trie::getStringsInternal(shared_ptr<Node> node, vector<char> &trail, vector<string> &results) const {
    if(node->value) {
        results.push_back(string(trail.begin(), trail.end()));
    }

    for(auto kv : node->children) {
        trail.push_back(kv.first);
        this->getStringsInternal(kv.second, trail, results);
        trail.pop_back();
    }
}

vector<string> Trie::getStrings() const {
    vector<string> results;
    vector<char> trail;
    this->getStringsInternal(this->head, trail, results);
    return results;
}

vector<string> Trie::getStrings(const string &startsWith) const {
    shared_ptr<Node> matchingNode = this->getMatchingNode(this->head, startsWith, 0);

    vector<string> results;
    if(matchingNode == NULL) {
        return results;
    }

    vector<char> trail;
    this->getStringsInternal(matchingNode, trail, results);
    std::transform(results.begin(), results.end(), results.begin(), [startsWith] (string &str) { return str.insert(0, startsWith); });
    return results;
}
