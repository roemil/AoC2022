#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "includes/FileReader.h"

int mapShapeToPoints(const char& myHand)
{
    switch(myHand)
    {
        case 'X':
            return 1;
        case 'Y':
            return 2;
        case 'Z':
            return 3;
        default:
            return INT_MIN;
    }
}

int countGameOutcome(const char& A, const char& B)
{
    std::map<std::pair<char, char>, int> map {};
    map.insert(std::pair {std::pair<char, char> {'A', 'Z'}, 0});
    map.insert(std::pair {std::pair<char, char> {'A', 'Y'}, 6});
    map.insert(std::pair {std::pair<char, char> {'A', 'X'}, 3});

    map.insert(std::pair {std::pair<char, char> {'B', 'X'}, 0});
    map.insert(std::pair {std::pair<char, char> {'B', 'Y'}, 3});
    map.insert(std::pair {std::pair<char, char> {'B', 'Z'}, 6});

    map.insert(std::pair {std::pair<char, char> {'C', 'X'}, 6});
    map.insert(std::pair {std::pair<char, char> {'C', 'Y'}, 0});
    map.insert(std::pair {std::pair<char, char> {'C', 'Z'}, 3});

    return map[std::pair<char, char> {A, B}];

}

int part1(std::vector<std::pair<char, char>> readLines)
{
    int score {0};
    for(auto& pair : readLines)
    {
        score += mapShapeToPoints(pair.second) + countGameOutcome(pair.first, pair.second);
    }
    return score;
}

int part2Strategy(const char& me)
{
    switch (me)
    {
    case 'X':
        return 0;
    case 'Y':
        return 3;
    case 'Z':
        return 6;
    default:
        return INT_MIN;
    }
}

int selectHandReturnPoints(int opp, int me)
{
    std::map<char, int> strategy {};
    switch(opp)
    {
        case 'A':
            strategy.insert({std::pair<char, int> {'X', 3}});
            strategy.insert({std::pair<char, int> {'Y', 1}});
            strategy.insert({std::pair<char, int> {'Z', 2}});
            break;
        case 'B':
            strategy.insert({std::pair<char, int> {'X', 1}});
            strategy.insert({std::pair<char, int> {'Y', 2}});
            strategy.insert({std::pair<char, int> {'Z', 3}});
            break;
        case 'C':
            strategy.insert({std::pair<char, int> {'X', 2}});
            strategy.insert({std::pair<char, int> {'Y', 3}});
            strategy.insert({std::pair<char, int> {'Z', 1}});
            break;
    }

    return strategy[me];
}

int part2(std::vector<std::pair<char, char>> readLines)
{
    int score {0};
    for(auto& pair : readLines)
    {
        score += selectHandReturnPoints(pair.first, pair.second) + part2Strategy(pair.second);
    }
    return score;
}

int main(int argc, char *argv[])
{
    FileReader fr {};
    std::vector<std::pair<char, char>> readLines {fr.readPairs("input_day2.txt")};
    
    std::cout << "Part1: " << part1(readLines) << std::endl;
    std::cout << "Part2: " << part2(readLines) << std::endl;;
    assert(part1(readLines) == 11449);
    assert(part2(readLines) == 13187);

    return 0;
}