#include "SortInAscendingOrder.h"
#include <iostream>

void SortInAscendingOrder(int** matrix, int row, int column)
{
    int temp = 0; 
    bool exit = false; 
    std::cout << "Введите столбец для сортировки: ";
    int sortingColumn{};
    std::cin >> sortingColumn;

    while (sortingColumn > column-1 || sortingColumn < 0)
    {
        std::cout <<"Введен некорректный столбец\n" <<"Введите столбец для сортировки заново: ";
        std::cin >> sortingColumn;
    }

    while (!exit) 
    {
        exit = true;
        for (int i = 0; i < (row - 1); ++i)
        {
            if (matrix[i][sortingColumn] > matrix[i + 1][sortingColumn])
            {
                temp = matrix[i][sortingColumn];
                matrix[i][sortingColumn] = matrix[i + 1][sortingColumn];
                matrix[i + 1][sortingColumn] = temp;
                exit = false;
            }
        }
    }
    std::cout << std::endl;
}
