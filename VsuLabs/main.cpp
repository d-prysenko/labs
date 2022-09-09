#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "Trie.h"

void print_description()
{
	printf("4. В trie–дереве распечатать слово (или слова), содержащее наибольшее количество различных букв.\n\n");
}

int main()
{
	setlocale(LC_ALL, "ru");

	print_description();

	TrieTree trie;
	trie.Insert("hello");
	trie.Insert("world");
	trie.Insert("test");
	trie.Insert("of");
	trie.Insert("trie");
	trie.Insert("tree");

	std::map<std::string, int> characters_count;

	trie.ForEach([&characters_count](std::string word) {
		std::string temp = word;
		std::sort(temp.begin(), temp.end());
		int uniqueCount = std::unique(temp.begin(), temp.end()) - temp.begin();
		characters_count[word] = uniqueCount;
	});

	int max = 0;
	for (const auto& it : characters_count)
		max = std::max(max, it.second);

	printf("Максимальное количество различных букв:\n");
	for (const auto& it : characters_count)
		if (it.second == max)
			printf("%s - %d\n", it.first.c_str(), it.second);

	system("pause");

	return 0;
}