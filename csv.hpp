#ifndef __CSV_HPP
#define __CSV_HPP
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::istream;
using std::cout;
using std::cin;
using std::endl;

class Csv
{
public:
    Csv(istream& fin = cin, string sep = ",") : fin(fin), fieldsep(sep) {}

    int getline(string& str);

    string getfield(int n);

    int getnfield();

private:
    int split();

    bool endofline(char c);

    int advplain(const string& line, string& fld, int start);

    int advquoted(const string& line, string& fld, int start);

private:
    istream& fin;
    string line;
    vector<string> field;
    int nfield;
    string fieldsep;
};

#endif