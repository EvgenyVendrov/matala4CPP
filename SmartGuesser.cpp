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
    if ((this->numOfGuess < 10) && (this->sumOfArray) < (this->length))
    {
        string numOfGuessString = to_string(this->numOfGuess);
        cout << "string num of guess>>" << numOfGuessString << endl;
        for (int i = 0; i < this->length; i++)
        {
            guess += numOfGuessString;
            cout << "our guess>>" << guess << endl;
        }
    }
    else if (this->whichDigit < this->length)
    {
        if (this->whichPlace < this->length)
        {
            for (int i = 0; i < this->length; i++)
            {
                if (i == this->whichPlace)
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
        else if (this->whichPlace == this->length)
        {
            this->isFirstPlace = true;
            for (int i = 0; i < this->length; i++)
            {
                if (i == this->whichPlace)
                {
                    guess += this->allRightCharsMessy.at(this->whichDigit);
                    //guess += '3';
                }
                else
                {
                    guess += '*';
                }
            }
            this->whichPlace = 0;
            this->isFirstPlace = false;
            this->whichDigit++;
            this->isFirstDigit = false;
        }
    }
    else
    {
        guess = this->lastGuess;
    }
    this->numOfGuess++;
    return guess;
}

void SmartGuesser::startNewGame(uint length)
{
    this->length = length;
    this->lastGuess = "";
    this->numOfGuess = 0;
    this->sumOfArray = 0;
    this->whichDigit = 0;
    this->whichPlace = 0;
    for (int i = 0; i < this->length; i++)
    {
        this->allRightCharsOrdered.push_back('*');
    }
    this->isFirstDigit = true;
    this->isFirstPlace = true;
    for (int i = 0; i < 10; i++)
    {
        this->whichNumbersAreIn[i] = 0;
    }
}

SmartGuesser::SmartGuesser()
{
    this->length = -5;
    this->lastGuess = "";
    this->numOfGuess = 0;
    this->sumOfArray = 0;
    this->whichDigit = 0;
    this->whichPlace = 0;
}

void SmartGuesser::learn(calcFunOutput arg)
{
    if (this->numOfGuess < 10 && this->sumOfArray < length)
    {
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!sum of array->"<<this->sumOfArray<<endl;
        this->whichNumbersAreIn[this->numOfGuess - 1] = arg.bull;
        sumOfArray += arg.bull;
        if (this->numOfGuess == 9 || this->sumOfArray == length)
        {
            for (int i = 0; i < 10; i++)
            {
                cout << this->whichNumbersAreIn[i] << "//";
            }
            cout << endl;
            for (int i = 0; i < 10; i++)
            {
                cout << "which cell->" << i << endl;

                if (this->whichNumbersAreIn[i] != 0)
                {
                    cout << "which guess->" << this->numOfGuess << endl;

                    for (int j = 0; j < this->whichNumbersAreIn[i]; j++)
                    {
                        cout << "went to add a num in VECOTR MESSY" << endl;
                        cout << "value of cell->" << this->whichNumbersAreIn[i] << "which cell->" << i << endl;
                        char aboutToGoIn = '0' + i;
                        this->allRightCharsMessy.push_back(aboutToGoIn);
                    }
                }
            }
        }
    }
    else if (this->whichDigit < length)
    {
        int rightNumOfPlace = 0;
        if (this->whichPlace == 0 && !this->isFirstPlace)
        {
            rightNumOfPlace = 3;
        }
        else if (this->whichPlace != 0)
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
            cout << "size of messy chars VECTOR>>" << this->allRightCharsMessy.size() << endl;
            cout << "which digit>>" << this->whichDigit << endl;

            this->allRightCharsOrdered.at(rightNumOfPlace) = this->allRightCharsMessy.at(this->whichDigit);
        }
    }
    else
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
