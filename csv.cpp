#include "csv.hpp"

int Csv::getline(string& str)
{
    char c;

    for (line = ""; fin.get(c) && !endofline(c);)
        line += c;
    cout << line << endl;
    split();
    str = line;
    return !fin.eof();
}

string Csv::getfield(int n)
{
    if (n < 0 || n >= field.size())
    {
        return "";
    }
    else
    {
        return field[n];
    }
}

int Csv::getnfield()
{
    return field.size();
}

int Csv::split()
{
    string fld;
    int i, j;
    nfield = 0;

    if (line.length() == 0)
        return 0;

    i = 0;
    do 
    {
        if (i < line.length() && line[i] == '"')
            j = advquoted(line, fld, ++i);
        else
            j = advplain(line, fld, i);
        field.push_back(fld);
        ++nfield;
        i = j + 1;

    } while (j < line.length());
}

bool Csv::endofline(char c)
{
    bool eol = (c == '\r' || c == '\n');
    if (c == '\r')
    {
        fin.get(c);
        if (!fin.eof() && c != '\n')
            fin.putback(c);
    }
    
    return eol;
}

int Csv::advplain(const string& line, string& fld, int start)
{
    int pos = line.find_first_of(fieldsep, start);
    if (pos > line.size())
    {
        pos = line.size();
    }
    fld = string(line, start, pos - start);
    return pos;
}

int Csv::advquoted(const string& line, string& fld, int start)
{
    fld = "";

    int j;
    for (j = start; j < line.length(); ++j)
    {
        if (line[j] == '"' && line[++j] != '"')
        {
            int k = line.find_first_of(fieldsep, j);
            if (k > line.length())
            {
                k = line.length();
            }

            for (k -= j; k > 0; --k)
            {
                fld += line[j++];
            }

            break;
        }

        fld += line[j];
    }

    return j;
}

int main(int argc, char** argv)
{
    Csv c;
    string line;

    while (c.getline(line) != 0)
    {
        cout << "line = '" << line << "'\n";
        for (int i = 0; i < c.getnfield(); ++i)
        {
            cout << "field[" << i << "] = '" << c.getfield(i) << "'\n";
        }
    }

    return 0;
}