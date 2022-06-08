#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

template<class T>
using Matrix = std::vector<std::vector<T>>;

template<class T>
class Graph
{
public:
	Graph();

	int getOrder();

	void insert(T from, T to, float weight);
	void add_vertex(T vertex);

	std::pair<float, std::vector<T>> _dijkstra(T from, T to);

	// тебе это не пригодится, смело удаляй
	std::string export_to()
	{
		std::stringstream res;

		for (int i = 0; i < getOrder(); i++)
		{
			for (int j = 0; j < getOrder(); j++)
			{
				if (_adjacencyMatrix[i][j] != FLT_MAX)
				{
					auto v1 = std::find_if(_vertices.begin(), _vertices.end(), [&i](const auto& val) {return val.second == i; });
					auto v2 = std::find_if(_vertices.begin(), _vertices.end(), [&j](const auto& val) {return val.second == j; });

					res << "{" << (*v1).first.x << ", " << (*v1).first.y << ", " << (*v2).first.x << ", " << (*v2).first.y << "}, ";
				}
			}
		}

		return res.str();
	}

	// это тоже выпили
	void print_debug();

private:

	std::map<T, int> _vertices;
	int _vertex_uid = 0;
	Matrix<float> _adjacencyMatrix;

	

};



template<class T>
Graph<T>::Graph()
{
	int _order = 50;
	_adjacencyMatrix.resize(_order);
	for (int i = 0; i < _order; i++)
	{
		_adjacencyMatrix[i].resize(_order);
		for (int j = 0; j < _order; j++)
			_adjacencyMatrix[i][j] = FLT_MAX;
	}
}

// Возвращает порядок
template<class T>
int Graph<T>::getOrder()
{
	return _vertices.size();
}

template<class T>
void Graph<T>::insert(T from, T to, float weight)
{
	if (_vertices.find(from) == _vertices.end())
	{
		add_vertex(from);
	}

	if (_vertices.find(to) == _vertices.end())
	{
		add_vertex(to);
	}

	_adjacencyMatrix[_vertices[from]][_vertices[to]] = weight;
	_adjacencyMatrix[_vertices[to]][_vertices[from]] = weight;
}

template<class T>
void Graph<T>::add_vertex(T vertex)
{
	_vertices[vertex] = _vertex_uid++;
}

template<class T>
void Graph<T>::print_debug()
{

	printf("Вершины графа:\n");
	for (auto& v : _vertices)
	{
		printf("%d %d\n", v.first.x, v.first.y);
	}
	printf("\n");

	printf("Матрица смежности:\n");
	for (int i = 0; i < getOrder(); i++)
	{
		for (int j = 0; j < getOrder(); j++)
			printf("%.0f ", (_adjacencyMatrix[i][j] == FLT_MAX) ? 0.0 : _adjacencyMatrix[i][j]);
		printf("\n");
	}
}

// Алгоритм Дейкстры, возвращает массив расстояний от вершины src
template<class T>
std::pair<float, std::vector<T>> Graph<T>::_dijkstra(T from, T to)
{
	int order = getOrder();

	bool* visited = new bool[order];
	std::vector<float> D;

	std::vector<std::vector<T>> trace;
	trace.resize(50);

	for (int i = 0; i < order; ++i)
	{
		trace[i].push_back(from);
	}

	// Инициализация результирующего массива, на всех вершинах временные метки
	for (int i = 0; i < order; i++)
	{
		D.push_back(_adjacencyMatrix[_vertices[from]][i]);
		visited[i] = false;
	}

	D[_vertices[from]] = 0;
	int index = 0, u = 0;
	for (int i = 0; i < order; i++)
	{
		// Поиск наименьшего расстояния, среди вершин с временными метками
		float min = FLT_MAX;
		for (int j = 0; j < order; j++)
		{
			if (!visited[j] && D[j] < min)
			{
				min = D[j];
				index = j;
			}
		}
		u = index;
		visited[u] = true;
		// Обновление расстояний для вершин с временными метками с учетом найденного на предыдущем шаге наименьшего расстояния
		for (int j = 0; j < order; j++)
		{
			if (!visited[j] && _adjacencyMatrix[u][j] != FLT_MAX && D[u] != FLT_MAX && (D[u] + _adjacencyMatrix[u][j] < D[j]))
			{
				D[j] = D[u] + _adjacencyMatrix[u][j];
				trace[j] = trace[u];
				auto v1 = std::find_if(_vertices.begin(), _vertices.end(), [&j](const auto& val) {return val.second == j; });
				auto v2 = std::find_if(_vertices.begin(), _vertices.end(), [&u](const auto& val) {return val.second == u; });
				if (v1 != _vertices.end() && v2 != _vertices.end())
				{
					trace[j].push_back((*v2).first);
				}

			}
		}
	}

	trace[_vertices[to]].push_back(to);

	delete[] visited;
	return std::pair<float, std::vector<T>>(D[_vertices[to]], trace[_vertices[to]]);
}