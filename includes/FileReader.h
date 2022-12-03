#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

class FileReader
{
    private:
    public:
        FileReader() = default;
        std::vector<std::string> readLines(const std::string& fileName)
        {
            std::ifstream in(fileName, std::ios_base::in);
            std::string line{};
            std::vector<std::string> res {};
            while(std::getline(in, line))
            {
                res.push_back(line);
            }
            return res;
        }
        std::vector<std::pair<char, char>> readPairs(const std::string& fileName)
        {
            std::ifstream in(fileName, std::ios_base::in);
            std::string line{};
            std::vector<std::pair<char, char>> res {};
            while(std::getline(in, line))
            {
                std::pair<char, char> pair {line[0], line[2]};
                res.push_back(pair);
            }
            return res;
        }
};