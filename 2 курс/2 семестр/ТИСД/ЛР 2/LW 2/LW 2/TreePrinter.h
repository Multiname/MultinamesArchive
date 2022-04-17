#pragma once

#include "ExpressionTree.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <math.h>

class TreePrinter
{
public:
    TreePrinter() {}

    ~TreePrinter() {}

public:
    static void BeautifulPrint(DTAS::ExpressionTree &tree, bool isColored)
    {
        if (tree.IsEmpty()) { std::cout << "Tree is empty!" << std::endl; return; }
        int height = tree.GetHeight();
        int currentHeight { height };
        int n = 2 * std::pow(2, height + 1);

        std::queue<DTAS::ExpressionTree::Number*> queue;
        queue.push(tree._root);

        for (int i{}; i < height; i++)
        {
            for (int j{}; j < std::pow(2, i); ++j)
            {
                auto currentNode = queue.front();
                queue.pop();

                if (currentNode != NULL)
                {
                    queue.push(currentNode->left); 
                    queue.push(currentNode->right); 

                    if (isColored)
                    {
                        std::cout << (j % 2 == 0 ? "\033[30;42m" : "\033[30;41m");
                    }

                    std::string temp = currentNode->number;

                    int half_string_length = temp.length() / 2;
                    int half_output_width = n / 2;

                    int leading_spaces = half_output_width - half_string_length;
                    int post_spaces = (n - temp.length()) / 2;

                    std::cout << std::setw(leading_spaces) << " " 
                        << currentNode->number << std::setw(post_spaces) << " ";
                    if (isColored)
                    {
                        std::cout << "\033[0m";
                    }
                }
                else
                {
                    queue.push(NULL); 
                    queue.push(NULL); 
                    if (isColored)
                    {
                        std::cout << (j % 2 == 0 ? "\033[30;42m" : "\033[30;41m") 
                            << std::setw(n) << ' ' << "\033[0m";
                    }
                    else
                    {
                        std::cout << std::setw(n) << ' ';
                    }
                    
                }
            }

            n /= 2;
            std::cout << std::endl;
        }
    }
};
