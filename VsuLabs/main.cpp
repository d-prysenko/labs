#include "Trie.h"
#include <algorithm>
#include <list>
int main()
{
	TrieTree T;
	string w = " ";
	string words[] = { "we" ,"walk" ,"want","wa","wish","wit","am", "yo" ,"will", "wee" ,"war" ,"warp" ,"win" };

	for (int i = 0; i < 12; i++)
		T.Insert(words[i]);

	T.ForEach([](string value) { cout << value << endl; });

	cout << "\n=========\n";

	T.EraseIf([](string value) {
		return value.length() % 2 == 0;
	});
		
	T.ForEach([&T](string value) { cout << value << endl; });

	cout << "\n=========\n";

	T.printWord(w);

	system("pause");
}