#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Hash.h"

using namespace std;

bool get_cell(ifstream& input, Cell& a);

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    ifstream input("hash.txt");
    setlocale(LC_ALL, "Russian");
    int work;
    cout << "0-Считать из файла" << endl <<
        "1 -Удалить элемент " << endl <<
        "2 -Найти элемент" << endl <<
        "3 -Вывести данные " << endl <<
        "4- Добавить элемент" << endl;


    cin >> work;
    HashTable* h = new HashTable(50);

    while (work != -1)
    {
        switch (work)
        {
        case 0:
        {
            Cell elem;
            while (!input.eof()) {

                if (get_cell(input, elem)) {
                    h->AddElem(elem);
                }
            }
            input.close();

            break;
        }
        case 1: {



            break;
        }
        case 2: {
            break;
        }
        case 3: {
            h->print();
            break;
        }
        }
    }

    system("pause");
    return 0;
}

bool get_cell(ifstream& input, Cell& a) {
    if (input.eof())
        return false;

    string line;

    getline(input, line, '\t');
    a.data.car_number = line;

    getline(input, line, '\t');
    a.data.company = line;

    getline(input, line, '\t');
    a.data.driver_fullname = line;

    getline(input, line, '\t');
    a.data.route_number = stoi(line);

    getline(input, line, '\n');
    if (line == "в парке")
        a.data.condition = park;
    else
        a.data.condition = route;

    return true;
}
