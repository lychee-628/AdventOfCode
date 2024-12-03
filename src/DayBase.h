#pragma once

#include <fstream>
#include <iostream>

class DayBase
{
public:
    void Run(std::ifstream& _input)
    {
        ParseInput(_input);
        std::cout << "RESULT 1 : " << ProcessInput1() << "\n";
        std::cout << "RESULT 2 : " << ProcessInput2() << "\n";
    }

private:

    virtual void ParseInput(std::ifstream& _input) = 0;
    virtual int  ProcessInput1() = 0;
    virtual int  ProcessInput2() = 0;
};

template <int D>
class Day
{
    void ParseInput(std::ifstream& _input);
    int  ProcessInput1() override;
    int  ProcessInput2() override;
};
