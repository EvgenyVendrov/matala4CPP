#include "calculate.hpp"

using namespace bullpgia;

calcFunOutput bullpgia::calculateBullAndPgia(const string choice, const string guess)
{
    // if (choice.length() == 0 || choice.length() != guess.length() || guess.length() == 0)
    // {
    //     throw std::invalid_argument("one of input strings has incorrect length -> it has to be a positive Neutral number");
    // }
    string choiceCpoy = "";
    string guessCopy = "";
    uint bull = 0, pgia = 0;
    choiceCpoy.append(choice);
    guessCopy.append(guess);
    if (choiceCpoy.length() > guessCopy.length())
    {
        for (int i = 0; i < choiceCpoy.length() && i < guessCopy.length(); i++)
        {
            if (guessCopy[i] == choiceCpoy[i])
            {
                bull++;
                guessCopy[i] = 'a';
                choiceCpoy[i] = 'a';
            }
        }

        for (int i = 0; i < guessCopy.length(); i++)
        {
            for (int j = 0; j < choiceCpoy.length(); j++)
            {
                //std::cout<<guessCopy[j]<<","<<choiceCpoy[i]
                if (guessCopy[i] != 'a' && choiceCpoy[j] != 'a' && guessCopy[i] == choiceCpoy[j])
                {
                    guessCopy[i] = 'a';
                    choiceCpoy[j] = 'a';
                    pgia++;
                }
            }
        }
    }
    else
    {

       for (int i = 0; i < guessCopy.length() && i < choiceCpoy.length(); i++)
        {
            if (guessCopy[i] == choiceCpoy[i])
            {
                bull++;
                guessCopy[i] = 'a';
                choiceCpoy[i] = 'a';
            }
        }

        for (int i = 0; i < choiceCpoy.length(); i++)
        {
            for (int j = 0; j < guessCopy.length(); j++)
            {
                if (guessCopy[j] != 'a' && choiceCpoy[i] != 'a' && guessCopy[j] == choiceCpoy[i])
                {
                    guessCopy[j] = 'a';
                    choiceCpoy[i] = 'a';
                    pgia++;
                }
            }
        }
    }
    calcFunOutput output{bull, pgia};
    return output;
}

calcFunOutput::calcFunOutput(const uint bull, const uint pgia)
{
    this->setBull(bull);
    this->setPgia(pgia);
}

void calcFunOutput::setBull(const uint bull)
{
    this->bull = bull;
}

void calcFunOutput::setPgia(const uint pgia)
{
    this->pgia = pgia;
}

std::ostream &bullpgia::operator<<(std::ostream &os, const calcFunOutput &arg)
{
    uint bull = arg.bull;
    uint pgia = arg.pgia;
    return (os << bull << "," << pgia);
}