#include "../include/FileReader.h"
#include <iostream>
#include <deque>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

void printQueue(std::deque<char> q)
{
  while (!q.empty())
  {
    std::cout << q.front() << " ";
    q.pop_front();
  }
  std::cout << std::endl;
}

void printFirstElemInQueue(std::vector<std::deque<char>> stackVec)
{
    for(const auto& q : stackVec)
    {
        std::cout << q.front();
    }
    std::cout << std::endl;
}

void part1(const int& num, const int& from, const int& to, std::vector<std::deque<char>>& stackVec)
{
    for(int j = 0; j < num; ++j)
    {
        auto elemToMove {stackVec[from-1].front()};
        stackVec[from-1].pop_front();
        stackVec[to-1].push_front(elemToMove);
    }
}

void part2(const int& num, const int& from, const int& to, std::vector<std::deque<char>>& stackVec)
{
    if(num == 1)
    {
        part1(num, from, to, stackVec);
    }
    else
    {
        std::deque<char> tmp {};
        for(int j = 0; j < num; ++j)
        {
            auto elemToMove {stackVec[from-1].front()};
            stackVec[from-1].pop_front();
            tmp.push_back(elemToMove);
        }
        for(int j = 0; j < num; ++j)
        {
            auto elemToMove = tmp.back();
            stackVec[to-1].push_front(elemToMove);
            tmp.pop_back();
        }
    }
}

void solvePart(const bool& usePart1, const std::vector<std::string>& readLines, std::vector<std::deque<char>> stackVec)
{
    for(int i = 10; i < 511; ++i)
    {
        auto line = readLines[i];
        std::stringstream ss {line};
        int num;
        int from;
        int to;
        std::string dummy;
        ss >> dummy >> num >> dummy >> from >> dummy >> to;
        if(usePart1)
        {
            part1(num, from, to, stackVec);
        }else
        {
            part2(num, from, to, stackVec);
        }
    }
    auto strToPrint = usePart1 ? "Part 1: " : "Part 2: ";
    std::cout << strToPrint;
    printFirstElemInQueue(stackVec);
}

int main()
{
    FileReader fr;
    auto readLines = fr.readLines("data/input_day5.txt");

    auto line = readLines[3];

    std::vector<std::deque<char>> stackVec {9};
    size_t pos = 0;
    std::string delimiter { '[' };
    char token;

    for(int i = 0; i < 8; ++i)
    {
        line = readLines[i];
        int queueInd = 0;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            queueInd += pos / 4;
            token = line[pos+1];
            line.erase(0, pos + delimiter.length());
            stackVec[queueInd++].push_back(token);
        }
    }

    solvePart(true, readLines, stackVec);
    solvePart(false, readLines, stackVec);
}