#pragma once
#include <string>
using namespace std;

namespace bullpgia
{
//basic "chooser" class - which in a way is the interface that define's a chooser from any kind
class Chooser
{
public:
    virtual string choose(uint length) = 0;
};
} // namespace bullpgia