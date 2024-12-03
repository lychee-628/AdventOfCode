#pragma once
#include "DayBase.h"
#include <vector>
#include <string>

template <>
class Day<2> : public DayBase
{
public:

	Day(): m_lists() {}

	void SplitAndToInt(const std::string& txt, std::vector<int>& strs, char ch)
	{
		size_t pos = txt.find(ch);
		size_t initialPos = 0;
		strs.clear();

		// Decompose statement
		while (pos != std::string::npos) {
			strs.push_back(std::stoi(txt.substr(initialPos, pos - initialPos)));
			initialPos = pos + 1;

			pos = txt.find(ch, initialPos);
		}

		// Add the last one
		strs.push_back(std::stoi(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1)));
	}


	void ParseInput(std::ifstream& _input)
	{
		std::string line;
		while (std::getline(_input, line, '\n'))
		{
			m_lists.emplace_back();
			
			SplitAndToInt(line, m_lists.back(), ' ');
		}
	}

	bool IsValid(const std::vector<int>& _list)
	{
		int diffSign = 0;

		for (int i = 0; i< _list.size()-1; ++i)
		{
			int diff = _list[i] - _list[i + 1];
			
			//First iteration : initialize diffSign
			if (diffSign == 0)
				diffSign = diff;

			//Smaller or equal to zero if diffSign is null OR if one is positive and the other negative
			if (diff * diffSign <= 0)
			{
				//std::cout << "NOT SAFE : NOT INCREASING OR DECREASING CONSTANTLY\n";
				return false;
			}

			if (std::abs(diff) > 3)
			{
				//std::cout << "NOT SAFE : " << diff << "\n";
				return false;
			}
		}

		//std::cout << "SAFE\n";
		return true;
	}

	int  ProcessInput1()
	{
		int nbValid = 0;
		for (auto& vect : m_lists)
		{
			if (IsValid(vect))
				nbValid++;
		}
		return nbValid;
	}

	int  ProcessInput2()
	{
		int nbValid = 0;
		for (auto& vect : m_lists)
		{
			if (IsValid(vect))
			{
				nbValid++;
				continue;
			}

			//Father plz forgive me for that
			for (int i = 0; i < vect.size(); ++i)
			{
				std::vector<int> copy;
				copy.reserve(vect.size() - 1);

				for (int j = 0; j < vect.size(); ++j)
				{
					if (i == j) continue;

					copy.push_back(vect[j]);
				}

				if (IsValid(copy))
				{
					nbValid++;
					break;
				}
			}
		}
		return nbValid;
	}

private:
	std::vector<std::vector<int>> m_lists;
	
};