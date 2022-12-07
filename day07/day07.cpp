#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string CHARACTERS = " \n\r\t\f\v";

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


void    printOutFS(Directory *directory)
{
    cout << directory->dirName << endl;
    cout << "Total size: " << directory->totalSize << endl;
    for (auto file = directory->files.begin(); file != directory->files.end(); file++) 
    {
        cout << file->second << ": " << file->first << endl;
    }

    cout << endl;

    if (directory->subdirectories.size() == 0)
        return ;

    for (int i = 0; i < directory->subdirectories.size(); i++)
    {
        printOutFS(directory->subdirectories[i]);
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
    
    for (int i = 0; i < dir->subdirectories.size(); i++)
    {
        printDirAndSize(dir->subdirectories[i], threshold, total);
    }
}

void  smallestFolderToDelete()
{

}

int    setSizes(Directory *dir)
{
    if (dir->subdirectories.size() == 0)
    {
        return dir->totalSize;
    }

    for (int i = 0; i < dir->subdirectories.size(); i++)
    {
        dir->totalSize += setSizes(dir->subdirectories[i]);
    }
    return dir->totalSize;
}

void    create_dirs(char *filename)
{
    string line;
    int total;

    ifstream fs(filename);
    
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
    setSizes(root);
    partOne(root, 100000, total);
    fs.close();
}

int main(int ac, char *argv[])
{
    if (ac < 2)
    {
        cerr << "Insufficient amount of params supplied, expects: <filename> & <range of unique values>" << endl;
        return 1;
    }

    ifstream fs(argv[1]);
    if(!fs.good())
    {
        cerr << "Failed to open file: " << argv[1] << endl;
        return 1;
    }
    fs.close();

    // create_dirs(argv[1]);

    // Total disk space: 70000000
    // Unused space voor update: 30000000
    // 70.000.000 - 30.000.000 = 40.000.000
    // Find the smallest directory that, 
    // if deleted,
    // would free up enough space on the filesystem to run the update.

    return 0;
}

// 919137 -> correct
