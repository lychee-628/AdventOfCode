#pragma once
#include "DayBase.h"

#include <vector>
#include <string>
#include <algorithm>

template <>
class Day<1> : public DayBase
{
public:
    Day() :
        m_leftNumbers(), m_rightNumbers()
    {}

    void ParseInput(std::ifstream& _input)
    {
        std::string line;

        const char* DELEMITER = "   ";
        const size_t DELEMITER_SIZE = 3;

        while (std::getline(_input, line))
        {
            auto id = line.find("   ");
            std::pair<std::string, std::string> nums = std::make_pair(
                line.substr(0, id),
                line.substr(id + DELEMITER_SIZE, line.length() - (id + DELEMITER_SIZE)));
            m_leftNumbers.emplace_back(std::stoi(nums.first));
            m_rightNumbers.emplace_back(std::stoi(nums.second));
        }

        std::sort(m_leftNumbers.begin(), m_leftNumbers.end());
        std::sort(m_rightNumbers.begin(), m_rightNumbers.end());
    }

    size_t ProcessInput1()
    {
        int sum = 0;
        for (int i = 0; i < m_leftNumbers.size(); ++i)
        {
            sum += std::abs(m_leftNumbers[i] - m_rightNumbers[i]);
        }
        return sum;
    }

    size_t ProcessInput2()
    {
        int sum = 0;

        for (int i : m_leftNumbers)
        {
            int nbAppears = 0;
            for (int j : m_rightNumbers)
            {
                if (j == i)
                    ++nbAppears;
                if (j > i)
                    break;
            }
            sum += i * nbAppears;
        }
        return sum;
    }

private:
    std::vector<int> m_leftNumbers;
    std::vector<int> m_rightNumbers;
};