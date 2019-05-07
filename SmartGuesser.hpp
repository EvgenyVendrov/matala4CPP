#pragma once
#include <string>
#include "Guesser.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace bullpgia
{
class SmartGuesser : public bullpgia::Guesser
{
    //this class is a smart guesser which will guess any 4 digit number in under 30 guesses,
    //and will guess any number with 9 digits at most in under 100 guesses
    //any other length number will be guessed too - eventually (the algorithem works for any number of digits)
public:
    SmartGuesser();
    string guess() override;
    void startNewGame(const uint length) override;
    void learn(const calcFunOutput arg) override;

private:
    string assembleAWord(string &guess);
    int whichPlace;
    int whichDigit;
    vector<char> allRightCharsMessy;
    vector<char> allRightCharsOrdered;
    int sumOfArray;
    string lastGuess;
    int whichNumbersAreIn[10];
    uint numOfGuess;
    void setLastGuess(string arg);
    bool isFirstGuessingRoundIsFinished;
};
} // namespace bullpgia