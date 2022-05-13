#include "csvParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>


CsvParser::CsvParser(const string& path) {
    _data.clear();
    ifstream file;
    file.open(path);

    if (!file.is_open()) {
        throw out_of_range("File not found: '" + path + "'");
    }

    string line, word;

    while (getline(file,line))
    {
        stringstream ss(line);
        vector<string> row;
        while (getline(ss, word, ','))
        {
            row.push_back(word);
        }
        _data.push_back(row);
    }
    if (_data.empty()) {
        throw out_of_range("File " + path + " is empty!");
    }
    for (int i = 1; i < _data.size(); ++i) {
        if (_data[i].size() != _data[i - 1].size()) {
            throw out_of_range("Number of columns in file " + path + " is not constant!");
        }
    }
    _filePath = path;
}

map<string, string> CsvParser::find(const vector<string>& keys) const {
    map<string, string> result;
    for (auto&& item: _data) {
        int count = 0;
        for (auto&& item1: keys) {
            if (!findInRow(item1, item)) {
                break;
            }
            count++;
            if (count == keys.size()) {
                for (int i = 0; i < _data[0].size(); ++i) {
                    result.insert(pair<string, string>(_data[0][i], item[i]));
                }
                return result;
            }
        }
    }
    throw out_of_range("");
}

bool CsvParser::findInRow(const string &key, const vector<string>& row) const {
    for (auto&& item: row) {
        if (item == key) {
            return true;
        }
    }
    return false;
}

void CsvParser::setData(const vector<vector<string>>& newData) {
    _data = newData;
    updateFile();
}

vector<vector<string>>CsvParser::getData() const {
    return _data;
}

void CsvParser::updateFile() const{
    ofstream file;
    file.open(_filePath);
    for (auto&& item: _data) {
        for (int i = 0; i < item.size() - 1; ++i) {
                file << item[i] << ",";
        }
        file << item.back() << endl;;
    }
}
