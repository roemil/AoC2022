#include "../../include/FileReader.h"
#include <string>
#include <iostream>
#include <set>

// void print(const std::vector<std::vector<int>>& readLines)
// {
//     for(int i = 0; i < numRows; ++i)
//     {
//         for(int j = 0; j < numCols; ++j)
//         {
//             std::cout << readLines[i][j];
//         }
//         std::cout << std::endl;
//     }
// }

int part1()
{
    FileReader fr;
    auto readLines {fr.readLinesAsInt("input_day8.txt")};

    // Count outer layer
    // numCol * 2 + numRows * 2 - 4;
    int numRows = readLines.size();
    int numCols = readLines[0].size();

    std::cout << "numRows: " << numRows << " numCols: " << numCols << std::endl;
    int outerVisible = numCols * 2 + 2 * (numRows - 2);
    std::cout << "outerVisible: " << outerVisible << std::endl;

    std::set<std::pair<int, int>> visible{};

    // Left to right
    for(int i = 1; i < numRows-1; ++i)
    {
        auto max = 0;
        for(int j = 0; j < numCols-1; ++j)
        {
            max = std::max(max, readLines[i][j]);
            if(max < readLines[i][j+1])
            {
                visible.insert(std::pair(j+1,i));
            }
        }
    }

    // top to bottom
    for(int j = 1; j < numCols-1; ++j)
    {
        auto max = 0;
        for(int i = 0; i < numRows-1; ++i)
        {
            max = std::max(max, readLines[i][j]);
            if(max < readLines[i+1][j])
            {
                visible.insert(std::pair(j,i+1));
            }
        }
    }

    // Right to left
    for(int i = 1; i < numRows-1; ++i)
    {
        auto max = 0;
        for(int j = numCols-1; j > 0; --j)
        {
            max = std::max(max, readLines[i][j]);
            if(max < readLines[i][j-1])
            {
                visible.insert(std::pair(j-1,i));
            }
        }
    }

    // bottom to top
    for(int j = 1; j < numCols-1; ++j)
    {
        auto max = 0;
        for(int i = numRows-1; i > 0; --i)
        {
            max = std::max(max, readLines[i][j]);
            if(max < readLines[i-1][j])
            {
                visible.insert(std::pair(j, i-1));
            }
        }
    }
    return outerVisible + visible.size();
}

int main()
{
    std::cout << "Part1: " << part1() << std::endl;
}