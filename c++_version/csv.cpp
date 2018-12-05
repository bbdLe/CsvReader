#include "csv.hpp"

int Csv::getline(string& str)
{
    char c;

    for (line = ""; fin.get(c) && !endofline(c);)
        line += c;
    split();
    str = line;
    return !fin.eof();
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

int Csv::split()
{
	string fld;
	int i, j;

	if (line.length() == 0)
		return 0;

	field.clear();
	i = 0;
	while (i < line.length())
	{
		if (line[i] == '"')
		{
			j = advquoted(line, fld, ++i);
		}
		else
		{
			j = advplain(line, fld, i);
		}
		field.push_back(fld);
		i = j + 1;
	}

	return 0;
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

	int advPos;
	for (advPos = start; advPos < line.length(); ++advPos)
	{
		if (line[advPos] == '"' && line[++advPos] != '"')
		{
			int fieldSepPos = line.find_first_of(fieldsep, advPos);
			if (fieldSepPos > line.length())
			{
				fieldSepPos = line.length();
			}

			for (int leftChar = fieldSepPos - advPos; leftChar > 0; --leftChar)
			{
				fld += line[advPos++];
			}

			break;
		}

		fld += line[advPos];
	}

	return advPos;
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