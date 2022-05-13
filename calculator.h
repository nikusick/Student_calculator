#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include "Dataloader.h"
typedef unsigned int uint;
using namespace std;

class Calculator
{
public:
    Calculator() = default;
    uint getCosts(DataLoader& dataLoader, uint month, const string& city, const string& address,
                  uint age, const string& institute, const string& cafe, const string& cinema) const;
private:
    uint getWeekendCost(DataLoader& dataLoader, const string& city, const string& address, const string& cafe, const string& cinema) const;
    uint getWorkdayCost(DataLoader& dataLoader, const string &city, const string &address, const string &institute) const;
};

#endif // CALCULATOR_H
