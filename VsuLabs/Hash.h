#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

typedef string CarNumber;

enum CellState {
    empty = 0,
    used = 1,
    deleted = -1,
};

enum Condition {
    park = 0,
    route = 1,
};

struct RouteDetail {
    CarNumber car_number;
    string company;
    string driver_fullname;
    int route_number;
    Condition condition;
};

struct Cell {
    CellState state;
    RouteDetail data;

    bool is_empty() { return state == CellState::empty; }
    bool is_used() { return state == CellState::used; }
};

class HashTable {
private:
    vector<Cell> table;
    int size;

    int HashFunc(CarNumber elem);
    int Probing(int func, int i);

public:
    HashTable(int size = 100);
    void AddElem(Cell elem);
    bool FindElem(CarNumber elem);
    void DeleteElem(CarNumber elem);
    void print();
};