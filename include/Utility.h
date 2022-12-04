#pragma once

namespace Utility
{
std::vector<char> setIntersection(std::set<char> set1, std::set<char> set2)
{
    std::vector<char> intersection {};
    for(auto it = set1.begin(); it != set1.end(); ++it)
    {
        if((set2.count(*it) != 0))
        {
            intersection.push_back(*it);
        }
    }
    return intersection;
}

template<class T>
std::set<T> vectorToSet(std::vector<T> vec)
{
    std::set<T> s {};
    for(auto& val : vec)
    {
        s.insert(val);
    }
    return s;
}
}