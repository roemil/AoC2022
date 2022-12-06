#include <set>
#include <vector>
#include <string>
#include <iostream>
#include "../include/FileReader.h"

bool isCharSeen(const char& ch, const std::set<char>& set)
{
    return (set.count(ch) != 0);
}

int solveDay6(const std::string& line, int charCnt)
{
    std::set<char> seenChars {};

    int slowPointer = 0;
    int i = 0;
    while(i < line.size()-3)
    {
        auto ch = line[i];
        if(isCharSeen(ch, seenChars))
        {
            i = slowPointer - 1; // Since we automatically increment i after if-statement.
            ++slowPointer;
            seenChars.clear();
        }
        else
        {
            seenChars.insert(ch);
        }
        if(seenChars.size() == charCnt)
        {
            std::cout << "Index i: " << i+1 << std::endl;
            break;
        }
        i++;
    }
    return (i+1);
}


int main()
{
    FileReader fr;
    std::vector<std::string> readLines {fr.readLines("data/input_day6.txt")};
    auto line = readLines[0];
    assert(solveDay6(line, 4) == 1538);
    assert(solveDay6(line, 14) == 2315);
    return 0;
}