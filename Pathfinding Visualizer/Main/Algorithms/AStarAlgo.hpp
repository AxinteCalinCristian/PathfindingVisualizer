#ifndef ASTAR_H
#define ASTAR_H

#include "../GUI/DisplayMatrix.hpp"
#include <cstring>
#include <queue>
#include <chrono>
#include <stack>
#include <set>
#include <cfloat>
struct cell
{
    int parent_i, parent_j;
    double f, g, h;
};
class AStar{
  int rowNum[4] = {-1, 0, 0, 1}, colNum[4] = {0, -1, 1, 0};
  Matrix* matrix;
  bool* running;
  inline bool isValid(int row, int col, int ROW, int COL) { return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL); }
  inline bool isUnBlocked(std::vector<std::vector<int>>& grid, int row, int col)
  {
      if (grid[row][col] == CELL_IDLE || grid[row][col] == CELL_DEST || grid[row][col] == CELL_WEIGHT)
          return true;
      return false;
  }
  inline bool isDestination(int row, int col, std::pair<int,int> dest)
  {
      if (row == dest.first && col == dest.second)
          return true;
      else
          return false;
  }
  double manhattan(int row, int col, std::pair<int,int> dest)
  {
      return abs(row-dest.first + col-dest.second);
  }
  void tracePath(std::vector<std::vector<cell>>& cellDetails, std::pair<int,int> dest, std::vector<std::vector<int>>& grid)
  {
      int row = dest.first;
      int col = dest.second;
      std::stack<std::pair<int,int>> Path;
      while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col ))
      {
          Path.push (std::make_pair (row, col));
          row = cellDetails[row][col].parent_i;
          col = cellDetails[row][col].parent_j;
      }
      Path.push (std::make_pair (row, col));
      auto start = std::chrono::system_clock::now();
      while (!Path.empty())
      {
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        if(elapsed_seconds.count() > 0.005f)
        {
          start = end;
          std::pair<int,int> p = Path.top();
          grid[p.first][p.second] = CELL_PATH;
          Path.pop();
        }
      }
      return;
  }
  void aStarSearch(std::vector<std::vector<int>>* matr, std::pair<int,int> src, std::pair<int,int> dest)
  {
      std::vector<std::vector<int>>& grid = *(matr);
      int ROW = grid.size(), COL = grid[0].size();
      bool closedList[ROW][COL];
      memset(closedList, false, sizeof (closedList));
      std::vector<std::vector<cell>> cellDetails(ROW,std::vector<cell>(COL));
      int i, j;
      for (i=0; i<ROW; i++)
      {
          for (j=0; j<COL; j++)
          {
              cellDetails[i][j].f = FLT_MAX;
              cellDetails[i][j].g = FLT_MAX;
              cellDetails[i][j].h = FLT_MAX;
              cellDetails[i][j].parent_i = -1;
              cellDetails[i][j].parent_j = -1;
          }
      }
      i = src.first, j = src.second;
      cellDetails[i][j].f = 0.0;
      cellDetails[i][j].g = 0.0;
      cellDetails[i][j].h = 0.0;
      cellDetails[i][j].parent_i = i;
      cellDetails[i][j].parent_j = j;
      std::set<std::pair<double,std::pair<int,int>>> openList;
      openList.insert(std::make_pair (0.0, std::make_pair (i, j)));
      bool foundDest = false;
      auto start = std::chrono::system_clock::now();
      while (!openList.empty())
      {
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        if(elapsed_seconds.count() > 0.005f){
          start = end;
          std::pair<double,std::pair<int,int>> p = *openList.begin();
          openList.erase(openList.begin());
          i = p.second.first;
          j = p.second.second;
          closedList[i][j] = true;
          double gNew, hNew, fNew;
          grid[i][j]=CELL_VISITED;
          //----------- 1st Successor (North) ------------
          if (isValid(i-1, j, ROW, COL))
          {
              if (isDestination(i-1, j, dest) == true)
              {
                  cellDetails[i-1][j].parent_i = i;
                  cellDetails[i-1][j].parent_j = j;
                  std::cout<<"destReached\n";
                  tracePath (cellDetails, dest, grid);
                  foundDest = true;
                  return;
              }
              else if (closedList[i-1][j] == false && isUnBlocked(grid, i-1, j) == true)
              {
                  gNew = cellDetails[i][j].g + 1.0;
                  hNew = manhattan (i-1, j, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i-1][j].f == FLT_MAX || cellDetails[i-1][j].f > fNew)
                  {
                      openList.insert( std::make_pair(fNew, std::make_pair(i-1, j)));
                      cellDetails[i-1][j].f = fNew;
                      cellDetails[i-1][j].g = gNew;
                      cellDetails[i-1][j].h = hNew;
                      cellDetails[i-1][j].parent_i = i;
                      cellDetails[i-1][j].parent_j = j;
                  }
              }
          }

          //----------- 2nd Successor (South) ------------
          if (isValid(i+1, j, ROW, COL))
          {
              if (isDestination(i+1, j, dest) == true)
              {
                  cellDetails[i+1][j].parent_i = i;
                  cellDetails[i+1][j].parent_j = j;
                  std::cout<<"destReached\n";
                  tracePath (cellDetails, dest, grid);
                  foundDest = true;
                  return;
              }
              else if (closedList[i+1][j] == false && isUnBlocked(grid, i+1, j) == true)
              {
                  gNew = cellDetails[i][j].g + 1.0;
                  hNew = manhattan(i+1, j, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i+1][j].f == FLT_MAX || cellDetails[i+1][j].f > fNew)
                  {
                      openList.insert( std::make_pair (fNew, std::make_pair (i+1, j)));
                      cellDetails[i+1][j].f = fNew;
                      cellDetails[i+1][j].g = gNew;
                      cellDetails[i+1][j].h = hNew;
                      cellDetails[i+1][j].parent_i = i;
                      cellDetails[i+1][j].parent_j = j;
                  }
              }
          }

          //----------- 3rd Successor (East) ------------
          if (isValid (i, j+1, ROW, COL) == true)
          {
              if (isDestination(i, j+1, dest) == true)
              {
                  cellDetails[i][j+1].parent_i = i;
                  cellDetails[i][j+1].parent_j = j;
                  std::cout<<"destReached\n";
                  tracePath (cellDetails, dest, grid);
                  foundDest = true;
                  return;
              }
              else if (closedList[i][j+1] == false && isUnBlocked (grid, i, j+1) == true)
              {
                  gNew = cellDetails[i][j].g + 1.0;
                  hNew = manhattan (i, j+1, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i][j+1].f == FLT_MAX || cellDetails[i][j+1].f > fNew)
                  {
                      openList.insert(std::make_pair(fNew, std::make_pair (i, j+1)));
                      cellDetails[i][j+1].f = fNew;
                      cellDetails[i][j+1].g = gNew;
                      cellDetails[i][j+1].h = hNew;
                      cellDetails[i][j+1].parent_i = i;
                      cellDetails[i][j+1].parent_j = j;
                  }
              }
          }

          //----------- 4th Successor (West) ------------
          if (isValid(i, j-1, ROW, COL) == true)
          {
              if (isDestination(i, j-1, dest) == true)
              {
                  cellDetails[i][j-1].parent_i = i;
                  cellDetails[i][j-1].parent_j = j;
                  std::cout<<"destReached\n";
                  tracePath (cellDetails, dest, grid);
                  foundDest = true;
                  return;
              }
              else if (closedList[i][j-1] == false && isUnBlocked(grid, i, j-1) == true)
              {
                  gNew = cellDetails[i][j].g + 1.0;
                  hNew = manhattan(i, j-1, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i][j-1].f == FLT_MAX || cellDetails[i][j-1].f > fNew)
                  {
                      openList.insert( std::make_pair (fNew, std::make_pair (i, j-1)));
                      cellDetails[i][j-1].f = fNew;
                      cellDetails[i][j-1].g = gNew;
                      cellDetails[i][j-1].h = hNew;
                      cellDetails[i][j-1].parent_i = i;
                      cellDetails[i][j-1].parent_j = j;
                  }
              }
          }
        }
      }
      if (foundDest == false)
          std::cout<<"noPathFound\n";
      return;
  }
public:
  AStar(Matrix *& matrix, bool *& running)
  {
    this->matrix = matrix;
    this->running = running;
  }
  void start()
  {
    *running = true;
    std::cout<<"staredAstar\n";
    sf::Vector2i src = this->matrix->getSource(), dest = this->matrix->getDest();
    std::pair<int,int> srci = {src.x, src.y}, desti = {dest.x, dest.y};
    //std::cout<<src.x<<'\t'<<src.y<<'\n'<<dest.x<<'\t'<<dest.y<<'\n';
    aStarSearch(this->matrix->getMatrix(),srci,desti);
    *running = false;
  }
};

#endif
