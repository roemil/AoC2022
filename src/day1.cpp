#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../includes/FileReader.h"

bool comp(int i, int j)
{
    return i > j;
}

int main(int argc, char *argv[])
{
    FileReader fr {};
    std::vector<std::string> readLines {fr.readLines("data/input_day1.txt")};
    int currentCal {0};
    std::vector<int> calVector {};
    for(std::string& line : readLines)
    {
        if(line.empty())
        {
            calVector.push_back(currentCal);
            currentCal = 0;
        }else
        {
            currentCal += std::stoi(line);
        }
    }

    std::sort(calVector.begin(), calVector.end(), comp);
    std::cout << "Part1: maxCal: " << calVector[0] << std::endl;
    std::cout << "Part2: Sum of top 3: " << calVector[0] + calVector[1] + calVector[2] << std::endl;

    return 0;
}