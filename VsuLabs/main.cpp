#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Hash.h"

using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    ifstream input("hash.txt");
    setlocale(LC_ALL, "Russian");
    int work;
    cout << "0-������� �� �����" << endl <<
        "1 -������� ������� " << endl <<
        "2 -����� �������" << endl <<
        "3 -������� ������ " << endl <<
        "4- �������� �������" << endl;


    cin >> work;
    HashTable* h = new HashTable(1);

    while (work != -1)
    {
        switch (work)
        {
        case 0:
        {
            cell elem;
            while (!input.eof()) {

                if (h->get_cell(input, elem)) {
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


        system("pause");
        return 0;
    }
}