#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <array>
#include <ctype.h>
#include <unistd.h>

using namespace std;

string  start_first_part(char *filename)
{
    string line;
    int n_stacks;
    vector<string> stack_values;

    n_stacks = -1;
    ifstream fs(filename);
    
    while (getline(fs, line))
    {
        if (line[0] == ' ' && isdigit(line[1]))
        {
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
            n_stacks = line.length();
            break;
        }
        stack_values.push_back(line);
    }

    if (n_stacks == -1)
    {
        cerr << "Stacks not found in input" << endl;
        fs.close();
        exit(1);
    }
    stack<string> stacks[n_stacks];

    reverse(stack_values.begin(), stack_values.end());

    int end = 3;
    int i = 0;
    for (string v: stack_values)
    {
        for (int start = 0; start < v.length(); start += (end + 1))
        {
            string store = v.substr(start, end);
            if (store.find_first_not_of(' ') != string::npos)
                stacks[i].push(store);
            i++;
        }
        i = 0;
    }

    vector<string> instructions;

    while (getline(fs, line))
    {
        if(line.find_first_not_of(' ') != string::npos)
        {
            string instruction;
            for(char c: line)
            {
                if (isdigit(c))
                {
                    instruction += c;
                }
            }
            instructions.push_back(instruction);
        }
    }
    fs.close();

    // move <amount> from <source> to <destination>
    int amount;
    int src_stack;
    int dest_stack;
    for(string instruction: instructions)
    {
        if (instruction.length() > 3)
        {
            amount = stoi(instruction.substr(0, 2));
            src_stack = (instruction[2] - '0')-1;
            dest_stack = (instruction[3] - '0')-1;
        } 
        else 
        {
            amount = (instruction[0] - '0');
            src_stack = (instruction[1] - '0')-1;
            dest_stack = (instruction[2] - '0')-1;
        }
        // Part 1
        while (amount--)
        {
            string value = stacks[src_stack].top();
            stacks[src_stack].pop();
            stacks[dest_stack].push(value);
        }
        // Part 2
        // stack<string> hold;
        // string value;
        // while (amount--)
        // {
        //     value = stacks[src_stack].top();
        //     stacks[src_stack].pop();
        //     hold.push(value);
        // }
        // while (hold.size() > 0)
        // {
        //     string value = hold.top();
        //     hold.pop();
        //     stacks[dest_stack].push(value);
        // }
    }
    string res;

    for (int i = 0; i < n_stacks; i++)
    {
        res += stacks[i].top();
    }
    cout << res << endl;
    return line;
}

int main(int argc, char *argv[])
{
    string  	    line;
	int	    	    contains;


    if (access(argv[1], F_OK) != 0)
    {
        cerr << "File doesn't exist" << endl;
        return 1;
    }
    
    start_first_part(argv[1]);
    return 0;
}