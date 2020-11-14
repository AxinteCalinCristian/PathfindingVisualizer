#ifndef BEFS_H
#define BEFS_H

#include "../GUI/DisplayMatrix.hpp"
#include <cstring>
#include <queue>
#include <chrono>
#define pii std::pair<std::pair<int,int>,int>
class Compare
{
  public:
  bool operator() (pii a, pii b)
  {
      return a.second>b.second;
  }
};
class BeFS{
private:
  int rowNum[4] = {-1, 0, 0, 1}, colNum[4] = {0, -1, 1, 0};
  Matrix* matrix;
  bool* running;
  inline bool isValid(int row, int col,int ROW, int COL){ return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL); }
  void BeFSAlgo(std::vector<std::vector<int>>* matr, sf::Vector2i src, sf::Vector2i dest)
  {
    int len = -1;
    std::vector<std::vector<int>>& mat = *(matr);
    int ROW = mat.size(), COL = mat[0].size();
    std::vector<std::vector<int>> p(ROW, std::vector<int>(COL));
    int c=0;
    for(int i=0;i<ROW;i++)
      for(int j=0;j<COL;j++)
      {
        if(mat[i][j]==CELL_IDLE || mat[i][j]==CELL_SRC || mat[i][j]==CELL_DEST || mat[i][j]==CELL_WEIGHT)
          p[i][j]=c;
        else p[i][j]=mat[i][j];
        c++;
      }
    std::vector<int> pred(ROW*COL,-1);
    bool vis[ROW][COL];
    memset(vis, false, sizeof vis);
    vis[src.x][src.y] = true;
    std::priority_queue<pii, std::vector<pii>, Compare> q;
    q.push({{src.x,src.y},0});
    bool found = false;
    auto start = std::chrono::system_clock::now();
    while (!q.empty() && !found)
    {
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        if(elapsed_seconds.count() > 0.005f)
        {
          start = end;
          std::pair<std::pair<int,int>,int> curr = q.top();
          std::pair<int,int> pt = curr.first;
          mat[pt.first][pt.second] = CELL_VISITED;
          int cost = curr.second;
          q.pop();

          for (int i = 0; i < 4; i++)
          {
              int row = pt.first + rowNum[i];
              int col = pt.second + colNum[i];
              if (isValid(row, col, ROW, COL) && mat[row][col]!=CELL_SRC && mat[row][col]!=CELL_WALL  && !vis[row][col])
              {
                  vis[row][col] = true;
                  pred[p[row][col]] = p[pt.first][pt.second];
                  std::pair<std::pair<int,int>,int> adj = {{row, col},cost + mat[row][col]};
                  q.push(adj);
                  if (row == dest.x && col == dest.y)
                    len = curr.second, found=true;
              }
          }
      }
    }
    std::vector<std::pair<int,int>> path;
    int d=p[dest.x][dest.y];
    while(pred[d]!=-1)
      path.push_back({d/COL,d-d/COL*COL}),
      d=pred[d];
    int i = path.size()-1;
    start = std::chrono::system_clock::now();
    while(i>0)
    {
      auto end = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_seconds = end-start;
      if(elapsed_seconds.count() > 0.005f)
      {
        start = end;
        mat[path[i].first][path[i].second]=CELL_PATH;
        i--;
      }
    }
  }
public:
  BeFS(Matrix *& matrix, bool *& running)
  {
    this->matrix = matrix;
    this->running = running;
  }
  void start()
  {
    *running = true;
    std::cout<<"staredBeFS\n";
    sf::Vector2i src = this->matrix->getSource(), dest = this->matrix->getDest();
    BeFSAlgo(this->matrix->getMatrix(),src,dest);
    *running = false;
  }
};

#endif
