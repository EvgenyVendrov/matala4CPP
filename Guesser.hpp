#pragma once
#include <string>
#include "calculate.hpp"

using namespace std;

namespace bullpgia
{
class Guesser
{
public:
    uint length;

    virtual void startNewGame(uint length)
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