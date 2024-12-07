#pragma once

#pragma once
#include "DayBase.h"

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

template <>
class Day<5> : public DayBase
{
public:
    void SplitAndToInt(const std::string& txt, std::vector<size_t>& strs, char ch)
    {
        size_t pos = txt.find(ch);
        size_t initialPos = 0;
        strs.clear();

        // Decompose statement
        while (pos != std::string::npos) {
            strs.push_back(std::stoll(txt.substr(initialPos, pos - initialPos)));
            initialPos = pos + 1;

            pos = txt.find(ch, initialPos);
        }

        // Add the last one
        strs.push_back(std::stoi(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1)));
    }

    void ParseInput(std::ifstream& _input)
    {
        std::string s;
        while (_input >> s)
        {
            size_t bar = s.find('|');
            size_t comma = s.find(',');
            if (bar != std::string::npos)
            {
                size_t before = std::stoull(s.substr(0, bar));
                size_t after = std::stoull(s.substr(bar + 1));

                m_map[before].insert(after);
            }
            else if (comma != std::string::npos)
            {
                std::vector<size_t> ints;
                SplitAndToInt(s, ints, ',');
                m_lines.emplace_back(std::move(ints));
            }
        }
    }

    bool FindWrongNumber(std::vector<size_t>& _line, const std::vector<size_t>::iterator& _itRef, std::vector<size_t>::iterator* _itRes, size_t _rule)
    {
        auto res = std::find(_line.begin(), _line.end(), _rule);
        if (_itRes)
            *_itRes = res;
        return res < _itRef;
    }

    size_t ProcessInput1()
    {
        size_t sum = 0;
        for (auto& line : m_lines)
        {
            bool ok = true;
            for (auto it = line.begin(); it != line.end(); ++it)
            {
                const std::unordered_set<size_t>& rulesSet = m_map[*it];

                for (size_t s : rulesSet)
                {
                    if (FindWrongNumber(line, it, NULL, s))
                    {
                        ok = false;
                        goto break_loops;
                    }
                }
            }

break_loops:
            if (ok)
            {
                sum += line[line.size() / 2];
            }
        }
        return sum;
    }

    size_t ProcessInput2()
    {
        size_t sum = 0;
        for (auto& line : m_lines)
        {
            bool ok = true;
pls_dont_judge: //I know this is terrible practice but it fucking works and I don't give a fuck :]
            for (auto it = line.begin(); it != line.end(); ++it)
            {
                const std::unordered_set<size_t>& rulesSet = m_map[*it];

                for (size_t s : rulesSet)
                {
                    std::vector<size_t>::iterator wrongIT;
                    while (FindWrongNumber(line, it, &wrongIT, s))
                    {
                        ok = false;
                        size_t swp = *it;
                        *it = *wrongIT;
                        *wrongIT = swp;
                        goto pls_dont_judge;
                    }
                }
            }

            if (!ok)
            {
                sum += line[line.size() / 2];
            }
        }
        return sum;
    }

private:
    std::unordered_map<size_t, std::unordered_set<size_t>> m_map;
    std::vector<std::vector<size_t>> m_lines;
};