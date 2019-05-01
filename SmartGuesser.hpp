#pragma once
#include <string>
#include "Guesser.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace bullpgia
{
class SmartGuesser : public bullpgia::Guesser
{
public:
    SmartGuesser();
    string guess() override;
    void startNewGame(uint length) override;
    void learn(calcFunOutput arg) override;

private:
    int whichPlace;
    int whichDigit;
    vector<char> allRightCharsMessy;
    vector<char> allRightCharsOrdered;
    int sumOfArray;
    string lastGuess;
    int whichNumbersAreIn[10];
    uint numOfGuess;
    void setLastGuess(string arg);
    bool isFirstDigit;
    bool isFirstPlace;
};
} // namespace bullpgia