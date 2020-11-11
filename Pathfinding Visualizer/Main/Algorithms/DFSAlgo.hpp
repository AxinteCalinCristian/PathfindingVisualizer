#ifndef DFS_H
#define DFS_H

#include "../GUI/DisplayMatrix.hpp"
#include <cstring>
#include <stack>
#include <chrono>

class DFS{
private:
  Matrix* matrix;
  bool* running;
  bool found;
  int rowNum[4] = {-1, 0, 0, 1}, colNum[4] = {0, -1, 1, 0};
  inline bool equal(sf::Vector2i a,sf::Vector2i b){ return a.x == b.x && a.y == b.y; }
  inline bool isValid(int row, int col,int ROW, int COL){ return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL); }
  void DFSAlgo(std::vector<std::vector<int>>& matr, sf::Vector2i src, sf::Vector2i dest, sf::Vector2i curr, std::stack<sf::Vector2i>& st, std::vector<std::vector<int>>& vis)
  {
    sf::sleep(sf::seconds(0.01));
    st.push(curr);
    if(equal(dest,curr))
    {
      found = true;
      return;
    }
    if(!found)
    {
      int ROW = matr.size(), COL = matr[0].size();
      for (int i = 0; i < 4; i++)
      {
          int row = curr.x + rowNum[i];
          int col = curr.y + colNum[i];
          if (isValid(row, col, ROW, COL) && matr[row][col]!=CELL_SRC && matr[row][col]!=CELL_WALL  && !vis[row][col])
          {
              vis[row][col] = true;
              if(!found)
                matr[row][col] = CELL_VISITED,
                DFSAlgo(matr,src,dest,{row,col},st,vis);
          }
      }
    }
  }
  void arrangeDirVec(sf::Vector2i src, sf::Vector2i dest)
  {
    if(src.x<=dest.x)
    {
        if(src.y<=dest.y){
          rowNum[0]=1,colNum[0]=0;
          rowNum[1]=0,colNum[1]=1;
          rowNum[2]=0,colNum[2]=-1;
          rowNum[3]=-1,colNum[3]=0;
        }else{
          rowNum[0]=1,colNum[0]=0;
          rowNum[1]=0,colNum[1]=-1;
          rowNum[2]=0,colNum[2]=1;
          rowNum[3]=-1,colNum[3]=0;
        }
    }else
    {
      if(src.y<=dest.y){
        rowNum[0]=-1,colNum[0]=0;
        rowNum[1]=0,colNum[1]=-1;
        rowNum[2]=0,colNum[2]=1;
        rowNum[3]=1,colNum[3]=0;
      }else{
        rowNum[0]=-1,colNum[0]=0;
        rowNum[1]=0,colNum[1]=1;
        rowNum[2]=0,colNum[2]=-1;
        rowNum[3]=1,colNum[3]=0;
      }
    }
  }
public:
  DFS(Matrix *& matrix, bool *& running)
  {
    this->matrix = matrix;
    this->running = running;
  }
  void start()
  {
    found = false;
    *running = true;
    std::cout<<"staredDFS\n";
    sf::Vector2i src = this->matrix->getSource(), dest = this->matrix->getDest();
    //arrangeDirVec(src,dest);
    std::vector<std::vector<int>>& matr = *(this->matrix->getMatrix());
    int ROW = matr.size(), COL = matr[0].size();
    std::stack<sf::Vector2i> st;
    std::vector<std::vector<int>> vis(ROW, std::vector<int>(COL));
    for(int i=0;i<ROW;i++)
      for(int j=0;j<COL;j++)
        vis[i][j]=0;
    vis[src.x][src.y] = true;
    DFSAlgo(matr,src,dest,src,st,vis);
    if(found)
    {
      std::vector<std::pair<int,int>> v;
      while(!st.empty())
      {
        v.push_back({st.top().x,st.top().y});
        st.pop();
      }
      reverse(v.begin(),v.end());
      std::cout<<v.size()<<'\n';
      for(auto it:v) sf::sleep(sf::seconds(0.01)), matr[it.first][it.second] = CELL_PATH,std::cout<<it.first<<' '<<it.second<<'\n';
    }
    else
      std::cout<<"No path found\n";
    *running = false;
  }
};

#endif
