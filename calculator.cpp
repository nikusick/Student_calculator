#include "calculator.h"

uint workDaysCount = 24;

uint getMonthDays(uint month) {
    uint months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return months[month - 1];
}

uint getWorkdays(uint month) {
    return workDaysCount;
}

uint getWeekendDays(uint month) {
    return getMonthDays(month) - workDaysCount;
}


uint Calculator::getWeekendCost(DataLoader& dataLoader, const string& city, const string& address, const string& cafe, const string& cinema) const {
    return dataLoader.getCinemaCost(city, address, cinema) + dataLoader.getCaffeCost(city, address, cafe);
}

uint Calculator::getWorkdayCost(DataLoader& dataLoader, const string &city, const string &address, const string &institute) const {
    return 2 * dataLoader.getTransportCost(city, address, institute) + dataLoader.getInstituteDinner(city, institute);
}

uint Calculator::getCosts(DataLoader& dataLoader, uint month, const string& city, const string& address,
                          uint age, const string& institute, const string& cafe, const string& cinema) const {
    return getWorkdays(month) * getWorkdayCost(dataLoader, city, address, institute) +
           getWeekendDays(month) * getWeekendCost(dataLoader, city, address, cafe, cinema) +
           dataLoader.getOtherCosts(city, age) + dataLoader.getHomeFoodCost(city, age);
}
