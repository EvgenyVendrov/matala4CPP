#pragma once
#include <string>
#include "calculate.hpp"

using namespace std;

namespace bullpgia
{
class Guesser
{
public:
    int length;

    virtual void startNewGame(int length)
    {
        this->length = length;
    };

    virtual string guess() = 0;

    virtual void learn(calcFunOutput reply)
    {
    }

private:
};
} // namespace bullpgia