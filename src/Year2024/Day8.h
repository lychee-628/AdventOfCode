#pragma once
#include "DayBase.h"

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

template <>
class Day<8> : public DayBase
{
    struct Coord
    {
        size_t x, y;

        Coord operator-(const Coord& _c2) const
        {
            return Coord{ x - _c2.x, y - _c2.y };
        }

        Coord operator+(const Coord& _c2) const
        {
            return Coord{ x + _c2.x, y + _c2.y };
        }

        bool InBounds(Coord _c) const
        {
            return x < _c.x && y < _c.y;
        }
    };

public:
    
    void ParseInput(std::ifstream& _input)
    {
        std::string s;
        Coord coord{0, 0};
        while (_input >> s)
        {
            m_mapEdge.x = s.size();
            for (char c : s)
            {

                if (c != '.')
                {
                    m_antennas[c].push_back(coord);
                }
                coord.x++;
            }

            coord.x = 0;
            coord.y++;
        }
        m_mapEdge.y = coord.y;
        //std::cout << "MAP EDGE : " << m_mapEdge.x << ", " << m_mapEdge.y << "\n";
    }

    void GetAntipodes(const std::vector<Coord>& _coords, std::vector<std::vector<bool>>& _result, size_t& _newAntipodesCount)
    {
        _newAntipodesCount = 0;
        for (auto c1 = _coords.begin(); c1 != _coords.end(); ++c1)
        {
            for (auto c2 = _coords.begin(); c2 != _coords.end(); ++c2)
            {
                if (c1 == c2)
                    continue;

                Coord diff = (*c1) - (*c2);
                Coord antipode = (*c1) + diff;
                if (antipode.InBounds(m_mapEdge) && _result[antipode.y][antipode.x] == false)
                {
                    _newAntipodesCount++;
                    _result[antipode.y][antipode.x] = true;
                }
            }

        }
    }

    size_t ProcessInput1()
    {
        size_t s = 0;
        
        std::vector<std::vector<bool>> antipodesLocations(m_mapEdge.y, std::vector<bool>(m_mapEdge.x, false));

      
        for (auto& [c, vec] : m_antennas)
        {
            size_t count = 0;
            GetAntipodes(vec, antipodesLocations, count);

            s += count;
        }

        return s;
    }

    void GetAntipodes2(const std::vector<Coord>& _coords, std::vector<std::vector<bool>>& _result, size_t& _newAntipodesCount)
    {
        _newAntipodesCount = 0;
        for (auto c1 = _coords.begin(); c1 != _coords.end(); ++c1)
        {
            for (auto c2 = _coords.begin(); c2 != _coords.end(); ++c2)
            {
                if (c1 == c2)
                    continue;

                Coord diff = (*c1) - (*c2);
                Coord antipode = (*c1);
                
                while (antipode.InBounds(m_mapEdge))
                {
                    if (_result[antipode.y][antipode.x] == false)
                    {
                        _newAntipodesCount++;
                        _result[antipode.y][antipode.x] = true;
                    }
                    antipode = antipode + diff;
                }
            }

        }
    }

    size_t ProcessInput2()
    {
        size_t s = 0;

        std::vector<std::vector<bool>> antipodesLocations(m_mapEdge.y, std::vector<bool>(m_mapEdge.x, false));


        for (auto& [c, vec] : m_antennas)
        {
            size_t count = 0;
            GetAntipodes2(vec, antipodesLocations, count);

            s += count;
        }

        return s;
    }

private:
    std::unordered_map<char, std::vector<Coord>> m_antennas;
    Coord m_mapEdge;
};