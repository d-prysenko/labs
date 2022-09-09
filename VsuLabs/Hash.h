#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

enum CellState {
    empty = 0,
    used = 1,
    deleted = -1,
};

struct Person {
    string number;
    string fullname;
    double salary;
};

struct Cell {
    CellState state;
    Person data;

    bool is_empty() { return state == CellState::empty; }
    bool is_used() { return state == CellState::used; }
};

class HashTable {
private:
    vector<Cell> table;
    int size;

    int HashFunc(string elem);
    int Probing(int func, int i);

public:
    HashTable(int size = 100);
    void AddElem(Cell elem);
    bool FindElem(string elem);
    void DeleteElem(string elem);
    void print();
};