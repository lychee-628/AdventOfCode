#pragma once
#include "DayBase.h"

#include <list>
#include <string>
#include <algorithm>
#include <cmath>

/*

a = (X - X2b)/X1
b = (YX1 - Y1X)/(Y2X1 - Y1X2)


//
If (YX1 - Y1X) % (Y2X1 - Y1X2) != 0, impossible
If (X - X2b) % X1 != 0, impossible
If a < 0 or b < 0, impossible


*/

template <>
class Day<12> : public DayBase
{
public:
    struct Coord
    {
        size_t x, y;
    };

    struct Elem
    {
        char c;
        bool marked;
    };
    
    using MapType = std::vector<std::vector<Elem>>;

    void ParseInput(std::ifstream& _input)
    {
        std::string line;
        while (_input >> line)
        {
            std::vector<Elem> dataLine;
            dataLine.emplace_back('.', 0);

            for (char c : line)
            {
                dataLine.emplace_back(c, false);
            }

            dataLine.emplace_back('.', false);

            m_map.emplace_back(std::move(dataLine));
        }
        std::vector<Elem> padding(line.size()+2, {'.', false});
        m_map.emplace_back(padding);
        m_map.emplace(m_map.begin(), std::move(padding));
    }

    struct AreaData
    {
        size_t volume, permimeter, nbCorners;

        AreaData operator+(const AreaData& _other) const
        {
            return {volume + _other.volume, permimeter + _other.permimeter, nbCorners + _other.nbCorners};
        }
    };

    bool IsCorner(const MapType& _map, Coord _pos, int _xDir, int _yDir, char _c)
    {
        std::array<char, 4> square = {
            _map[_pos.y][_pos.x].c,
            _map[_pos.y][_pos.x + _xDir].c,
            _map[_pos.y + _yDir][_pos.x].c,
            _map[_pos.y + _yDir][_pos.x + _xDir].c
        };


        size_t nbOfShape = std::count(square.begin(), square.end(), _c);
        if (nbOfShape == 1)
            return true;

        if (nbOfShape == 4)
            return false;
        
        if (nbOfShape == 3)
        {
            if (_map[_pos.y + _yDir][_pos.x + _xDir].c != _c)
                return true;
        }
        if (nbOfShape == 2)
        {
            if (_map[_pos.y + _yDir][_pos.x + _xDir].c == _c)
                return true;
        }
        return false;
    }

    AreaData GetShapeData(Coord _pos, char _c, MapType& _map, std::vector<Coord>* _oobPos)
    {
    
        if (_map.at(_pos.y).at(_pos.x).c != _c)
        {
            if (_oobPos)
            {
                _oobPos->push_back(_pos);
            }
            return {0, 1, 0}; //If oob, 0 volume but 1 perimeter
        }
        
        //If already checked, then 0 volume and 0 permieter
        if (_map.at(_pos.y).at(_pos.x).marked == true)
            return {0, 0, 0};
        

        _map[_pos.y][_pos.x].marked = true;

        std::array<AreaData, 4> neighbours = {
            GetShapeData({_pos.x, _pos.y+1}, _c, _map, _oobPos), 
            GetShapeData({_pos.x, _pos.y-1}, _c, _map, _oobPos),
            GetShapeData({_pos.x+1, _pos.y}, _c, _map, _oobPos),
            GetShapeData({_pos.x-1, _pos.y}, _c, _map, _oobPos)
        };
        

        size_t nbCorners = 0;

        nbCorners += IsCorner(_map, _pos, 1, 1, _c) ? 1 : 0;
        nbCorners += IsCorner(_map, _pos, 1, -1, _c) ? 1 : 0;
        nbCorners += IsCorner(_map, _pos, -1, 1, _c) ? 1 : 0;
        nbCorners += IsCorner(_map, _pos, -1, -1, _c) ? 1 : 0;

        
        return AreaData{1, 0, nbCorners} + neighbours[0] + neighbours[1] + neighbours[2] + neighbours[3];
    }

    size_t ProcessInput1()
    {
        size_t res = 0;
        MapType copy = m_map;

        for (size_t y = 1; y < copy.size()-1; ++y)
        {
            for (size_t x = 1; x < copy[y].size()-1; ++x)
            {
                char chr = copy[y][x].c;
                AreaData data = GetShapeData({x, y}, chr, copy, nullptr);
                if (data.volume == 0)
                    continue;
                res += data.permimeter * data.volume;
            }
        }
        return res;
    }

    //Thanks nick42d for pointing out that number of sides == number of corners
    //I would have never found that otherwise
    size_t ProcessInput2()
    {
        size_t res = 0;
        MapType copy = m_map;

        for (size_t y = 1; y < copy.size()-1; ++y)
        {
            for (size_t x = 1; x < copy[y].size()-1; ++x)
            {
                char chr = copy[y][x].c;
                AreaData data = GetShapeData({x, y}, chr, copy, nullptr);
                if (data.volume == 0)
                    continue;
                std::cout << " " << chr << " " << data.nbCorners << "\n";
                res += data.nbCorners * data.volume;
            }
        }
        return res;
    }

private:
    MapType m_map;
};