#include "SmartGuesser.hpp"
using namespace bullpgia;
using namespace std;
string SmartGuesser::guess()
{
    //in case length hasn't been started yet
    if (this->length <= 0)
    {
        throw invalid_argument("one of input strings has incorrect length -> it has to be a positive Neutral number");
    }
    string guess = "";
    //this means we're in first 10 guesses
    if (this->numOfGuess < 10 && this->sumOfArray < this->length)
    {
        string numOfGuessString = to_string(this->numOfGuess);
        for (int i = 0; i < this->length; i++)
        {
            guess += numOfGuessString;
        }
    }
    else if (this->whichDigit <= this->length - 1)
    {
        //std::cout << "which digit=>" << this->whichDigit << std::endl;
        //std::cout << "which place==>" << this->whichPlace << std::endl;
        if (this->whichPlace <= this->length - 1)
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
        }
        else
        {
            this->whichPlace = 0;
            this->whichDigit++;
            for (int i = 0; i < this->length; i++)
            {
                if (i == this->whichPlace && this->allRightCharsOrdered.at(whichPlace) == '*')
                {
                    guess += this->allRightCharsMessy.at(this->whichDigit);
                    //guess += '3';
                }
                else
                {
                    guess += '*';
                }
            }
            this->whichPlace++;
        }
    }
    else
    {
        guess = this->lastGuess;
    }
    this->numOfGuess++;
    // std::cout << "OUR CURRENT GUESS>>" << guess << std::endl;
    return guess;
}

void SmartGuesser::startNewGame(int length)
{
    if (length <= 0)
    {
        throw invalid_argument("one of input strings has incorrect length -> it has to be a positive Neutral number");
    }
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
    this->length = -5;
}

void SmartGuesser::learn(calcFunOutput arg)
{
    if (this->length == -5)
    {
        throw invalid_argument("HAVEN'T STARTED NEW GAME YET!");
    }
    if (this->numOfGuess <= 10 && this->sumOfArray < this->length)
    {
        //  cout << "argbull->" << arg.bull<<"for guess "<<this->numOfGuess-1 << endl;
        this->whichNumbersAreIn[this->numOfGuess - 1] = arg.bull;
        sumOfArray += arg.bull;
    }
    if (this->isFirstGuessingRoundIsFinished == false && (this->numOfGuess - 1 == 9 || this->sumOfArray == this->length))
    {
        //    for (int i = 0; i < 10; i++)
        //     {
        //         cout << this->whichNumbersAreIn[i] << "//";
        //     }
        //     cout << endl;
        for (int i = 0; i < 10; i++)
        {
            //cout << "which cell->" << i << endl;

            if (this->whichNumbersAreIn[i] != 0)
            {
                //cout << "which guess->" << this->numOfGuess << endl;

                for (int j = 0; j < this->whichNumbersAreIn[i]; j++)
                {
                    //cout << "went to add a num in VECOTR MESSY" << endl;
                    //cout << "value of cell->" << this->whichNumbersAreIn[i] << "which cell->" << i << endl;
                    char aboutToGoIn = '0' + i;
                    this->allRightCharsMessy.push_back(aboutToGoIn);
                }
            }
        }
        this->isFirstGuessingRoundIsFinished = true;
        // std::cout << "MESSY VECTOR IS ALIVE!!" << endl;
    }
    else if (this->whichDigit < length && this->isFirstGuessingRoundIsFinished)
    {
        //  std::cout << "BULL&PGIA=>" << arg.bull << endl;
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
            //cout << "size of messy chars VECTOR>>" << this->allRightCharsMessy.size() << endl;
            //cout << "which digit>>" << this->whichDigit << endl;
            this->allRightCharsOrdered.at(rightNumOfPlace) = this->allRightCharsMessy.at(this->whichDigit);
            // std::cout << "NEW ORDERED VECTOR!" << endl;
            // for (char c : this->allRightCharsOrdered)
            // {
            //     std::cout << c;
            // }
            // std::cout << endl;
        }
    }
    else if (this->isFirstGuessingRoundIsFinished)
    {
        string lastGuess = "";
        for (char c : this->allRightCharsOrdered)
        {
            lastGuess += c;
        }
        this->setLastGuess(lastGuess);
        // std::cout << "LAST GUESS >>>>>" << this->lastGuess;
    }
}

void SmartGuesser::setLastGuess(string arg)
{
    this->lastGuess.append(arg);
}
