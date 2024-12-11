#pragma once
#include "DayBase.h"

#include <list>
#include <string>
#include <algorithm>
#include <cmath>

template <>
class Day<11> : public DayBase
{
public:
    void ParseInput(std::ifstream& _input)
    {
        std::string line;
        while (_input >> line)
        {
            m_numbers.push_back(std::stoull(line));
        }
    }
    size_t GetNumberOfDigits (size_t i)
    {
        return i > 0 ? (size_t) log10 ((double) i) + 1 : 1;
    }

    size_t SplitNumberSecondHalf(size_t n, size_t _nbDigits, size_t _pow10=0)
    {
        size_t res = 0;
        size_t pow10 = 1;

        while(n >= pow(10, _pow10))
        {
            size_t r=n%10;
            n=n/10;

            res += r * pow10;
            pow10*=10;
        }
        return res;

    }

    void Blink(std::list<size_t>& _numbers)
    {

        for (auto it = _numbers.begin(); it != _numbers.end(); ++it)
        {
            //Rule 1
            if ((*it) == 0)
            {
                (*it) = 1;
                continue;
            }
            size_t nbDg = GetNumberOfDigits(*it);
            if (nbDg % 2 == 0)
            {
                size_t secondHalf = SplitNumberSecondHalf(*it, nbDg, nbDg/2);
                size_t firstHalf = (*it) - secondHalf;
                firstHalf /= (pow(10, nbDg/2));
                *it = secondHalf;
                _numbers.insert(it, firstHalf);
            }
            else
            {
                *it *= 2024;
            }

        }
    }

    size_t GetNbStoneAfterNBlink(size_t _stone, size_t _nbBlink)
    {
        if (_nbBlink == 0)
            return 1;
        else if (m_lookup[_stone][_nbBlink] != 0)
            return m_lookup[_stone][_nbBlink];
        else
        {
            if (_stone == 0)
            {
                size_t res = GetNbStoneAfterNBlink(1, _nbBlink-1);
                m_lookup[_stone][_nbBlink] = res;
                return res;
            }
            size_t nbDg = GetNumberOfDigits(_stone);
            if (nbDg % 2 == 0)
            {
                size_t secondHalf = SplitNumberSecondHalf(_stone, nbDg, nbDg/2);
                size_t firstHalf = _stone - secondHalf;
                firstHalf /= (pow(10, nbDg/2));
                
                size_t res1 = GetNbStoneAfterNBlink(firstHalf, _nbBlink-1);
                size_t res2 = GetNbStoneAfterNBlink(secondHalf, _nbBlink-1);

                m_lookup[_stone][_nbBlink] = res1 + res2;
                return res1+res2;
            }
            else
            {
                size_t res = GetNbStoneAfterNBlink(_stone*2024, _nbBlink-1);
                m_lookup[_stone][_nbBlink] = res;
                return res;
            }
        }
    }

    size_t ProcessInput1()
    {
        std::list<size_t> copy = m_numbers;

        for (int i = 0; i < 25; ++i)
        {
            Blink(copy);
        }

        return copy.size();
    }


    size_t ProcessInput2()
    {
        size_t res = 0;
        std::list<size_t> copy = m_numbers;

        for (size_t s : m_numbers)
        {
           // std::cout << s << " : " << GetNbStoneAfterNBlink(res, 1) << "\n";
            res += GetNbStoneAfterNBlink(s, 75);
        }

        return res;
    }

private:
    std::list<size_t> m_numbers;

    std::unordered_map<size_t, std::array<size_t, 100>> m_lookup;
};