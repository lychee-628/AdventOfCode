#pragma once

#include "DayBase.h"
#include <string>
#include <string.h>
#include <vector>

template <>
class Day<7> : public DayBase
{
    class CrapArray
    {

    public:
        CrapArray(const std::vector<size_t> _data, size_t _result):
            m_size{ (size_t)_data.size()}, m_data{new size_t[_data.size() + 1]}, isSub{false}
        {
            m_data[0] = _result;

            for (size_t i = 0; i < _data.size(); ++i)
            {
                m_data[1 + i] = _data[i];
            }
        }

        CrapArray(CrapArray&& _other) noexcept
        {
            m_size = _other.m_size;
            m_data = _other.m_data;
            _other.m_data = nullptr;
        }

        size_t Result() const
        {
            return m_data[0];
        }

        size_t Size() const
        {
            return m_size;
        }

        size_t& operator[](size_t _i)
        {
            return m_data[1+_i];
        }

        const size_t& operator[](size_t _i) const
        {
            return m_data[1 + _i];
        }

        CrapArray Sub(size_t _offset) const
        {
            return CrapArray(*this, _offset);
        }

        ~CrapArray()
        {
            if (!isSub)
                free(m_data);
        }


    private:
        CrapArray(const CrapArray& _a, size_t _offset):
            m_size{_a.m_size - _offset}, m_data{_a.m_data + _offset}, isSub{true}
        {

        }
    private:        
        size_t m_size;
        size_t* m_data;
        bool isSub;
    };
private:

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

    void ParseInput(std::ifstream& _input) override
    {
        std::string s;
        while (std::getline(_input, s))
        {
            size_t c = s.find(':');
            size_t result = std::stoll(s.substr(0, c));
            std::string rem = s.substr(c + 2);
            std::vector<size_t> nums;
            SplitAndToInt(rem, nums, ' ');

            std::reverse(nums.begin(), nums.end());

            m_data.emplace_back(nums, result);
            
        }
    }

    static size_t OperatorAdd(size_t _a, size_t _b)
    {
        return _a + _b;
    }

    static size_t OperatorMult(size_t _a, size_t _b)
    {
        return _a * _b;
    }

    static size_t OperatorConcat(size_t _a, size_t _b)
    {

        //Find smallest power of 10 above b
        int p = 1;
        while (p <= _b)
            p *= 10;

        return (_a * p) + _b;
    }


    template <typename Func> //You think I have the time to remember the type of a function ptr ???
    void GetOpsResult(const CrapArray& c, std::vector<size_t>& _possibleResults, const std::vector<Func>& _operations)
    {
        if (c.Size() == 1)
        {
            _possibleResults.clear();
            _possibleResults.push_back(c[0]);
            return;
        }

        GetOpsResult<Func>(c.Sub(1), _possibleResults, _operations);

        _possibleResults.reserve(_operations.size() * _possibleResults.size());

        auto end = _possibleResults.end();
        for (auto it = _possibleResults.begin(); it != end; ++it)
        {
            for (int op = 1; op < _operations.size(); ++op)
                _possibleResults.push_back(_operations[op]((*it), c[0]));

            (*it) = _operations[0]((*it), c[0]);
        }
    }


    void GetOpsResultAUUUGH(const CrapArray& c, std::vector<size_t>& _possibleResults)
    {
        if (c.Size() == 1)
        {
            _possibleResults.clear();
            _possibleResults.push_back(c[0]);
            return;
        }

        GetOpsResultAUUUGH(c.Sub(1), _possibleResults);


        auto end = _possibleResults.end();
        for (auto it = _possibleResults.begin(); it != end; ++it)
        {

            (*it) = OperatorConcat((*it), c[0]);
        }
    }

    size_t ProcessInput1() override
    {
        size_t c = 0;
        for (CrapArray& arr : m_data)
        {
            std::vector<size_t> thongs;
            auto ops = std::vector({ &OperatorAdd, & OperatorMult });
            GetOpsResult(arr, thongs, ops);

            if (std::find(thongs.begin(), thongs.end(), arr.Result()) != thongs.end())
                c+= arr.Result();

        }
        return c;
    }



    size_t ProcessInput2() override
    {
        size_t c = 0;
        for (const CrapArray& arr : m_data)
        {

            std::vector<size_t> thongs;
            
            auto ops = std::vector({ &OperatorAdd, &OperatorMult, &OperatorConcat });
            GetOpsResult(arr, thongs, ops);

            if (std::find(thongs.begin(), thongs.end(), arr.Result()) != thongs.end())
                c += arr.Result();

        }
        return c;
    }

private:
    //Arrays of size_t, where 
    std::vector<CrapArray> m_data;
};