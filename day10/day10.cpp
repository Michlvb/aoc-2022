#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>

using namespace std;

const string WHITESPACES = " \n\r\t\f\v";

class CPU
{
    public:
        CPU()
        {
            this->X = 1;
            this->div = 20;
            this->width = 40;
            this->height = 6;
            this->cycles = 0;
            this->signal_strength = 0;
        }


        int getSignalStrength()
        {
            return this->signal_strength;
        }

        int getRegisterValue()
        {
            return this->X;
        }

        int getCycle()
        {
            return this->cycles;
        }

        void checkSignalStrength()
        {
            if ((this->cycles % this->div) == 0 && this->div <= 220)
            {
                this->signal_strength += (this->cycles * this->X);
                this->div += 40;
            }
        }

        void renderMap()
        {
            for(string line : this->map)
            {
                cout << line << endl;
            }
        }

        void CRT()
        {
            if ((this->cycles % 40) >= (this->X  - 1) && (this->cycles % 40) <= (this->X + 1))
                this->curr_row += '#';
            else
                this->curr_row += '.';

            if (this->curr_row.length() == 40)
            {
                this->map.push_back(this->curr_row);
                this->curr_row.clear();
            }
        }

        void cycle(ifstream &fs)
        {
            string line;

            while(getline(fs, line))
            {
                string instruction = line.substr(0,line.find_first_of(WHITESPACES));
                if (instruction == "noop")
                {
                    this->CRT();
                    this->cycles++;
                    this->checkSignalStrength();
                }
                else if (instruction == "addx")
                {
                    this->CRT();
                    this->cycles++;
                    this->checkSignalStrength();
                    this->CRT();
                    this->cycles++;
                    this->checkSignalStrength();
                    int value = stoi(line.substr(line.find_first_of(WHITESPACES) + 1));
                    this->X += value;
                }
            }
            cout << "Signal strength: " << this->signal_strength << endl;
        }

    private:
        int X;
        int cycles;
        int div;
        int width;
        int height;
        int signal_strength;
        string  curr_row;
        vector<string> map;
        set<string> instruction_set;
};

int main(int ac, char *av[])
{
    ifstream fs(av[1]);
    CPU cpu;

    if (!fs.good())
        cerr << "Error while trying to open file" << endl;

    cpu.cycle(fs);
    cpu.renderMap();
    return 0;
}