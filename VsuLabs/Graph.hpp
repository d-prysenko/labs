#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

template<class _Ty>
using Matrix = std::vector<std::vector<_Ty>>;

template<class T, class _Ty = int>
class Graph
{
public:
	Graph();

	int get_order();
	Matrix<_Ty> get_adjacency_matrix();
	int get_last_id();

	void insert(T from, T to, _Ty weight = 1);

	void print_debug();

	std::vector<T> operator[](int key) const
	{
		return _adjacencyMatrix[key];
	}

private:

	std::map<T, int> _vertices;
	int _vertex_uid = 0;
	Matrix<_Ty> _adjacencyMatrix;

	void add_vertex(T vertex);

};



template<class T, class _Ty>
Graph<T, _Ty>::Graph()
{
	int _order = 50;
	_adjacencyMatrix.resize(_order);
	for (int i = 0; i < _order; i++)
	{
		_adjacencyMatrix[i].resize(_order);
		for (int j = 0; j < _order; j++)
			_adjacencyMatrix[i][j] = 0;
	}
}

// Возвращает порядок
template<class T, class _Ty>
int Graph<T, _Ty>::get_order()
{
	return _vertices.size();
}

template<class T, class _Ty>
int Graph<T, _Ty>::get_last_id()
{
	return _vertex_uid;
}

template<class T, class _Ty>
Matrix<_Ty> Graph<T, _Ty>::get_adjacency_matrix()
{
	return _adjacencyMatrix;
}

template<class T, class _Ty>
void Graph<T, _Ty>::insert(T from, T to, _Ty weight)
{
	add_vertex(from);
	add_vertex(to);

	_adjacencyMatrix[_vertices[from]][_vertices[to]] = weight;
	_adjacencyMatrix[_vertices[to]][_vertices[from]] = weight;
}

template<class T, class _Ty>
void Graph<T, _Ty>::add_vertex(T vertex)
{
	if (_vertices.find(vertex) == _vertices.end())
	{
		_vertices[vertex] = _vertex_uid++;
	}
}

template<class T, class _Ty>
void Graph<T, _Ty>::print_debug()
{

	//printf("Вершины графа:\n");
	//for (auto& v : _vertices)
	//{
	//	printf("%d %d\n", v.first.x, v.first.y);
	//}
	//printf("\n");

	printf("Матрица смежности:\n");
	for (int i = 0; i < get_order(); i++)
	{
		for (int j = 0; j < get_order(); j++)
			printf("%.0f ", (_adjacencyMatrix[i][j] == FLT_MAX) ? 0.0 : _adjacencyMatrix[i][j]);
		printf("\n");
	}
}