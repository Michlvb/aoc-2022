#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>
#include <cmath>
#include <queue>

using namespace std;

const string WHITESPACES = " \n\r\t\f\v\0";

class Monkey
{
    public:
        Monkey(){this->inspected = 0;}

    public:
        queue<int> items;
        int multiplier;
        int divisor;
        int false_monkey;
        int true_monkey;
        int inspected;
        int worry_lvl;
        char operand;
};

class Human
{
    public:
        Human() {this->worry_lvl = 1;}
    public:
        int worry_lvl;
};

class Day10
{

    public:
        Day10(int rounds){this->rounds = rounds;}
        
        void monkeyInTheMiddle()
        {
            while (this->rounds > 0)
            {
                for(Monkey *monkey: this->monkeys)
                {
                    while (!monkey->items.empty())
                    {
                        int item = monkey->items.front();
                        monkey->items.pop();
                        monkey->inspected++;
                        switch(monkey->operand)
                        {
                            case '*':
                                if (monkey->multiplier == -1)
                                    monkey->worry_lvl = item * item;
                                else
                                    monkey->worry_lvl = item * monkey->multiplier;
                                break;
                            case '+':
                                if (monkey->multiplier == -1)
                                    monkey->worry_lvl = item + item;
                                else
                                    monkey->worry_lvl = item + monkey->multiplier;
                                break;
                        }
                        // Divide worry level
                        monkey->worry_lvl = (int)round(monkey->worry_lvl / 3);

                        // Throw to other monkey
                        if ((monkey->worry_lvl % monkey->divisor) == 0)
                            this->monkeys[monkey->true_monkey]->items.push(monkey->worry_lvl);
                        else
                            this->monkeys[monkey->false_monkey]->items.push(monkey->worry_lvl);
                    }
                }
                this->rounds--;
            }
        }
        
        void  find_lvl_monkey_business()
        {
            int cnt = 0;
            for(Monkey *monkey: monkeys)
            {
                cout << "Monkey: " << cnt++ << " inspected items: " <<  monkey->inspected << endl;
            }
            
        }  

        void parseData(char *filename)
        {
            string line;
            ifstream fs(filename);

            if(!fs.good())
            {
                cerr << "Unable to open file" << endl;
                exit(1);
            }

            while (getline(fs, line))
            {
                if (line.find("Monkey") != string::npos)
                {
                    Monkey *new_monkey = new Monkey;
                    while (getline(fs, line))
                    {
                        line.erase(0, line.find_first_not_of(WHITESPACES));
                        if (line == "")
                            break;
                        if (line.find("Starting items:") != string::npos)
                        {
                            string items = line.substr(line.find(":") + 2);
                            stringstream ss(items);
                            string item;
                            while(getline(ss, item, ','))
                            {
                                if (item[0] == ' ')
                                    item.erase(0,1);
                                new_monkey->items.push(stoi(item));
                            }
                        }
                        else if (line.find("Operation:") != string::npos)
                        {
                            string parseOperand = line.substr(line.find("old") + 4);
                            string operand = parseOperand.substr(0, parseOperand.find_first_of(WHITESPACES));
                            string multiplier = line.substr(line.find_last_of(WHITESPACES) + 1);
                            if (multiplier == "old")
                                new_monkey->multiplier = -1;
                            else
                                new_monkey->multiplier = stoi(multiplier);
                            new_monkey->operand = operand[0];
                        }
                        else if (line.find("Test:") != string::npos)
                        {
                            string divisor = line.substr(line.find_last_of(WHITESPACES) + 1);
                            new_monkey->divisor = stoi(divisor);
                        }
                        else if (line.find("If") != string::npos)
                        {
                            string n_monkey = line.substr(line.find_last_of(WHITESPACES) + 1);
                            string sub =  line.substr((line.find_first_of(WHITESPACES) + 1));
                            if (sub.substr(0, sub.find(":"))  == "true")
                                new_monkey->true_monkey = stoi(n_monkey);
                            else
                                new_monkey->false_monkey = stoi(n_monkey); 
                        }
                    }
                    this->monkeys.push_back(new_monkey);
                }
            }
            fs.close();
        }

    public:
        vector<Monkey*> monkeys;
        Human *simpleton;
        int rounds;
        int supermodulo;
};


int main (int ac, char *av[])
{
    Day10 start(10000);

    start.parseData(av[1]);
    start.monkeyInTheMiddle();
    return 0;
}