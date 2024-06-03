#include "RedBlackTree.h"

int main()
{
    RedBlackTree tree;

    // Вставка случайных уникальных значений
    int count = 10; // Количество узлов
    int min = 1;    // Минимальное значение
    int max = 100;  // Максимальное значение

    tree.InsertRandom(count, min, max);

    // Отображение дерева
    std::cout << "Красно-черное дерево:\n";
    tree.DisplayTree();

    // Получение глубины дерева
    int depth = tree.GetDepth();
    std::cout << "\nГлубина дерева: " << depth << std::endl;

    return 0;
}