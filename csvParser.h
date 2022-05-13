#ifndef STUDENT_CSV_READER_H
#define STUDENT_CSV_READER_H
#include <string>
#include <vector>
#include <map>


using namespace std;

class CsvParser {
private:
    string _filePath;
    vector <vector <string>> _data;

    bool findInRow(const string &key, const vector<string>& row) const;
    void updateFile() const;
public:
    CsvParser() = default;
    CsvParser(const string& path);
    map<string, string> find(const vector<string>&) const;
    void setData(const vector<vector<string>>& newData);
    vector <vector <string>> getData() const;
};

#endif //STUDENT_CSV_READER_H
