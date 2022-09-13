#include <iostream>
#include <istream>
#include <sstream>
#include "Graph.hpp"

// 11. На олимпиаду прибыло N человек. Некоторые из них знакомы между собой.
// Можно ли опосредованно перезнакомить их всех между собой ? (Незнакомые люди
// могут познакомиться только через общего знакомого).

void print_description()
{
	printf("11. На олимпиаду прибыло N человек. Некоторые из них знакомы между собой.\n");
	printf("Можно ли опосредованно перезнакомить их всех между собой ? (Незнакомые люди\n");
	printf("могут познакомиться только через общего знакомого).\n\n");
}

template<typename T>
void dfs(Graph<T> g, int i, bool* used)
{	
	used[i] = true;
	for (int v = 0; v < g.get_last_id(); ++v)
		if (g[i][v] && !used[v])
			dfs(g, v, used);
}

template<typename T>
int get_graph_component(Graph<T> g)
{
	int comp = 0;
	bool* used = new bool[g.get_last_id()];

	for (int i = 0; i < g.get_last_id(); ++i)
		used[i] = false;

	for (int i = 0; i < g.get_last_id(); ++i)
	{
		if (!used[i])
		{
			++comp;
			dfs(g, i, used);
		}
	}

	delete[] used;

	return comp;
}

template<typename T>
void load_graph_from_file(Graph<T>& g, std::string filename)
{
	std::ifstream s_input(filename);

	if (!s_input)
	{
		fprintf(stderr, "Error: could not open input file '%s'\n", filename.c_str());
		exit(-1);
	}

	std::string str;
	while (std::getline(s_input, str))
	{
		std::stringstream ss;
		ss << str;

		std::string from, to;

		std::getline(ss, from, ' ');
		std::getline(ss, to, ' ');

		g.insert(std::stoi(from), std::stoi(to));
	}

	s_input.close();
}

int main()
{
	setlocale(LC_ALL, "ru");

	print_description();

	Graph<int> g;
	load_graph_from_file(g, "graph.txt");

	g.print_debug();

	int components = get_graph_component(g);

	printf("Число компонент связности: %d\n", components);
	printf("Людей %s перезнакомить  опосредованно\n", components != 1 ? "нельзя" : "можно");

	system("pause");
	return 0;
}