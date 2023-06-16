#include <iostream>
#include <fstream>

int main()
{
    const int letterNumber = 13;
    const int numbers[letterNumber] { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    const std::string letters[letterNumber] { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

    int number = 0;
    std::cout << "Input number: ";
    std::cin >> number;

    std::string result = "";
    while (number > 0)
    {
        for (int i = 0; i < letterNumber; ++i)
        {
            while (number >= numbers[i])
            {
                result += letters[i];
                number -= numbers[i];
            }
        }
    }
    std::cout << "Result: " << result << std::endl;

    std::ofstream out;
    out.open("result.txt");
    if (out.is_open())
    {
        out << result;
    }
    out.close();

    return 0;
}