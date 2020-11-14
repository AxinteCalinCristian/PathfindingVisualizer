#ifndef ALGOMAN_H
#define ALGOMAN_H

#include "BeFSAlgo.hpp"
#include "BFSAlgo.hpp"
#include "DFSAlgo.hpp"
#include "AStarAlgo.hpp"
#include "DijkstraAlgo.hpp"
#include "../GUI/DisplayMatrix.hpp"
#include <SFML/System.hpp>
class AlgoManager{

private:
  int currActive=-1;
  BeFS* befs;
  BFS* bfs;
  DFS* dfs;
  AStar* astar;
  Dijkstra* dijkstra;
  Matrix* matrix;
public:
  bool* running;

  AlgoManager(Matrix *& matrix)
  {
    this->running = new bool;
    *(this->running) = false;
    this->matrix = matrix;
    this->befs = new BeFS(this->matrix,running);
    this->bfs = new BFS(this->matrix,running);
    this->dfs = new DFS(this->matrix,running);
    this->astar = new AStar(this->matrix,running);
    this->dijkstra = new Dijkstra(this->matrix,running);
  }
  ~AlgoManager()
  {
    delete befs;
    delete bfs;
    delete dfs;
    delete astar;
    delete dijkstra;
  }
  void startAlgorithm(Matrix& matrix, int currActive)
  {
    if(matrix.getSource().x==-1 || matrix.getSource().y==-1 || matrix.getDest().x==-1 || matrix.getDest().y==-1)
    {
      return;
    }
    if(!(*(this->running)))
    {
      this->currActive = currActive;
      *running = true;
      if(currActive == 2)
      {
        static sf::Thread algo(BeFS::start,befs);
        algo.launch();
      }
      else if(currActive == 3)
      {
        static sf::Thread algo(BFS::start,bfs);
        algo.launch();
      }
      else if(currActive == 4)
      {
        static sf::Thread algo(DFS::start,dfs);
        algo.launch();
      }
      else if(currActive == 5)
      {
        static sf::Thread algo(AStar::start,astar);
        algo.launch();
      }
      else if(currActive == 6)
      {
        static sf::Thread algo(Dijkstra::start,dijkstra);
        algo.launch();
      }
    }
  }
};

#endif
