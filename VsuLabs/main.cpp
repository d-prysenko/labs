#include <iostream>
#include <fstream>
#include <vector>
#include "Graph.hpp"

#define INPUT_FILENAME "input1.txt"
#define RECT_SIZE 5

struct Point
{
	int x, y;

	Point(int x = 0, int y = 0) : x(x), y(y) {}

	// расстояние до точки other
	float distance(const Point& other)
	{
		return sqrt((this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y));
	}

	// нужно для того, чтобы map и vector нормально с этой структурой работали
	bool operator<(const Point& other) const
	{
		int d1 = (this->x * this->x + this->y * this->y);
		int d2 = (other.x * other.x + other.y * other.y);

		if (d1 == d2 && this->x != 0 && other.x != 0)
			return (this->y / this->x) < (other.y / other.x);

		return d1 < d2;
	}
};

struct Rect
{
	Point p;

	Rect(int x, int y) : p(x, y) {}

	// возвращает координаты углов
	std::vector<Point> get_corner_points() const
	{
		std::vector<Point> res;
		res.push_back(Point(p.x, p.y));
		res.push_back(Point(p.x + RECT_SIZE, p.y));
		res.push_back(Point(p.x + RECT_SIZE, p.y + RECT_SIZE));
		res.push_back(Point(p.x, p.y + RECT_SIZE));
		return res;
	}
};


/// Introduction to Algorithms. Cormen.
/// page 1060
/// https://vk.com/doc179585542_437543470?hash=9MFJf53ZaQXuDrrM1ZbkmNBmYcV1MzgF69yWZIm4GVs&dl=zq2RlHBYgizrJh8qKRuuAzr4uHDrFdKhsmdZ7YzQ7wT

/// нужно будет проверять пересечения отрезков, эти функции взяты из книги по алгоритмам выше

/// BEGIN ///

float direction(Point p1, Point p2, Point p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

bool on_segment(Point p1, Point p2, Point p3)
{
	if (std::min(p1.x, p2.x) < p3.x && p3.x < std::max(p1.x, p2.x)
		&& std::min(p1.y, p2.y) < p3.y && p3.y < std::max(p1.y, p2.y))
		return true;
	return false;
}

bool segment_intersect(Point p1, Point p2, Point p3, Point p4)
{
	float d1 = direction(p3, p4, p1);
	float d2 = direction(p3, p4, p2);
	float d3 = direction(p1, p2, p3);
	float d4 = direction(p1, p2, p4);

	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0))
		&& ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
		return true;
	else if (d1 == 0 && on_segment(p3, p4, p1))
		return true;
	else if (d2 == 0 && on_segment(p3, p4, p2))
		return true;
	else if (d3 == 0 && on_segment(p1, p2, p3))
		return true;
	else if (d4 == 0 && on_segment(p1, p2, p4))
		return true;

	return false;
}
/// END ///


// возвращает список угловых точек квадрата, к которым можно провести отрезок от точки p, не пересекая сам квадрат
// это небольшая оптимизация, в принципе, если смущает, то можно забить на это и вместо это функции вызывать get_corner_points()
std::vector<Point> get_visible_corner_points(Point p, Rect rect)
{
	std::vector<Point> res;

	if (p.y >= rect.p.y +RECT_SIZE)
	{
		// два верхних угла
		res.push_back({ rect.p.x, rect.p.y +RECT_SIZE });
		res.push_back({ rect.p.x +RECT_SIZE, rect.p.y +RECT_SIZE });

		if (p.x <= rect.p.x)
			res.push_back({ rect.p.x, rect.p.y });
		else if (p.x >= rect.p.x +RECT_SIZE)
			res.push_back({ rect.p.x +RECT_SIZE, rect.p.y });
	}
	else if (p.y <= rect.p.y)
	{
		// два нижних угла
		res.push_back({ rect.p.x, rect.p.y });
		res.push_back({ rect.p.x +RECT_SIZE, rect.p.y });

		if (p.x <= rect.p.x)
			res.push_back({ rect.p.x, rect.p.y +RECT_SIZE });
		else if (p.x >= rect.p.x +RECT_SIZE)
			res.push_back({ rect.p.x +RECT_SIZE, rect.p.y +RECT_SIZE });
	}
	else
	{
		if (p.x <= rect.p.x)
		{
			res.push_back({ rect.p.x, rect.p.y });
			res.push_back({ rect.p.x, rect.p.y +RECT_SIZE });
		}
		else if (p.x >= rect.p.x +RECT_SIZE)
		{
			res.push_back({ rect.p.x +RECT_SIZE, rect.p.y });
			res.push_back({ rect.p.x +RECT_SIZE, rect.p.y +RECT_SIZE });
		}
	}
	
	return res;
}

// проверяем пересекает ли отрезок [from, to] какой-нибудь квадрат из rectangles
// если да, то возвращаем true
bool intersectins(Point from, Point to, std::vector<Rect> rectangles)
{
	for (const auto& rect : rectangles)
	{
		const auto& points = rect.get_corner_points();
		for (int i = 0; i < 4; ++i)
		{
			if (segment_intersect(from, to, points[i], points[(i + 1) % 4]))
				return true;
		}
	}

	return false;

}

int main()
{
	// логика такая:
	// 1) читаем из файла
	// 2) добавляем сразу сами квадраты в граф
	// 3) от угла каждого квадрата пытаемся построить отрезок к углу очередного квадрата
	// 3.1) если этот отрезок не пересекает никакой другой квадрат, то добавляем его в граф
	// 3.2) если этот отрезок пересекает что-то, то идет он нахуй
	// 4) ну и добавляем связи от вершин (0, 0) и (100, 100) к остальным
	// 5) с помощью алгоритма дейкстры ищем наименьшее расстояние

	setlocale(LC_ALL, "ru");

	std::cout << "Reading " INPUT_FILENAME "..\n";

	std::ifstream input_stream(INPUT_FILENAME);

	if (!input_stream)
	{
		std::cerr << "Error: cannot open input file(" INPUT_FILENAME ")\n";
		system("pause");
		return -1;
	}

	Graph<Point> g;
	std::vector<Rect> rectangles;
	int size;

	// 1) читаем из файла
	input_stream >> size;
	for (int i = 0; i < size; ++i)
	{
		int x, y;
		input_stream >> x >> y;
		rectangles.push_back(Rect(x, y));
	}

	// вдруг повезло и сразу можно построить дорогу от начала до конца без пересечений
	if (!intersectins(Point(0, 0), Point(100, 100), rectangles))
	{
		std::cout << "Distance: " << 100 * sqrt(2) << std::endl;
		std::cout << "Trace: (0; 0) (100; 100)" << std::endl;

		return 0;
	}	

	// 2) добавляем сразу сами квадраты в граф
	for (auto& rect : rectangles)
	{
		std::vector<Point> cur_rect = rect.get_corner_points();
		for (int i = 0; i < 4; ++i)
		{
			g.insert(cur_rect[i], cur_rect[(i + 1) % 4],RECT_SIZE);
		}
	}

	// 3) от угла каждого квадрата пытаемся построить отрезок к углу очередного квадрата
	for (int i = 0; i < rectangles.size(); ++i)
	{
		// j = i + 1 чтобы не возвращаться к тем квадратам, от которых уже и так посчитали расстояние до всех
		for (int j = i + 1; j < rectangles.size(); ++j)
		{
			std::vector<Point> cur_rect = rectangles[i].get_corner_points();

			for (int m = 0; m < 4; ++m)
			{
				// в этом месте можно написать .. = rectangles[j].get_corner_points()
				// но тогда будет на 1-2 точки больше, которые будут отсеиваться с помощью более сложных вычислений
				std::vector<Point> other_rect = get_visible_corner_points(cur_rect[m], rectangles[j]);
				for (int n = 0; n < other_rect.size(); ++n)
				{
					// 3.1) если этот отрезок не пересекает никакой другой квадрат, то добавляем его в граф
					if (!intersectins(cur_rect[m], other_rect[n], rectangles))
					{
						g.insert(cur_rect[m], other_rect[n], cur_rect[m].distance(other_rect[n]));
					}
				}
			}

			for (int m = 0; m < 4; ++m)
			{
				g.insert(cur_rect[m], cur_rect[(m + 1) % 4], cur_rect[m].distance(cur_rect[(m + 1) % 4]));
			}
		}
	}

	// 4) ну и добавляем связи от вершин (0, 0) и (100, 100) к остальным
	for (int i = 0; i < rectangles.size(); ++i)
	{
		std::vector<Point> cur_rect = get_visible_corner_points(Point(0, 0), rectangles[i]);
		for (int j = 0; j < cur_rect.size(); ++j)
		{
			if (!intersectins(Point(0, 0), cur_rect[j], rectangles))
			{
				g.insert(Point(0, 0), cur_rect[j], Point(0, 0).distance(cur_rect[j]));
			}
		}
	}

	// 4) ну и добавляем связи от вершин (0, 0) и (100, 100) к остальным
	for (int i = 0; i < rectangles.size(); ++i)
	{
		std::vector<Point> cur_rect = get_visible_corner_points(Point(100, 100), rectangles[i]);
		for (int j = 0; j < cur_rect.size(); ++j)
		{
			if (!intersectins(Point(100, 100), cur_rect[j], rectangles))
			{
				g.insert(Point(100, 100), cur_rect[j], Point(100, 100).distance(cur_rect[j]));
			}
		}
	}

	auto res = g._dijkstra(Point(0, 0), Point(100, 100));
	
	std::cout << "Distance: " << res.first << std::endl;
	std::cout << "Trace: ";
	for (const Point& p : res.second)
	{
		std::cout << "(" << p.x << "; " << p.y << ") ";
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}