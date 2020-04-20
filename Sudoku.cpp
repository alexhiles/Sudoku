#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <random>

enum class GameDifficulty
{
  EASY,
  MEDIUM,
  HARD,
};

void printBoard(std::vector<std::vector<int>> array)
{
std::cout << '\n';
  std::cout << "--------------------";
  std::cout << '\n';
  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      std::cout << array[row][col] << " ";
      if (col == 2 or col == 5 or col == 8)
      {
        std::cout << "|";
      }
    }
    std::cout << '\n';
    if (row == 2 or row == 5 or row == 8)
    {
      std::cout << "------|------|------";
      std::cout << '\n';
    }
  }
  std::cout << '\n';
};

void printRow(std::vector<std::vector<int> > array, int row_number)
{
  for (int i = 0; i < 9; i++)
  {
    std::cout << array[row_number][i] << " ";
  }
  std::cout << '\n';
}

void printCol(std::vector<std::vector<int> > array, int col_number)
{
  for (int i = 0; i < 9; i++)
  {
    std::cout << array[i][col_number] << " ";
  }
  std::cout << '\n';
}

void printRules()
{
  std::cout << "WELCOME TO SUDOKU!" << '\n';
  std::cout << "Here's how the game works... " << '\n' << '\n' << '\n';
  std::cout << "(1) Each row, column, and nonet can contain each number (1 to 9 only) exactly once. " << '\n';
  std::cout << "(2) The sum of all numbers in any nonet, row, or column must match the small number printed" << '\n';
  std::cout << "    in its corner. For traditional Sudoku puzzles featuring the numbers 1 to 9, this sum" << '\n';
  std::cout << "    is equal to 45." << '\n';
};

std::vector<int> getRow(std::vector<std::vector<int> > array, int row_number)
{
  std::vector<int> row;

  row = array[row_number];

  return row;
};

std::vector<int> getCol(std::vector<std::vector<int> > array, int col_number)
{
  std::vector<int> col(9);

  for (int i = 0; i < 9; i++)
  {
    col[i] = array[i][col_number];
  };


  return col;
};

int getSum(std::vector<int> array)
{
  int sum{0};

  for (int i = 0; i < 9; i++)
  {
    sum += array[i];
  }

  return sum;
}

bool findInteger(std::vector<int> array, int findme)
{
  for (int i = 0; i < 9; i++)
  {
    if (array[i] == findme)
    {
      return true;
    }
  };
  return false;
};

bool checkWin(std::vector<std::vector<int> > array)
{
  for (int i = 0; i < 9; i++)
  {
    if (getSum(getRow(array, i)) != 45)
    {
      return false;
    }
    else if (getSum(getCol(array, i)) != 45)
    {
      return false;
    }
  };
  return true;
};

int play(std::vector<std::vector<int> > array)
{
  while (1)
  {
    int row;
    int col;
    int user_input;
    printBoard(array);

    std::cout << "Enter the row you want to alter (0 <= row <= 8): ";

    while (!(std::cin  >> row) or row >= 9)
    {
      std::cout << "Error! Please enter an integer between (0 and 8): ";

      std::cin.clear();
      std::cin.ignore(123, '\n');
    }

    std::cout << "Enter the column you want to alter (0 <= column <= 8): ";

    while (!(std::cin  >> col) or col >= 9)
    {
      std::cout << "Error! Please enter an integer between (0 and 8): ";
    }

    std::cout << "What number do you want to place at this location?";
    while (!(std::cin  >> user_input) or row >= 9)
    {
      std::cout << "Error! Please enter an integer between (0 and 8): ";
    }

    std::vector<int> row_vec = getRow(array, row);
    std::vector<int> col_vec = getCol(array, col);

    if (findInteger(row_vec, user_input) or findInteger(col_vec, user_input))
    {
      std::cout << "Cannot place there, try again!" << '\n';
    }
    else
    {
    array[row][col] = user_input;
    }

   bool Win{checkWin(array)};

   if (Win)
   {
     printBoard(array);
     std::cout << "You have solved the Sudoku puzzle!" << '\n';
     exit(0);
   }
   else
   {
     continue;
   }


  };

};

GameDifficulty getDifficulty(int d)
{
  GameDifficulty diff;
  if (d == 1)
  {
    diff = GameDifficulty::EASY;
  }
  else if (d == 2)
  {
    diff = GameDifficulty::MEDIUM;
  }
  else if (d == 3)
  {
    diff = GameDifficulty::HARD;
  }
  return diff;
}


std::vector<int> shiftLeft(std::vector<int> array)
{
  for (int i = 0; i < array.size() - 1;i++)
  {
  int temp     = array[i + 1];
  array[i + 1] = array[i];
  array[i]     = temp;

  };
  return array;
}

std::vector<std::vector<int> > zeroFilling(std::vector<std::vector<int> > array, GameDifficulty Difficulty)
{
  std::vector<int> permIndices = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(permIndices.begin(), permIndices.end(), std::default_random_engine(seed));

  switch (Difficulty)
  {
    case GameDifficulty::EASY:

    for (int i = 0; i < 9; i++)
    {
      std::shuffle(permIndices.begin(), permIndices.end(), std::default_random_engine(seed));
      for (int j = 0; j <= 2; j++)
      {
        array[i][permIndices[j]] = 0;
      }
    }
    return array;
    break;
    case GameDifficulty::MEDIUM:

    for (int i = 0; i < 9; i++)
    {
      std::shuffle(permIndices.begin(), permIndices.end(), std::default_random_engine(seed));
      for (int j = 0; j <= 4; j++)
      {

        array[i][permIndices[j]] = 0;
      }
    }
    return array;
    break;
    case GameDifficulty::HARD:

    for (int i = 0; i < 9; i++)
    {
      std::shuffle(permIndices.begin(), permIndices.end(), std::default_random_engine(seed));
      for (int j = 0; j <= 6; j++)
      {
        array[i][permIndices[j]] = 0;
      }
    }
    return array;
    break;
  }
  return array;
};


std::vector<std::vector<int> > boardGen()
{

  std::vector<std::vector<int> > sudokuGen;
  std::vector<int> poss        = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(poss.begin(), poss.end(), std::default_random_engine(seed));

  std::vector<int> permIndices = {0, 1, 2, 3, 4, 5, 6, 7, 8};

  for (int i = 0; i < 9; i++){
  poss = shiftLeft(poss);
  sudokuGen.push_back(poss);
  }

  std::shuffle(permIndices.begin(), permIndices.end(), std::default_random_engine(seed));
  std::vector<std::vector<int> > Board;

  for (int k = 0; k < 9; k++)
  {
    Board.push_back(sudokuGen[permIndices[k]]);
  }
  return Board;
}

int main()
{
    printRules();
    std::vector<std::vector<int> > sudokuBoard;
    sudokuBoard = boardGen();

    std::cout << "Please enter difficulty: (1 : EASY, 2 : MEDIUM, 3 : HARD)" << '\n';

    int difficulty;
    while (!(std::cin  >> difficulty or difficulty > 3 or difficulty < 0))
    {
      std::cout << "Error! Please enter either 1, 2 or 3: ";

      std::cin.clear();
      std::cin.ignore(123, '\n');
    }

    sudokuBoard = zeroFilling(sudokuBoard, getDifficulty(difficulty));
    play(sudokuBoard);

};
