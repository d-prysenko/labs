#include <iostream>
#include "Hash.h"
#include <fstream>

HashTable::HashTable(int SIZE)
{
    size = SIZE;
    table.resize(size);
    for (int i = 0; i < size; i++) {
        table[i].status = Status::empty;
    }
}

int HashTable::HashFunc(type elem)
{
    int p = 31;
    int pow = 1;
    int i = 0;
    long int rez = 0;
    for (i = 0; i < elem.length(); i++) {
        rez += (elem[i] - '0' + 1) * pow;
        pow *= p;
    }
    return rez % size;
}

int HashTable::Probing(int func, int& i)
{
    int c = 1;
    int d = 1;
    for (int i = 1; i < size; i++) {
        func = func + c * i + i * i * d;
    }
    func = func % size;
    d++;
    return func;
}

void HashTable::AddElem(cell elem)
{
    int i = 1;
    int hash_0 = HashFunc(elem.data);
    int hash_i = hash_0;
    if (size < hash_0) {
        table.resize(hash_0 + 1);
    }
    else {
        while (table[hash_i].status == used) {
            hash_i = Probing(hash_0, i);
        }

    }
    table[hash_i] = elem;
    table[hash_i].status = Status::used;
}

bool HashTable::FindElem(type elem)
{
    bool isfind = false;
    int hash_0 = HashFunc(elem);
    int hash_i = hash_0;
    int i = 1;
    while (table[hash_i].status != Status::empty && isfind != true) {
        if (table[hash_i].status == Status::used && table[hash_i].data == elem) isfind = true;
        hash_i = Probing(hash_0, i);
    }
    return isfind;
}

void HashTable::DeleteElem(type elem)
{
    int hash_0 = HashFunc(elem);
    int hash_i = hash_0;
    int i = 1;
    while (table[hash_i].status != Status::empty) {
        if (table[hash_i].status == Status::used && table[hash_i].data == elem) table[hash_i].status = Status::deleted;
        hash_i = Probing(hash_0, i);
    }
}
void HashTable::print()
{
    for (int i = 0; i < size; i++) {

        if (table[i].status == Status::used)
            cout << table[i].data << " " << table[i].company << " " << table[i].fullnamedriver << " " << table[i].routenumber << " " << table[i].condition;
    }
}
bool HashTable::get_cell(ifstream& input, cell& a) {
    if (input.eof()) {
        return false;
    }
    else {
        string line;


        getline(input, line, '\t');
        a.data = line;
        getline(input, line, '\t');
        a.company = line;
        getline(input, line, '\t');
        a.fullnamedriver = line;
        getline(input, line, '\t');
        a.fullnamedriver = stoi(line);
        getline(input, line, '\n');
        if (line == "в парке") {
            a.condition = park;
        }
        else
            a.condition = route;


        return true;
    }

}
