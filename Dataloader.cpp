#include "Dataloader.h"

#include <stdlib.h>
#include <iostream>

DataLoader::DataLoader(const string& path) {
    _path = path;
    _costsParser = CsvParser(path + "\\Costs.csv");
    _transportParser = CsvParser(path + "\\Transport.csv");
    _caffeAndCinemaParser = CsvParser(path + "\\Caffe-and-cinema.csv");
    _instituteParser = CsvParser(path + "\\Institute.csv");
}

uint DataLoader::getOtherCosts(const string& city, uint age) const {
    if (age == 0) {
        return 0;
    }
    vector<string> keys{city, to_string(age)};
    map<string, string> result = _costsParser.find(keys);
    return stoi(result["Other costs"]);
}

uint DataLoader::getHomeFoodCost(const string& city, uint age) const {
    if (age == 0) {
        return 0;
    }
    vector<string> keys{city, to_string(age)};
    map<string, string> result = _costsParser.find(keys);
    return stoi(result["Average food cost per month"]);
}

uint DataLoader::getTransportCost(const string &city, const string &address, const string &institute) const {
    vector<string> keys = {city, address, institute};
    map<string, string> result = _transportParser.find(keys);
    return stoi(result["Transport cost"]);
}

uint DataLoader::getInstituteDinner(const string &city, const string &institute) const {
    vector<string> keys = {city, institute};
    map<string, string> result = _instituteParser.find(keys);
    return stoi(result["Dinner cost"]);
}

uint DataLoader::getCinemaCost(const string &city, const string &address, const string &cinema) const {
    vector<string> keys = {city, address, cinema};
    map<string, string> result = _caffeAndCinemaParser.find(keys);
    return stoi(result["Cinema cost"]);
}

uint DataLoader::getCaffeCost(const string &city, const string &address, const string &caffe) const {
    vector<string> keys = {city, address, caffe};
    map<string, string> result = _caffeAndCinemaParser.find(keys);
    return stoi(result["Average caffe cost"]);
}


CsvParser& DataLoader::getTransportParser() {
    return _transportParser;
}

CsvParser& DataLoader::getCostsParser() {
    return _costsParser;
}

CsvParser& DataLoader::getInstituteParser() {
    return _instituteParser;
}

CsvParser& DataLoader::getWeekendsParser() {
    return _caffeAndCinemaParser;
}


void DataLoader::setTransportData(const vector<vector<string>>& newData) {
    _transportParser.setData(newData);
}

void DataLoader::setInstituteData(const vector<vector<string>>& newData) {
    _instituteParser.setData(newData);
}

void DataLoader::setCostsData(const vector<vector<string>>& newData) {
    _costsParser.setData(newData);
}

void DataLoader::setWeekendsData(const vector<vector<string>>& newData) {
    _caffeAndCinemaParser.setData(newData);
}
