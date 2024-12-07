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
    virtual size_t  ProcessInput1() = 0;
    virtual size_t  ProcessInput2() = 0;
};

template <int D>
class Day
{
    void ParseInput(std::ifstream& _input);
    size_t  ProcessInput1() override;
    size_t  ProcessInput2() override;
};
