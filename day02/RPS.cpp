#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <string.h>

using namespace std;

#define WIN 6
#define DRAW 3
#define LOSS 0

bool if_won_part_one(char my_input, char opp_input)
{
    if ((my_input == 'X' && opp_input == 'C') || \
        (my_input == 'Y' && opp_input == 'A') || \
        (my_input == 'Z' && opp_input == 'B'))
        return (true);
    else
        return (false);
}

int go_for_win(char opp_input)
{
    if (opp_input == 'C')
        return (1);
    else if(opp_input == 'B')
        return (3);
    else
        return (2);
}

int go_for_loss(char opp_input)
{
    if (opp_input == 'C')
        return (2);
    else if(opp_input == 'B')
        return (1);
    else
        return (3);
}

int main(int argc, char *argv[]) 
{
    string content;
    char counter_attack;
    char opponent_attack;
    int my_score = 0;
    bool first_part;

    if (argc != 2)
        return 1;

    if (strcmp(argv[argc-1], "1") == 0)
        first_part = true;
    else if (strcmp(argv[argc-1], "2") == 0)
        first_part = false;
    else
    {
        return 1;
    }

    map<char, int> my_map;
    map<char, int> opponent_map;

    opponent_map.insert(pair<char, int>('A', 1));
    opponent_map.insert(pair<char, int>('B', 2));
    opponent_map.insert(pair<char, int>('C', 3));

    my_map.insert(pair<char, int>('X', 1));
    my_map.insert(pair<char, int>('Y', 2));
    my_map.insert(pair<char, int>('Z', 3));

    fstream fs("input.txt");

    while (getline(fs, content))
    {
        int value = 0;
        char opponent_move = content[0];
        char my_move = content[2];
        
        auto opp = opponent_map.find(opponent_move);
        auto me = my_map.find(my_move);

        if (first_part == true)
        {
            if (me->second == opp->second)
                my_score += (me->second + DRAW);
            else if (if_won_part_one(me->first, opp->first))
                my_score += (me->second + WIN);
            else 
                my_score += (me->second + LOSS);
        } 
        else
        {
            if (me->first == 'Z')
            {
                value = go_for_win(opp->first);
                my_score += (value + WIN);
            }
            else if (me->first == 'Y')
            {
                my_score += (opp->second + DRAW);
            } else
            {
                value = go_for_loss(opp->first);
                my_score += (value + LOSS);
            }
        }
       
    }
    fs.close();
    cout << "Score: " << my_score << endl;
    return 0;
}