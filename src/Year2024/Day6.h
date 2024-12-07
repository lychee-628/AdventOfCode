#pragma once

#include "DayBase.h"
#include <string>
#include <string.h>
#include <vector>

template <>
class Day<6> : public DayBase
{
    struct Coord
    {
        int x, y;

        void Inc(int _x, int _y) { x += _x; y += _y; }
        Coord Inc(Coord _c) { return Coord{ x + _c.x, y + _c.y }; }
    };

private:

    void ParseInput(std::ifstream& _input) override
    {
        std::string s;
        for (int i = 0; _input >> s; ++i)
        {
            std::vector<bool> vec;
            vec.resize(s.size(), false);

            int guard = (int)s.find('^');
            if (guard != std::string::npos)
            {
                m_originalGuardPos = Coord{ guard, i };
                vec[guard] = true;
            }

            m_maze.push_back(s);
        }
    }

    void CreatePathBoolVect(std::vector<std::vector<bool>>& _v, Coord _guardPos)
    {
        _v.clear();
        for (int i = 0; i < m_maze.size(); ++i)
        {
            std::vector<bool> v;
            v.resize(m_maze[i].size(), false);
            if (_guardPos.y == i)
            {
                v[_guardPos.x] = true;
            }

            _v.emplace_back(std::move(v));
        }
    }

    void CreatePathBoolVect(std::vector<std::vector<std::pair<bool, int>>>& _v, Coord _guardPos)
    {
        _v.clear();
        for (int i = 0; i < m_maze.size(); ++i)
        {
            std::vector<std::pair<bool, int>> v;
            v.resize(m_maze[i].size(), { false, -1 });
            if (_guardPos.y == i)
            {
                v[_guardPos.x] = { true, 0 };
            }

            _v.emplace_back(std::move(v));
        }
    }


    //Returns false if the path is an infinite loop
    bool GetPath(const std::vector<std::string>& _maze, Coord _startCoord, int _startDir, std::vector<Coord>* _result)
    {
        if (_result)
            _result->clear();

        std::vector<std::vector<std::pair<bool, int>>> path;
        CreatePathBoolVect(path, m_originalGuardPos);
        
        int coordDir = _startDir;
        Coord guardPos = _startCoord;

        while (true)
        {
            Coord newCoord = guardPos.Inc(m_dirsBruteForce[coordDir]);

            if (!(0 <= newCoord.x && newCoord.x < _maze[0].size() && 0 <= newCoord.y && newCoord.y < _maze[0].size())) //if oob
                return true;

            if (_maze[newCoord.y][newCoord.x] == '#')
            {
                coordDir = (coordDir + 1) % 4;
            }
            else
            {
                guardPos = newCoord;

                if (path[guardPos.y][guardPos.x].first == false)
                {
                    if (_result)
                        _result->push_back(guardPos);
                    path[guardPos.y][guardPos.x] = { true, coordDir };
                }
                else if (path[guardPos.y][guardPos.x].second == coordDir) //LOOP
                    return false;
            }
        }
    }

    size_t ProcessInput1() override
    {
        std::vector<std::vector<bool>> path;
        CreatePathBoolVect(path, m_originalGuardPos);
        size_t count = 1;
        int coordDir = 0;
        Coord guardPos = m_originalGuardPos;
        while (true)
        {
            Coord newCoord = guardPos.Inc(m_dirsBruteForce[coordDir]);

            if (!(0 <= newCoord.x && newCoord.x < m_maze[0].size() && 0 <= newCoord.y && newCoord.y < m_maze[0].size())) //if oob
                break;

            if (m_maze[newCoord.y][newCoord.x] == '#')
            {
                coordDir = (coordDir + 1) % 4;
            }
            else
            {
                guardPos = newCoord;

                if (path[guardPos.y][guardPos.x] == false)
                {
                    ++count;
                    path[guardPos.y][guardPos.x] = true;
                }
            }
        }

        return count;
    }



    size_t ProcessInput2() override
    {
        int counter = 0;
        std::vector<Coord> guardPath;
        GetPath(m_maze, m_originalGuardPos, 0, &guardPath);

        for (Coord c : guardPath)
        {
            m_maze[c.y][c.x] = '#';

            if (!GetPath(m_maze, m_originalGuardPos, 0, NULL))
                counter++;

            m_maze[c.y][c.x] = '.';
        }

        
        return counter;
    }

private:
    std::vector<std::string> m_maze;
    std::array<Coord, 4> m_dirsBruteForce = { Coord{0, -1},Coord{1, 0}, Coord{0, 1}, Coord{-1, 0} };
    Coord m_originalGuardPos;
};