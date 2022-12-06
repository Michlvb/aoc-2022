#include <iostream>
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <set>

using namespace std;

bool    check_duplicate(string value)
{
    bool            found_dup;
    set<char>       unique_values;

    found_dup = false;
    for(char c: value)
    {
        if (unique_values.count(c) > 0)
        {
            found_dup = true;
            break;
        } else {
            unique_values.insert(c);
        }
    }
    return found_dup;
}

void    find_marker(string filename, int range)
{
    string  	    line;
    string          store;
    char            c;
    int             pos;
    
    ifstream    fs(filename);

    pos = 0;
    for(; fs.get(c); pos++)
    {
        if (store.length() == range)
        {
            if (!check_duplicate(store))
                break ;
            store.erase(0,1);
        }
        store += c;
    }

    cout << "Found marker on position: " << pos << endl;
}

int main(int ac, char *argv[])
{
    int     range_of_unique;

    if (ac < 3)
    {
        cerr << "Insufficient amount of params supplied, expects: <filename> & <range of unique values>" << endl;
        return (1);
    }
    try 
    {
        range_of_unique = stoi(argv[2]);
        ifstream fs(argv[1]);
        if (!fs.good())
        {
            cerr << "File doesn't exist" << endl;
            return 1;
        }
        fs.close();
    }
    catch (invalid_argument& e)
	{
		cerr << e.what() << endl;
		return (1);
    }
    
    find_marker(argv[1], range_of_unique);
    return 0;
}