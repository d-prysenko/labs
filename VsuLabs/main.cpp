#include <iostream>
#include "Choice.h"
#include "Bubble.h"

void dump_container(Container* container)
{
    for (int i = 0; i < (*container).getSize(); i++)
    {
        printf("%.2f ", (*container).get(i));
    }
}

int main()
{
    setlocale(LC_ALL, "ru");

    int n;
    printf("Введите кол-во чисел\n");
    std::cin >> n;

    Container* p_bubble = new Bubble(n);
    Container* p_choice = new Choice(n);

    float num;
    printf("Введите числа:\n");
    for (int i = 0; i < n; i++)
    {
        printf(">> ");
        std::cin >> num;
        p_bubble->insert(num, i);
        p_choice->insert(num, i);
    }

    printf("p_bubble: ");
    dump_container(p_bubble);
    printf("\n");

    printf("p_choice: ");
    dump_container(p_choice);
    printf("\n");

    p_bubble->sort();
    p_choice->sort();

    printf("После сортировки:\n");

    printf("p_bubble: ");
    dump_container(p_bubble);
    printf("\n");

    printf("p_choice: ");
    dump_container(p_choice);
    printf("\n");

    p_bubble->foreach();
    p_choice->foreach();

    printf("После поэлементной обработки:\n");

    printf("p_bubble: ");
    dump_container(p_bubble);
    printf("\n");

    printf("p_choice: ");
    dump_container(p_choice);
    printf("\n");

    delete p_bubble;
    delete p_choice;

    system("pause");

	return 0;
}