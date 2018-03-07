#ifndef _ALGERNON_H
#define _ALGERNON_H

#include <string>

using namespace std;

enum Thing
{
  SPACE,
  WALL,
  FLOWER,
  START,
  CHEESE,
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Algernon
{
  public:
    Algernon(void);

    void loadMaze(string file);  // Write this function
    void printMaze(void);  // Write this function
    bool solveMaze(void);
    int getPathLength(void);

  private:
    void updateDisplay(void);    
    void storeMazeState(void);  // Write this function
    bool isDirOrCheese(Thing thing);  // Write this function
    Thing updateLocation(int row, int col);  // Write this function
    void dropFlowers(void);  // Write this function
    void clearDirections(void);  // Write this function

    static const int ROWS = 20;
    static const int COLS = 40;
    static const int DELAY_MILLISECONDS = 250;

    Thing maze[ROWS][COLS];
    Thing previousMaze[ROWS][COLS];
    int startRow;
    int startColumn;
    int cheeseRow;
    int cheeseColumn;
};

#endif // _ALGERNON_H
