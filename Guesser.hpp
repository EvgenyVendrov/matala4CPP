#pragma once
#include <string>
#include "calculate.hpp"

using namespace std;

namespace bullpgia
{
class Guesser
{
//basic "guesser" class - which in a way is the interface that define's a guesser from any kind
public:
    int length;

    virtual void startNewGame(const uint length)
    {
        this->length = length;
    };

    virtual string guess() = 0;

    virtual void learn(const calcFunOutput reply)
    {
    }

private:
};
} // namespace bullpgia