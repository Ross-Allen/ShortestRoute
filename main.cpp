#include <iostream>

#include "Algernon.h"

using namespace std;

int main()
{
    cout << "Game Input File: ";
    std::string fileName;
    getline(cin, fileName);

#ifdef JARVIS
    cout << "=~=" << endl;
#else
    cout << endl;
#endif

    Algernon algernon;
    algernon.loadMaze(fileName);
    if (algernon.solveMaze())
    {
        cout << "Solved maze, path length: " << algernon.getPathLength() << endl;
    }
    else
    {
        cout << "Maze was unsolvable" << endl;
    }

    return 0;
}