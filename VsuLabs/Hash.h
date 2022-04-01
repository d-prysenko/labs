#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

typedef string type;

enum Status {
    empty = 0,
    used = 1,
    deleted = -1,
};
enum Condition {
    park = 0,
    route = 1,
};
struct cell {
    type data;
    Status status;
    string company;
    string fullnamedriver;
    int routenumber;
    Condition condition;
};

class HashTable {
    vector<cell>table;
    int size;
public:
    HashTable(int SIZE);
    int HashFunc(type elem);
    int Probing(int func, int& i);
    void AddElem(cell elem);
    bool FindElem(type elem);
    void DeleteElem(type elem);
    void print();
    bool get_cell(ifstream& input, cell& a);

};