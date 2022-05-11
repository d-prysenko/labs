#include "Trie.h"

int main()
{
    TrieTree T;
    string w = " ";
    string words[] = { "we" ,"walk" ,"want","wish","wit","am", "yo" ,"will", "wee" ,"war" ,"warp" ,"win" };
    for (int i = 0; i < 12; i++)
        T.Insert(words[i]);
    T.printWord(w);
    for (int i = 0; i < 12; i++)
        T.Delete(words[i]);
    cout << "\n=========\n";
    T.printWord(w);
}