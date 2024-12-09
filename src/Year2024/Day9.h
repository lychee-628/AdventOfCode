#pragma once
#include "DayBase.h"

#include <vector>
#include <string>
#include <algorithm>

template <>
class Day<9> : public DayBase
{
public:


    void ParseInput(std::ifstream& _input)
    {
        std::string str;
        _input >> str;

        bool isData = true;
        size_t id = 0;
        for (char c : str)
        {
            size_t s = c - '0';
            size_t idToEmplace = id;
            if (!isData)
            {
                idToEmplace = std::string::npos;
                ++id;
            }

            for (int _ = 0; _ < s; ++_)
            {
                m_data.emplace_back(idToEmplace);
            }

            isData = !isData;
        }
    }

    void PrintNb(size_t s)
    {
        if (s == std::string::npos)
            std::cout << '.';
        else
            std::cout << s;
    }

    size_t ProcessInput1()
    {

        //Rearrange the things so that there are no gaps
        std::vector<size_t> copy = m_data;

        std::vector<size_t>::iterator front = copy.begin();
        std::vector<size_t>::iterator back = copy.end()-1;

        while (front < back)
        {
            if (*front == std::string::npos)
            {
                if (*back != std::string::npos)
                {
                    *front = *back;
                    *back = std::string::npos;
                }
            }
            else
            {
                ++front;
            }

            if (*back == std::string::npos)
            {
                --back;
            }
        }

        size_t sum = 0;
        
        size_t i = 0;
        while (copy[i] != std::string::npos)
        {
            sum += i * copy[i];
            ++i;
        }

        return sum;
    }

    //Identify the blocks of the data
    struct Block
    {
        size_t pos;
        size_t size;
        size_t id;
    };

    void PrintThong(std::vector<size_t>& copy)
    {

        for (size_t i = 0; i < copy.size(); ++i)
        {
            if (copy[i] != std::string::npos)
                std::cout << copy[i];
            else
                std::cout << '.';
            //sum += i * copy[i];
        }
        std::cout << "\n";

    }

    void Lmao(std::vector<size_t>& _copy)
    {
        std::vector<Block> structure;

        size_t blockStart = 0;
        size_t id = m_data[0];

        for (size_t i = 0; i <= m_data.size(); ++i)
        {
            if (m_data[i] != id || i == m_data.size())
            {
                structure.emplace_back(blockStart, i - blockStart, id);
                blockStart = i;
                id = m_data[i];
            }
        }

        std::vector<Block>::iterator back = structure.end() - 1;

        while (back != structure.begin())
        {
            //PrintThong(_copy);

            if (back->id != std::string::npos)
            {
                std::vector<Block>::iterator b = std::find_if(structure.begin(), back, [=](const Block& _b) { return _b.id == std::string::npos && _b.size >= back->size; });

                if (b != back)
                {
                    for (size_t i = 0; i < back->size; ++i)
                    {
                        _copy[b->pos + i] = _copy[back->pos + i];
                        _copy[back->pos + i] = std::string::npos;
                    }
                    b->pos = b->pos + back->size;
                    b->size -=  back->size;
                }
            }

            --back;
        }
    }

    size_t ProcessInput2()
    {
        //Rearrange the things so that there are no gaps
        std::vector<size_t> copy = m_data;
        
       
        Lmao(copy);
        


        size_t sum = 0;

        for (size_t i = 0; i < copy.size(); ++i)
        {
            if (copy[i] != std::string::npos)
                sum += i * copy[i];
        }
        std::cout << "\n";
        return sum;
    }

    std::vector<size_t> m_data;
};