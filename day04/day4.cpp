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

bool	validate_first_part(int start_first, int end_first, int start_sec, int end_sec)
{
	if ((start_first <= start_sec && end_first >= end_sec) || (start_sec <= start_first && end_sec >= end_first))
		return (true);
	return (false);
}

bool	validate_second_part(int start_first, int end_first, int start_sec, int end_sec)
{
	if ((start_first <= start_sec && end_first >= start_sec) || (start_sec <= end_first && end_sec >= start_first))
		return (true);
	return (false);
}

int main(int argc, char *argv[])
{
	string  	line;
	int	    	contains;
	int	 		part;

	if (argc < 3)
		return (1);
	
	try
	{
		part = stoi(argv[2]);
	} catch (invalid_argument& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	ifstream fs(argv[1]);
	if (!fs.good())
		cerr << "File doesn't exist" << endl;
	
	contains = 0;
	while (std::getline(fs, line))
	{
		string firstPair = line.substr(0, line.find(','));
		string secondPair = line.substr(line.find(',') + 1);

		int start_first = std::stoi((firstPair.substr(0, firstPair.find('-'))));
		int end_first = std::stoi((firstPair.substr(firstPair.find('-') + 1)));

		int start_sec = std::stoi((secondPair.substr(0, secondPair.find('-'))));
		int end_sec = std::stoi((secondPair.substr(secondPair.find('-') + 1)));

		if (part == 1)
		{
			if (validate_first_part(start_first, end_first, start_sec, end_sec) == true)
				contains++;
		}
		else if (part == 2)
		{
			if (validate_second_part(start_first, end_first, start_sec, end_sec) == true)
				contains++;
		} 
		else {
			cerr << "Part: " << part << " not found" << endl;
			exit(1);
		}
	}
	fs.close();
    cout << "Pairs found: " << contains << endl;
    return 0;
}