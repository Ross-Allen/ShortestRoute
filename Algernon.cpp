#include <iostream>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "Algernon.h"

Algernon::Algernon(void)
{
  startRow = 0;
  startColumn = 0;
  cheeseRow = 0;
  cheeseColumn = 0;
}

bool Algernon::solveMaze(void)
{
  bool madeUpdates = true;
  bool foundStart = false;

  while (madeUpdates && !foundStart)
  {
    // Print maze
    updateDisplay();

    // Store current state before we modify anything
    storeMazeState();

    // Reset to not having made any modifications to the maze this round
    madeUpdates = false;

    // Look at previous maze state, and make updates to current maze
    for (int row = 0; row < ROWS; row++)
    {
      for (int col = 0; col < COLS; col++)
      {
        maze[row][col] = updateLocation(row, col);

        // See if we made a change since last time
        if (maze[row][col] != previousMaze[row][col])
        {
          madeUpdates = true;

          // If we replaced the start position, then we found a path!
          if (row == startRow && col == startColumn)
          {
            foundStart = true;
          }
        }
      }
    }
  }

  // If we were able to reach the start, then start from the starting location and work towards the cheese, replacing with flowers
  if (foundStart)
  {
    dropFlowers();
  }

  // Get rid of all the (now useless) directions
  clearDirections();

  // Write start and cheese back into the maze
  maze[startRow][startColumn] = START;
  maze[cheeseRow][cheeseColumn] = CHEESE;

  printMaze();

  return foundStart;
}

void Algernon::updateDisplay(void)
{
  printMaze();

#ifdef JARVIS
  cout << "=~=" << endl;
  // Do nothing, allow animation viewer to set rate
#elif defined WIN32
  cout << endl;
  Sleep(DELAY_MILLISECONDS);
#else // Linux, Mac
  cout << endl;
  usleep(DELAY_MILLISECONDS * 1000);
#endif
}

int Algernon::getPathLength(void)
{
  int pathLength = 0;
  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j)
    {
      if (maze[i][j] == FLOWER)
      {
        pathLength++;
      }
    }
  }

  return pathLength;
}