#include <iostream>
#include "Hash.h"
#include <fstream>

HashTable::HashTable(int size)
    : size(size)
{
    table.resize(size);
    for (int i = 0; i < size; i++) {
        table[i].state = CellState::empty;
    }
}

int HashTable::HashFunc(string elem)
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

int HashTable::Probing(int hash_0, int i)
{
    const int c = 1;
    const int d = 3;

    return (hash_0 + i * c + i * i * d) % size;
}

void HashTable::AddElem(Cell elem)
{
    int i = 1;
    int hash_0 = HashFunc(elem.data.number);
    int hash_i = hash_0;

    while (table[hash_i].is_used()) {
        hash_i = Probing(hash_0, i++);
    }

    table[hash_i] = elem;
    table[hash_i].state = CellState::used;
}

bool HashTable::FindElem(string number)
{
    bool is_found = false;
    int hash_0 = HashFunc(number);
    int hash_i = hash_0;
    int i = 1;
    while (!table[hash_i].is_empty() && is_found != true)
    {
        if (table[hash_i].is_used() && table[hash_i].data.number == number)
            is_found = true;

        hash_i = Probing(hash_0, i++);
    }
    return is_found;
}

void HashTable::DeleteElem(string number)
{
    int hash_0 = HashFunc(number);
    int hash_i = hash_0;
    int i = 1;
    while (!table[hash_i].is_empty())
    {
        if (table[hash_i].is_used() && table[hash_i].data.number == number)
            table[hash_i].state = CellState::deleted;

        hash_i = Probing(hash_0, i++);
    }
}
void HashTable::print()
{
    for (int i = 0; i < size; i++) {

        if (table[i].is_used())
        {
            cout <<
                table[i].data.number << " " <<
                table[i].data.fullname << " " <<
                table[i].data.salary << endl;
        }
    }
}