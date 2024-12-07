#pragma once

#include "DayBase.h"
#include <string>
#include <string.h>
#include <vector>

template <>
class Day<4> : public DayBase
{
    struct Coord
    {
        size_t x, y;

        void Inc(int _x, int _y) { x += _x; y += _y; }
    };
private:
    void FindAll(char _c, const std::string& _s, size_t _y, std::vector<Coord>& _res)
    {
        size_t lastFound = std::string::npos;
        while (true)
        {
            lastFound = _s.find(_c, lastFound+1);
            if (lastFound == std::string::npos)
                return;
            
            _res.push_back(Coord{lastFound, _y});
        }
    }

    void ParseInput(std::ifstream& _input) override
    {
        std::string line;
        
        for (size_t y = 0; _input >> line; ++y)
        {
            FindAll('X', line, y, m_XCoords);
            FindAll('A', line, y, m_ACoords);
            m_Table.push_back(std::move(line));
        }
    }

    bool IsStringValid(Coord _c, const std::string& _val, int _dx, int _dy)
    {
        std::string s;
 
        for (int i = 0; i < _val.length(); ++i)
        {
            try
            {
                s += m_Table.at(_c.y)[_c.x];
            }
            catch(const std::exception& e)
            {
                (void)e;
                return false;
            }

            _c.Inc(_dx, _dy);
        }
        return s == _val;
    }

    int GetNumberOfStringInTableAt(std::string _val, const Coord& _c)
    {
        int res = 0;
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;
                
               if (IsStringValid(_c, _val, dx, dy))
                   ++res;
            }
        }
        return res;
    }

    size_t ProcessInput1() override
    {
        int sum = 0;
        for (Coord& c : m_XCoords)
        {
            sum += GetNumberOfStringInTableAt("XMAS", c);
        }
        return sum;
    }

    bool IsX_MAS(const Coord& _c)
    {
        int nbMas = 0;
        for (int dx = -1; dx <= 1; dx+=2)
        {
            for (int dy = -1; dy <= 1; dy+=2)
            {
                Coord c = _c;
                c.Inc(dx, dy);
                if (IsStringValid(c, "MAS", -dx, -dy))
                {
                    ++nbMas;
                }
            }
        }

        return nbMas >= 2;
    }

    size_t ProcessInput2() override
    {
        int sum = 0;
        for (Coord& c : m_ACoords)
        {
            if (IsX_MAS(c))
                ++sum;
        }
        return sum;
    }
private:
    std::vector<std::string> m_Table;
    std::vector<Coord> m_XCoords;
    std::vector<Coord> m_ACoords;
};