#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <string.h>
#include <vector>

using namespace std;

#define LOWER 1
#define UPPER 27

int main(int argc, char *argv[]) 
{
    string line;
    fstream fs("input.txt");

    int  sum_of_values = 0;
    bool found = false;

    std::vector<std::string> groups;

    while (std::getline(fs, line))
    {
        if (groups.size() == 2)
        {   
            for(int i = 0; i < line.length(); i++)
            {
                if ((groups[0].find(line[i]) != string::npos) && (groups[1].find(line[i]) != string::npos))
                {
                    found = true;
                    if (islower(line[i]))
                        sum_of_values += (line[i] - 'a' + LOWER);
                    else
                        sum_of_values += (line[i] - 'A' + UPPER);
                    break;
                }
            }
        }
        if (found == true)
        {
            groups.clear();
            found = false;
        } else {
            groups.push_back(line);
        }
    }
    fs.close();
    cout << "Score: " << sum_of_values << endl;
    return 0;
}


/*
Resources:
- https://stackoverflow.com/questions/10750057/how-do-i-print-out-the-contents-of-a-vector
- https://thispointer.com/c-check-if-string-contains-a-character/
*/