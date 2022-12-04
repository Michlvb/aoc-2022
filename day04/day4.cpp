#include <iostream>
#include <cstring>  
#include <fstream>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <array>

using namespace std;

bool	if_contains(string needle, string haystack)
{
	if (needle.find(haystack) != string::npos)
		return (true);
	return (false);
}

int main(int argc, char *argv[])
{
	string line;
	int	   contains;

	if (argc < 2)
		return (1);
	
	ifstream fs(argv[argc-1]);

	contains = 0;

	while (std::getline(fs, line))
	{
		string firstPair = line.substr(0, line.find(','));
		string secondPair = line.substr(line.find(',') + 1);

		int start_first = std::stoi((firstPair.substr(0, firstPair.find('-'))));
		int end_first = std::stoi((firstPair.substr(firstPair.find('-') + 1)));

		int start_sec = std::stoi((secondPair.substr(0, secondPair.find('-'))));
		int end_sec = std::stoi((secondPair.substr(secondPair.find('-') + 1)));

		if ((start_first <= start_sec && end_first >= end_sec) || (start_sec <= start_first && end_sec >= end_first))
			contains++;
	}
	fs.close();
    cout << "Score: " << contains << endl;
    return 0;
}