#pragma once

#include "DayBase.h"
#include <string>


template <>
class Day<3> : public DayBase
{

    struct Multiplication
    {
        std::string substr;
        bool enabled;
    };
public:

    size_t FindLastOfButItDoesWhatItSaysItDoes(const std::string& _data, const char* _str, size_t _pos)
    {
        std::string sub = _data.substr(0, _pos);
        size_t lastFound = std::string::npos;

        while (true)
        {
            size_t i = sub.find(_str, lastFound+1);
            if (i == std::string::npos)
                return lastFound;
            lastFound = i;
        }
    }

    void ParseInput(std::ifstream& _input) override
    {
        std::string data;
        bool enabled = true;
        
        while (_input >> data)
        {
            size_t nextMulFound = (size_t)-1;
            
            while (true)
            {

                nextMulFound = data.find("mul", nextMulFound+1);

                size_t doPos = FindLastOfButItDoesWhatItSaysItDoes(data, "do()", nextMulFound);
                size_t dontPos = FindLastOfButItDoesWhatItSaysItDoes(data, "don't()", nextMulFound);

                //std::cout << "DO :" << doPos << " && DONT " << dontPos << "\n";
                //std::cout << "DO :" << doPos << " && DONT " << dontPos << "\n";

                if (doPos != std::string::npos)
                {
                    if (dontPos != std::string::npos)
                    {
                        if (dontPos > doPos)
                            enabled = false;
                        else
                            enabled = true;
                    }
                    else
                        enabled = true;
                }
                else if (dontPos != std::string::npos)
                {
                    enabled = false;
                }

                if (nextMulFound == std::string::npos)
                    break;

                m_mulsStr.push_back({data.substr(nextMulFound, 13), enabled});//Worst case scenario : mul(123,123), length = 12 chars. 13 for security
            }
        }
    }

    bool IsNum(char c)
    {
        return '0' <= c && c <= '9';
    }

    bool IsThreeDigitOrLess(const char* _s, char _del, int& _res)
    {
        for (int i = 0; i < 4; ++i)
        {
            char c = *(_s+i);
            if (!IsNum(c))
            {
                if (c == _del && i > 0)
                {
                    _res = i+1;//+1 to go past the delemiter
                    return true;
                }
                return false;
            }
        }
        return false;
    }

    bool GetThreeDigitNumber(const char* _p, char _del, int& _result, int& _nbDigits)
    {
        std::string numberStart = std::string(_p);
        if (!IsThreeDigitOrLess(numberStart.data(), _del, _nbDigits))
            return false;
        _result = std::stoi(numberStart.substr(0, _nbDigits));
        return true;
    }

    int Process(bool _considerEnabled)
    {
        int sum = 0;
        for (auto&[s, enabled] : m_mulsStr)
        {
            //std::cout << "ENABLED IS " << enabled << "\n";
            if (_considerEnabled && !enabled)
                continue;
            const char* dbg = s.data();
            const char* p = s.data();

            p += 3;//skip the "mul" prefix
            if (*p != '(') //check for '(' after "mul"
            {
               // std::cout << "INVALID : '(' missing after mul : " << dbg << "\n";
                continue;
            }
            ++p;

            int result1, result2, nbDigits1, nbDigits2 = 0;
            if (!GetThreeDigitNumber(p, ',', result1, nbDigits1))
            {
                //std::cout << "INVALID : first number not recognised : " << dbg << "\n";
                continue;
            }
            
            p += nbDigits1;

            if (!GetThreeDigitNumber(p, ')', result2, nbDigits2))
            {
             //   std::cout << "INVALID : second number not recognised : " << dbg << "\n";
                continue;
            }
            
            sum += result1 * result2;
        }
        return sum;
    }

    int  ProcessInput1() override
    {
        return Process(false);
    }
    int  ProcessInput2() override
    {
        return Process(true);
    }

private:
    std::vector<Multiplication> m_mulsStr;
};