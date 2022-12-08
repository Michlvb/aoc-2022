#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool is_visible_top(vector<vector<char> > map, int rowpos, int colpos, int highest)
{
    bool visible = true;

    for (int row = rowpos - 1; row >= 0; row--)
    {
        if ((map[row][colpos] >= highest))
            visible = false;
    }

    return visible;
}

bool is_visible_bottom(vector<vector<char> > map, int rowpos, int colpos, int highest)
{
    bool visible = true;

    for (int row = rowpos + 1; row < map.size(); row++)
    {
        if (map[row][colpos] >= highest)
            visible = false;
    }
    return visible;
}

bool is_visible_left(vector<vector<char> > map, int rowpos, int colpos, int highest)
{
    bool visible = true;

    for (int col = colpos - 1; col >= 0; col--)
    {
        if (map[rowpos][col] >= highest)
            visible = false;
    }

    return visible;
}

bool is_visible_right(vector<vector<char> > map, int rowpos, int colpos, int highest)
{
    bool visible = true;

    for (int col = colpos + 1; col < map[rowpos].size(); col++)
    {
        if (map[rowpos][col] >= highest)
            visible = false;
    }

    return visible;
}

void    partOne(vector<vector<char> > map)
{
    vector<int> visible;
    int row = map.size() - 1;
    int col = map[0].size() - 1;
    int highest;


    for (int i = 0; i <= col; i++) {

        visible.push_back((map[0][i]) - '0');
        visible.push_back((map[row][i]) - '0');
    }
     
    for (int i = 1; i <= row - 1; i++) 
    {
        visible.push_back((map[i][0]) - '0');
        visible.push_back((map[i][col]) - '0');
    }

    // Check if tree is visible
    for(int row = 1; row < map.size() - 1; row++)
    {
        for (int col = 1; col < map[row].size() - 1; col++)
        {
            highest = map[row][col];
            if (is_visible_top(map, row, col, highest) ||
                is_visible_bottom(map, row, col, highest) ||
                is_visible_left(map, row, col, highest) ||
                is_visible_right(map, row, col, highest)
                )
            {
                visible.push_back(map[row][col]);
            }

        }
    }
    
    cout << "Visible: " << visible.size() << endl;   
}

//Part 2
int calScenicScore(vector<vector<char> > map, int x, int y, int currHeight)
{
    int treesSeenTop = 0;
    int treesSeenLeft = 0;
    int treesSeenBottom = 0;
    int treesSeenRight = 0;
    
    // Top
    for (int row = x - 1; row >= 0; row--)
    {
        treesSeenTop++;
        if ((map[row][y] - '0') >= currHeight)
            break;
    }

    // Bottom
    for (int row = x + 1; row < map.size(); row++)
    {
        treesSeenBottom++;
        if ((map[row][y] - '0') >= currHeight)
            break;
    }

    // Left
    for (int col = y - 1; col >= 0; col--)
    {
        treesSeenLeft++;
        if ((map[x][col] - '0') >= currHeight)
            break;
    }

    // Right
    for (int col = y + 1; col < map[x].size(); col++)
    {
        treesSeenRight++;
        if ((map[x][col] - '0') >= currHeight)
            break;
    }
    return (treesSeenTop * treesSeenRight * treesSeenBottom * treesSeenLeft);
}


void    partTwo(vector<vector<char> > &map)
{
    int row = map.size();
    int col = map[0].size();
    int currHeight;
    vector<int> scenicScores;

    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < col; y++)
        {
            currHeight = map[x][y] - '0';
            scenicScores.push_back(calScenicScore(map, x, y, currHeight));
        }
    }
    auto max = max_element(scenicScores.begin(), scenicScores.end());
    cout << "Highest scenic score: " << *max << endl;
}

vector<vector<char> >  getMap(ifstream &fs, vector<vector<char> > &map)
{
    char c;
    int rowLen = -1;
    int colLen = 0;
    string line;

    while(getline(fs, line))
    {
        if (rowLen == -1)
        {
            rowLen = line.length();
        }
        colLen++;
    }

    fs.clear();
    fs.seekg(0);

    map.resize(rowLen);

    for (auto& row : map)
    {
        row.resize(colLen);
    }

    for(auto &row : map)
    {
        for (auto &element : row)
        {
            fs.get(c);
            element = c; 
        }
        fs.get(c);
    }
    fs.close();

    return map;
}

int main(int ac, char *argv[])
{
    vector<vector<char> > map;

    if (ac < 2)
    {
        cerr << "Insufficient amount of params supplied, expects: <filename>" << endl;
        return 1;
    }

    ifstream fs(argv[1]);
    if(!fs.good())
    {
        cerr << "Failed to open file: " << argv[1] << endl;
        return 1;
    }

    getMap(fs, map);
    partOne(map);
    partTwo(map);
    return 0;
}
