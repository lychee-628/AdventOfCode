#pragma once
#include "DayBase.h"

#include <vector>
#include <string>
#include <algorithm>

template <>
class Day<10> : public DayBase
{
    struct Coord
    {
        size_t x, y;
    };

    void ParseInput(std::ifstream& _input)
    {
        std::string line;
        size_t y = 0;
        while (_input >> line)
        {
            std::vector<size_t> l;
            l.reserve(line.size());

            size_t x = 0;            
            for (char c : line)
            {
                l.emplace_back((size_t)(c - '0'));
                if (c == '0')
                {
                    m_trailheads.emplace_back(x, y);
                }

                ++x;
            }
            m_heightMap.emplace_back(std::move(l));
            ++y;
        }
    }

    size_t TrailScore(Coord _c, std::vector<std::vector<bool>>* _table)
    {
        size_t res = 0;

        if (m_heightMap[_c.y][_c.x] == 9)
        {
            if (_table)
            {
                if ((*_table)[_c.y][_c.x] == false)
                {
                    (*_table)[_c.y][_c.x] = true;
                    return 1;
                }
                return 0;
            }
            return 1;
        }
        
        Coord neighbours[4] = {Coord{_c.x, _c.y-1}, Coord{_c.x, _c.y+1}, Coord{_c.x+1, _c.y}, Coord{_c.x-1, _c.y}};
        
        for (Coord& n : neighbours)
        {
            try //Shhh it just works
            {
                if (m_heightMap.at(n.y).at(n.x) == m_heightMap.at(_c.y).at(_c.x)+1)
                    res += TrailScore(n, _table);
            }
            catch(const std::exception& e)
            {
                (void)e;
            }
            
        }
        
        return res;
    }

    size_t ProcessInput1()
    {
        size_t sum = 0;
        for (const Coord& c : m_trailheads)
        {
            std::vector<std::vector<bool>> table(m_heightMap.size(), std::vector<bool>(m_heightMap[0].size(), false));
            sum += TrailScore(c, &table);
        }
        return sum;
    }

    size_t ProcessInput2()
    {
        size_t sum = 0;
        for (const Coord& c : m_trailheads)
        {
            sum += TrailScore(c, NULL);
        }
        return sum;
    }

private:
    std::vector<std::vector<size_t>> m_heightMap;
    std::vector<Coord> m_trailheads;
};