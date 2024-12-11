#include "DayBase.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <string>

#include "Year2024/Day1.h"
#include "Year2024/Day2.h"
#include "Year2024/Day3.h"
#include "Year2024/Day4.h"
#include "Year2024/Day5.h"
#include "Year2024/Day6.h"
#include "Year2024/Day7.h"
#include "Year2024/Day8.h"
#include "Year2024/Day9.h"
#include "Year2024/Day10.h"
#include "Year2024/Day11.h"


#define MAX_DAY_IMPLEMENTED 11

const std::array<DayBase*, MAX_DAY_IMPLEMENTED> days =
{
    new Day<1>(),
    new Day<2>(),
    new Day<3>(),
    new Day<4>(),
    new Day<5>(),
    new Day<6>(),
    new Day<7>(),
    new Day<8>(),
    new Day<9>(),
    new Day<10>(),
    new Day<11>()
};

std::string GetFileName(const char* _prefix, int _day)
{
    std::string str = _prefix;
    str += std::to_string(_day);
    str += ".txt";
    return str;
}

bool OpenFile(const std::string& _fileName, std::ifstream& _stream)
{
    _stream.open(_fileName);
    if (!_stream.is_open())
    {
        std::cout << "ERROR : Could not open file " << _fileName << "  !\n";
        return false;
    }
    return true;
}


void RunDayImpl(const char* _file, int _day)
{
    std::string fileName = GetFileName(_file, _day);
    std::ifstream stream;

    if (!OpenFile(fileName, stream))
    {
        return;
    }

    DayBase* d = days[_day - 1];
    d->Run(stream);
}

void RunDay(int _day, bool _runExample=false)
{
    if (_runExample)
    {
        std::cout << "\n\nEXAMPLE : \n";
        RunDayImpl("res/Example", _day);    
        return; //Imagine running example AND full day, such that the results add up and you get a wrong answer...
    }

    std::cout << "\n\nCODE OUTPUT : \n";
    RunDayImpl("res/Day", _day);
}

int main()
{
    bool runExample = false;
    bool runEverything = false;

    if (runEverything)
    {
        for (int i = 1; i <= MAX_DAY_IMPLEMENTED; ++i)
        {
            RunDay(i, runExample);
        }
    }
    else
    {
        RunDay(MAX_DAY_IMPLEMENTED, runExample);
    }

    //Screw smart pointers :)
    for (auto* day : days)
        delete day;
}