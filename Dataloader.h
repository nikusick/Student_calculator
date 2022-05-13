#ifndef STUDENT_DATALOADER_H
#define STUDENT_DATALOADER_H
#include <string>
#include "csvParser.h"

typedef unsigned int uint;
using namespace std;


class DataLoader {
private:
    string _path;
    CsvParser _transportParser;
    CsvParser _instituteParser;
    CsvParser _costsParser;
    CsvParser _caffeAndCinemaParser;

public:
    DataLoader() = default;
    DataLoader(const string& path);

    void setTransportData(const vector<vector<string>>&);
    void setInstituteData(const vector<vector<string>>&);
    void setCostsData(const vector<vector<string>>&);
    void setWeekendsData(const vector<vector<string>>&);

    uint getOtherCosts(const string& city, uint age) const;
    uint getHomeFoodCost(const string& city, uint age) const;
    uint getTransportCost(const string& city, const string& address, const string& institute) const;
    uint getInstituteDinner(const string& city, const string& institute) const;
    uint getCinemaCost(const string& city, const string& address,  const string& cinema) const;
    uint getCaffeCost(const string& city, const string& address, const string& caffe) const;

    CsvParser& getTransportParser();
    CsvParser& getCostsParser();
    CsvParser& getInstituteParser();
    CsvParser& getWeekendsParser();
};

#endif //STUDENT_DATALOADER_H
