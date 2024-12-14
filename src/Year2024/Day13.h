
#pragma once
#include "DayBase.h"

#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

/*

X1a + X2b = X
Y1a + Y2b = Y

a = (X - X2b)/X1
b = (YX1 - Y1X)/(Y2X1 - Y1X2)


//
If , impossible
If a < 0 or b < 0, impossible


*/


template <>
class Day<13> : public DayBase
{

    struct Equation
    {
        size_t X1, X2, X;
        size_t Y1, Y2, Y;

        bool Solve(size_t& _a, size_t& _b)
        {
            //If b is < 0
            if (Y*X1 < Y1*X ^ Y2*X1 < Y1*X2)
            {
                return false;
            }

            size_t numB, denB = 0;
            
            //size_t bs
            if (Y*X1 < Y1*X && Y2*X1 < Y1*X2)
            {
                numB = (Y1*X - Y*X1);
                denB = (Y1*X2 - Y2*X1);
            }
            else
            {
                numB = (Y*X1 - Y1*X);
                denB = (Y2*X1 - Y1*X2);
            }

            //If b is not a whole number
            if (numB % denB != 0)
            {
                return false;
            }

            _b = numB/denB;

            //If a < 0
            if (X < X2*_b != 0)
            {
                return false;
            }

            //If a doesn't exist
            if ((X - X2*_b) % X1 != 0)
            {
                return false;
            }
            
            _a = (X - X2*_b)/X1;
            return true;
        }
    };

    void ParseInput(std::ifstream& _input)
    {
        std::string line;
        while (std::getline(_input, line))
        {
            //POsitions of X1 and Y1 in "Button A: X+??, Y+Y1" == 12-14, 18-20
            size_t X1 =  std::stoull(line.substr(12, 14));
            size_t Y1 =  std::stoull(line.substr(18, 20));
            
            std::getline(_input, line);

            size_t X2 =  std::stoull(line.substr(12, 14));
            size_t Y2 =  std::stoull(line.substr(18, 20));
            
            std::getline(_input, line);
            //Prize: X=?????, Y=?????
            size_t X =  std::stoull(line.substr(9, line.find(',')));
            size_t Y =  std::stoull(line.substr(line.find(',')+4));

            m_equations.emplace_back(X1, X2, X, Y1, Y2, Y);
            
            std::getline(_input, line);
        }
    }

    size_t ProcessInput1()
    {
        size_t total = 0;
        for (Equation& eq : m_equations)
        {
            size_t a, b;
            if (eq.Solve(a, b))
            {
                total += 3*a +b;
            }
        }
        return total;
    }

    size_t ProcessInput2()
    {
        size_t total = 0;
        for (Equation& eq : m_equations)
        {
            Equation modif = eq;
            modif.X += 10000000000000;
            modif.Y += 10000000000000;

            size_t a, b;
            if (modif.Solve(a, b))
            {
                total += 3*a +b;
            }
        }
        return total;
    }

private:
    std::vector<Equation> m_equations;
};