#pragma once
//Trie.h
#pragma once
#include <string>
#include <iostream>

using namespace std;
const int d = 26;
class TrieTree {
    struct Node {
        Node* alph[d + 1];
    };
    Node* root;
public:
    TrieTree() {
        root = new Node;
        for (int i = 0; i < d + 1; i++)
            root->alph[i] = 0;
    }

    ~TrieTree() {
        _clear(root);
    }

    void Add(Node*& p) {
        p = new Node;
        for (int i = 0; i < d + 1; i++)
            p->alph[i] = 0;
    }

    void Insert(string elem) {
        Node* tmp = root;
        for (int i = 0; i < elem.size(); i++) {
            if (tmp->alph[elem[i] - 'a'] == 0)
                Add(tmp->alph[elem[i] - 'a']);
            tmp = tmp->alph[elem[i] - 'a'];
        }
        Add(tmp->alph[d]);
    }

    void delete_Node(Node*& p) {
        delete[]p;
        p = 0;
    }

    bool IsList(Node* p) {
        int i = 0;
        bool result = true;
        while (i <= d && result) {
            result = (p->alph[i] == 0);
            i++;
        }
        return result;
    }

    void _Delete(string str, Node*& p) {
        if (str == "") {
            if (p->alph[d]) delete_Node(p->alph[d]);
        }
        else if (p->alph[str[0] - 'a']) {
            char s0 = str[0];
            str = str.erase(0, 1);
            _Delete(str, p->alph[s0 - 'a']);
            if (IsList(p->alph[s0 - 'a'])) delete_Node(p->alph[s0 - 'a']);
        }
    }

    void Delete(string str)
    {
        if (str.size() % 2 == 0)
            _Delete(str, this->root);
    }

    void printWord(Node* root, string word) {
        for (int i = 0; i < d; i++)
            if (root->alph[i]) {
                word += (char)(i + 'a');
                printWord(root->alph[i], word);
                word.erase(word.size() - 1, 1);
            }
        if (root->alph[d] != 0) {
            cout << word << endl;
        }
    }

    void printWord(string& word) {
        printWord(this->root, word);
    }

    void _clear(Node*& p) {
        for (int i = 0; i <= d; i++) {
            if (p->alph[i] != 0)
                _clear(p->alph[i]);
        }
        delete[]p;
        p = 0;
    }

};