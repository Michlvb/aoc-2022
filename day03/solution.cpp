#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <string.h>

using namespace std;

//Already tried:
// - 2104
//


#define LOWER 1
#define UPPER 27

char alph[] = {
    'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h',
    'i', 'j', 'k', 'l', 
    'm', 'n', 'o', 'p',
    'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 
    'y', 'z'
};

int main(int argc, char *argv[]) 
{
    string line;
    int  sum_of_values = 0;
    int add;
    int len;
    int i;
    fstream fs("input.txt");

    bool found = false;
    int n = sizeof(alph);

    sum_of_values = 0;
    while (std::getline(fs, line))
    {
        len = line.length();
        string substrFirstPart = line.substr(0, (len / 2));
        string substrSecPart = line.substr((len / 2), len);

        for(int j = 0; j < substrFirstPart.length(); j++)
        {
            for (int k = 0; k < substrSecPart.length(); k++)
            {
                if (substrFirstPart[j] == substrSecPart[k])
                {
                    char same = substrFirstPart[j];
                    if (islower(same))
                        add = LOWER;
                    else
                        add = UPPER;

                    for (int c = 0; c < n; c++)
                    {
                        if (tolower(same) == alph[c])
                        {
                            sum_of_values += (c + add);
                        }
                    }
                    found = true;
                    break;
                }
            }
            if (found == true)
                break;
        }
        found = false;
    }
    fs.close();
    cout << "Score: " << sum_of_values << endl;
    return 0;
}
