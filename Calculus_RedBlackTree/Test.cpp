#include "RedBlackTree.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    RedBlackTree tree;

    // ������� ��������� ���������� ��������
    int count = 10; // ���������� �����
    int min = 1;    // ����������� ��������
    int max = 100;  // ������������ ��������

    tree.InsertRandom(count, min, max);

    // ����������� ������
    std::cout << "������-������ ������:\n";
    tree.DisplayTree();

    // ��������� ������� ������
    int depth = tree.GetDepth();
    std::cout << "\n������� ������: " << depth << std::endl;

    return 0;
}