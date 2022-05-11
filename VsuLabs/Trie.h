//Trie.h
#pragma once
#include <string>
#include <iostream>
#include <stack>

using namespace std;
const int d = 26;

class TrieTree
{
private:
    struct Node
    {
        Node* alph[d + 1];
    };

    Node* root;

public:
    TrieTree()
    {
        Add(root);
    }

    ~TrieTree()
    {
        _clear(root);
    }

    void Add(Node*& p)
    {
        p = new Node;
        for (int i = 0; i < d + 1; i++)
            p->alph[i] = nullptr;
    }

    void Insert(string elem)
    {
        Node* tmp = root;

        for (int i = 0; i < elem.size(); i++)
        {
            if (tmp->alph[elem[i] - 'a'] == nullptr)
                Add(tmp->alph[elem[i] - 'a']);

            tmp = tmp->alph[elem[i] - 'a'];
        }

        Add(tmp->alph[d]);
    }

    void delete_Node(Node*& p)
    {
        delete[] p;
        p = nullptr;
    }

    bool IsList(Node* p)
    {
        int i = 0;
        bool result = true;

        while (i <= d && result)
        {
            result = (p->alph[i] == nullptr);
            i++;
        }

        return result;
    }

    void _Delete(string str, Node*& p)
    {
        if (str == "")
        {
            if (p->alph[d])
                delete_Node(p->alph[d]);
        }
        else if (p->alph[str[0] - 'a'])
        {
            char s0 = str[0];
            str = str.erase(0, 1);
            _Delete(str, p->alph[s0 - 'a']);
            if (IsList(p->alph[s0 - 'a']))
                delete_Node(p->alph[s0 - 'a']);
        }
    }


    void EraseIf(bool(*func)(string))
    {
        stack<pair<Node*, int>> trace_nodes;

        Node* p_node = root;

        string word;

        int i = 0;

        while (i < d)
        {
            if (p_node->alph[i] != nullptr)
            {
                word += ('a' + i);

                trace_nodes.push({ p_node, i });
                p_node = p_node->alph[i];
                i = 0;

                if (p_node->alph[d] != nullptr && func(word))
                {
                    delete_Node(p_node->alph[d]);

                    while (IsList(p_node) && p_node != root)
                    {
                        p_node = trace_nodes.top().first;
                        i = trace_nodes.top().second;
                        trace_nodes.pop();
                        word.pop_back();

                        delete_Node(p_node->alph[i]);
                    }

                }

                continue;
            }

            if (i == d - 1 && trace_nodes.size())
            {
                p_node = trace_nodes.top().first;
                i = trace_nodes.top().second;
                trace_nodes.pop();
                word.pop_back();
            }

            i++;
        }

    }



    template <class _Pr>
    void ForEach(_Pr func)
    {
        stack<pair<Node*, int>> trace_nodes;

        Node* p_node = root;

        string word;

        int i = 0;

        while (i < d)
        {
            if (p_node->alph[i] != nullptr)
            {
                word += ('a' + i);

                trace_nodes.push({ p_node, i });
                p_node = p_node->alph[i];
                i = 0;

                if (p_node->alph[d] != nullptr)
                {
                    func(word);
                }

                continue;
            }

            if (i == d - 1 && trace_nodes.size())
            {
                p_node = trace_nodes.top().first;
                i = trace_nodes.top().second;
                trace_nodes.pop();
                word.pop_back();
            }

            i++;
        }

    }

    void printWord(Node* p_node, string word)
    {
        for (int i = 0; i < d; i++)
        {
            if (p_node->alph[i])
            {
                word += (char)(i + 'a');
                printWord(p_node->alph[i], word);
                word.pop_back();
            }
        }

        if (p_node->alph[d] != nullptr)
            cout << word << endl;
    }

    void printWord(string& word)
    {
        printWord(this->root, word);
    }

    void _clear(Node*& p)
    {
        for (int i = 0; i <= d; i++)
        {
            if (p->alph[i] != 0)
                _clear(p->alph[i]);
        }

        delete[] p;
        p = nullptr;
    }
};