#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string CHARACTERS = " \n\r\t\f\v";
const int UNUSED_SPACE = 30000000;
const int TOTAL_DISK_SPACE = 70000000;

class Directory 
{
    public:
    Directory(string dirname)
    {
        this->dirName = dirname;
    }

    public:
    string  dirName;
    vector<Directory*> subdirectories;
    Directory *parent;
    map<string, int> files;
    int totalSize;
};


void    printOutFS(Directory *dir)
{
    cout << dir->dirName << endl;
    cout << "Total size: " << dir->totalSize << endl;
    for (auto file = dir->files.begin(); file != dir->files.end(); file++) 
    {
        cout << file->second << ": " << file->first << endl;
    }

    cout << endl;

    if (dir->subdirectories.size() == 0)
        return ;

    for (Directory *subdir: dir->subdirectories)
    {
        printOutFS(subdir);
    }
}

void  partOne(Directory *dir, int threshold, int &total)
{
    if (dir->totalSize <= threshold)
    {
        total += dir->totalSize;
    }

    if (dir->subdirectories.size() == 0)
        return ;
    
    for (Directory *subdir: dir->subdirectories)
    {
        partOne(subdir, threshold, total);
    }
}

void  smallestFolderToDelete(Directory *dir, int threshold, vector<int> &values)
{
    if (dir->totalSize >= threshold)
    {
        values.push_back(dir->totalSize);
    }

    if (dir->subdirectories.size() == 0)
        return ;

    for(Directory *subdir: dir->subdirectories)
    {
        smallestFolderToDelete(subdir, threshold, values);
    }
}

int    IncludeSubSize(Directory *dir)
{
    if (dir->subdirectories.size() == 0)
    {
        return dir->totalSize;
    }

    for (Directory *subdir: dir->subdirectories)
    {
        dir->totalSize += IncludeSubSize(subdir);
    }
    return dir->totalSize;
}

void    create_dirs(ifstream &fs, int part)
{
    string line;
    int total;
    vector<int> minDirs;
    
    Directory *root = new Directory("/");
    Directory *curr = root;

    curr->totalSize = 0;
    curr->parent = NULL;
    total = 0;

    while (getline(fs, line))
    {
        if (line[0] == '$')
        {
            string command = line.substr(2, line.find_first_of(CHARACTERS) + 1);
            string input;
            if (command == "cd")
            {
                input = line.substr(line.find(command) + 3);
                if (input != "..")
                {
                    for(Directory* dir: curr->subdirectories)
                    {
                        if (dir->dirName == input)
                        {
                            curr = dir;
                        }
                    }
                }
                else
                {
                    curr = curr->parent;
                }
            }
        }
        else if (line.find("dir") != string::npos)
        {
            int pos = line.find_first_of(CHARACTERS);
            string dirName = line.substr(pos + 1);
            Directory *newDir = new Directory(dirName);
            newDir->parent = curr;
            newDir->totalSize = 0;
            curr->subdirectories.push_back(newDir);
        }
        else if (isdigit(line[0]))
        {
            int cut = line.find_first_of(CHARACTERS);
            int size = stoi(line.substr(0, cut));
            string fileName = line.substr(cut + 1);
            curr->files.insert(pair<string, int>(fileName, size));
            curr->totalSize += size;
        }
    }
    IncludeSubSize(root);
    if (part == 1)
    {
        partOne(root, 100000, total);
        cout << "Total: " << total << endl;
    }
    else if (part == 2)
    {
        smallestFolderToDelete(root, (UNUSED_SPACE - (TOTAL_DISK_SPACE - root->totalSize)), minDirs);
        cout <<  "Min value: " << *min_element(minDirs.begin(), minDirs.end()) << endl;
    }
    // printOutFS(root);
    fs.close();
}

int main(int ac, char *argv[])
{
    int part;
    if (ac < 3)
    {
        cerr << "Insufficient amount of params supplied, expects: <filename> & <part>" << endl;
        return 1;
    }

    ifstream fs(argv[1]);
    try 
    {
        part = stoi(argv[2]);
        if(!fs.good())
        {
            cerr << "Failed to open file: " << argv[1] << endl;
            return 1;
        }
    }
    catch (invalid_argument& e)
	{
		cerr << e.what() << endl;
		return (1);
    }

    create_dirs(fs, part);
    return 0;
}
