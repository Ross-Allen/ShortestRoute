//
// Created by Ross on 4/25/17.
//
#include <iostream>
#include <fstream>

#include "Algernon.h"

using namespace std;

void Algernon::loadMaze(string file) {
  ifstream inputFile;
  inputFile.open(file);
  char type;
  if (!inputFile.is_open()) {
    cout << "FILE NOT FOUND" << endl;
  } else {
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        inputFile.get(type);
        switch (type) {
          case 'X':
            maze[i][j] = WALL;
            break;
          case 'S':
            maze[i][j] = START;
            startRow = i;
            startColumn = j;
            break;
          case 'C':
            maze[i][j] = CHEESE;
            cheeseRow = i;
            cheeseColumn = j;
            break;
          case ' ':
            maze[i][j] = SPACE;
            break;
          default:
            break;
        }

      }
      inputFile.ignore();
    }
    inputFile.close();
  }


}

void Algernon::printMaze() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      switch (maze[i][j]) {
        case WALL:
          cout << 'X';
          break;
        case SPACE:
          cout << ' ';
          break;
        case FLOWER:
          cout << '*';
          break;
        case START:
          cout << 'S';
          break;
        case CHEESE:
          cout << 'C';
          break;
        case UP:
          cout << '^';
          break;
        case DOWN:
          cout << 'v';
          break;
        case LEFT:
          cout << '<';
          break;
        case RIGHT:
          cout << '>';
          break;
        default:
          break;

      }
    }
    cout << endl;
  }

}

void Algernon::storeMazeState() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      previousMaze[i][j] = maze[i][j];
    }
  }


}

bool Algernon::isDirOrCheese(Thing thing) {
  switch (thing) {
    case UP:
      return true;
      break;
    case DOWN:
      return true;
      break;
    case LEFT:
      return true;
      break;
    case RIGHT:
      return true;
      break;
    case CHEESE:
      return true;
      break;
    default:
      return false;
      break;
  }
}

Thing Algernon::updateLocation(int row, int col) {

  if (previousMaze[row][col] == SPACE || previousMaze[row][col] == START) {
    if (row > 0 && col > 0 && row < ROWS - 1 && col < COLS - 1) {
      if (isDirOrCheese(previousMaze[row - 1][col])) {
        return UP;
      } else if (isDirOrCheese(previousMaze[row + 1][col])) {
        return DOWN;
      } else if (isDirOrCheese(previousMaze[row][col - 1])) {
        return LEFT;
      } else if (isDirOrCheese(previousMaze[row][col + 1])) {
        return RIGHT;
      } else {
        return previousMaze[row][col];
      }
    } else if (row == 0) {
      if (col == 0) {
        if (isDirOrCheese(previousMaze[row + 1][col])) {
          return DOWN;
        } else if (isDirOrCheese(previousMaze[row][col + 1])) {
          return RIGHT;
        } else {
          return previousMaze[row][col];
        }
      } else {
        if (isDirOrCheese(previousMaze[row + 1][col])) {
          return DOWN;
        } else if (isDirOrCheese(previousMaze[row][col - 1])) {
          return LEFT;
        } else if (isDirOrCheese(previousMaze[row][col + 1])) {
          return RIGHT;
        } else {
          return previousMaze[row][col];
        }
      }
    } else if (row == ROWS - 1) {
      if (col == COLS - 1) {
        if (isDirOrCheese(previousMaze[row - 1][col])) {
          return UP;
        } else if (isDirOrCheese(previousMaze[row][col - 1])) {
          return RIGHT;
        } else {
          return previousMaze[row][col];
        }
      } else {
        if (isDirOrCheese(previousMaze[row - 1][col])) {
          return DOWN;
        } else if (isDirOrCheese(previousMaze[row][col - 1])) {
          return LEFT;
        } else if (isDirOrCheese(previousMaze[row][col + 1])) {
          return RIGHT;
        } else {
          return previousMaze[row][col];
        }
      }
    }
  } else {
    return previousMaze[row][col];
  }
}

void Algernon::dropFlowers() {
  int row = startRow, col = startColumn;
  while (row != cheeseRow || col != cheeseColumn) {
    if (maze[row][col] == UP) {
      maze[row][col] = FLOWER;
      row -= 1;
    } else if (maze[row][col] == DOWN) {
      maze[row][col] = FLOWER;
      row += 1;
    } else if (maze[row][col] == LEFT) {
      maze[row][col] = FLOWER;
      col -= 1;
    } else if (maze[row][col] == RIGHT) {
      maze[row][col] = FLOWER;
      col += 1;
    }
    updateDisplay();
  }

}

void Algernon::clearDirections() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (maze[i][j] == UP || maze[i][j] == DOWN || maze[i][j] == LEFT || maze[i][j] == RIGHT) {
        maze[i][j] = SPACE;

      }
    }
  }

}