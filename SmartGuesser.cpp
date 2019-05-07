#include "SmartGuesser.hpp"
using namespace bullpgia;
using namespace std;
string SmartGuesser::guess()
{
    //in case length hasn't been started yet or it is somehow set to negative number
    if (this->length <= 0)
    {
        throw invalid_argument("one of input strings has incorrect length -> it has to be a positive Neutral number");
    }
    string guess = "";
    //this means we're in first 10 guesses - in which we're figuring out which digits are in the number and in which quantity
    if (this->numOfGuess < 10 && this->sumOfArray < this->length)
    {
        string numOfGuessString = to_string(this->numOfGuess);
        for (int i = 0; i < this->length; i++)
        {
            guess += numOfGuessString;
        }
    }
    //this means were at the second stage - of figuring out in which places these digits belong
    else if (this->whichDigit <= this->length - 1)
    {
        //if we're in a middle of looking for certain digit place
        if (this->whichPlace <= this->length - 1)
        {
            assembleAWord(guess);
        }
        //or we already found the place for this digit and now we should check the next
        else
        {
            this->whichPlace = 0;
            this->whichDigit++;
            assembleAWord(guess);
        }
    }
    //if we found all digits places - we guessed the number - it is indeed the last guess
    else
    {
        guess = this->lastGuess;
    }
    this->numOfGuess++;
    return guess;
}

//this method is made to configure a new game for the guesser - i.e to reset the variables and members
void SmartGuesser::startNewGame(uint length)
{
    this->length = length;
    this->lastGuess = "";
    this->numOfGuess = 0;
    this->sumOfArray = 0;
    this->whichDigit = 0;
    this->whichPlace = 0;
    this->allRightCharsOrdered.clear();
    for (int i = 0; i < this->length; i++)
    {
        this->allRightCharsOrdered.push_back('*');
    }
    for (int i = 0; i < 10; i++)
    {
        this->whichNumbersAreIn[i] = 0;
    }
    this->allRightCharsMessy.clear();
    isFirstGuessingRoundIsFinished = false;
}

SmartGuesser::SmartGuesser()
{
    //this way we could know that new game haven't started yet
    this->length = -5;
}

//this method will work only after guessing a number, so all "states" will be semetric to the "guess" method
void SmartGuesser::learn(calcFunOutput arg)
{
    if (this->length == -5)
    {
        throw invalid_argument("HAVEN'T STARTED NEW GAME YET!");
    }
    //this means we're at the first 10 guesses - in which we just trying to fill our "whichNumbersAreIn" array
    if (this->numOfGuess <= 10 && this->sumOfArray < this->length)
    {
        this->whichNumbersAreIn[this->numOfGuess - 1] = arg.bull;
        sumOfArray += arg.bull;
    }
    //this means we're at the last guess of these 10 - so we have to assemble the "allRightCharsMessy" vector
    if (this->isFirstGuessingRoundIsFinished == false && (this->numOfGuess - 1 == 9 || this->sumOfArray == this->length))
    {
        for (int i = 0; i < 10; i++)
        {
            if (this->whichNumbersAreIn[i] != 0)
            {
                for (int j = 0; j < this->whichNumbersAreIn[i]; j++)
                {
                    char aboutToGoIn = '0' + i;
                    this->allRightCharsMessy.push_back(aboutToGoIn);
                }
            }
        }
        //this boolean members exists just to be sure we won't enter this "state" more than once
        //and to assure that we won't enter next "states" without ending this one
        this->isFirstGuessingRoundIsFinished = true;
    }
    //this is the "state" in which we're looking for the right position for every digit
    else if (this->whichDigit < length && this->isFirstGuessingRoundIsFinished)
    {
        int rightNumOfPlace = 0;
        if (this->whichPlace == 0)
        {
            rightNumOfPlace = 3;
        }
        else
        {
            rightNumOfPlace = this->whichPlace - 1;
        }
        int rightNumOfDigit = 0;
        if (this->whichDigit != 0)
        {
            rightNumOfDigit = this->whichDigit - 1;
        }
        if (arg.bull == 1)
        {
            this->allRightCharsOrdered.at(rightNumOfPlace) = this->allRightCharsMessy.at(this->whichDigit);
        }
    }
    //assembeling the final guess
    else if (this->isFirstGuessingRoundIsFinished)
    {
        string lastGuess = "";
        for (char c : this->allRightCharsOrdered)
        {
            lastGuess += c;
        }
        this->setLastGuess(lastGuess);
    }
}

void SmartGuesser::setLastGuess(string arg)
{
    this->lastGuess.append(arg);
}

string SmartGuesser::assembleAWord(string &guess)
{
    for (int i = 0; i < this->length; i++)
    {
        if (i == this->whichPlace && this->allRightCharsOrdered.at(whichPlace) == '*')
        {
            guess += this->allRightCharsMessy.at(this->whichDigit);
        }
        else
        {
            guess += '*';
        }
    }
    this->whichPlace++;
    return guess;
}
