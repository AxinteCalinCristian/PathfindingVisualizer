#ifndef WINMAN_H
#define WINMAN_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GUI.hpp"
#include "DisplayMatrix.hpp"
#include "../Algorithms/AlgoManager.hpp"
#include "InfoTab.hpp"
#define FPS 60
#define min_W 800
#define min_H 600

class Window{

private:
  int window_H;
  int window_W;
  int screen_H;
  int screen_W;
  std::string id;
  bool fullScreen;
  GUI gui;
  bool LMClick;
  Matrix* matrix;
  InfoTab* infoTab;
  bool shift=false,ctrl=false;
  AlgoManager* algoMan;
public:
  Window(int window_W,int window_H,std::string id,GUI& gui): window_W(window_W), window_H(window_H), id(id), fullScreen(false), gui(gui)
  {
    infoTab = new InfoTab(gui.font);
    matrix = new Matrix(3,3);
    algoMan = new AlgoManager(matrix);
    LMClick = false;
    screen_H = sf::VideoMode::getDesktopMode().height;
    screen_W = sf::VideoMode::getDesktopMode().width;
  }
  ~Window()
  {
    delete matrix;
    delete algoMan;
  }
  void run(){

    //Initialize window
    sf::RenderWindow window(sf::VideoMode(window_W,window_H),id,sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(FPS);
    int c=0;
    //Main loop
    while(window.isOpen()){

      //Input Manager
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
      {
        if(!fullScreen)
        {
          window.create(sf::VideoMode::getFullscreenModes()[0], id, sf::Style::Fullscreen);
          fullScreen = true;
        }else
        {
          window.create(sf::VideoMode(window_W,window_H),id,sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
          fullScreen = false;
        }
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
      //Event Handler
      sf::Event ev;
      while(window.pollEvent(ev))
      {
        if (ev.type == sf::Event::Closed)
            window.close();
        else if(ev.type == sf::Event::Resized)
        {
          if(ev.size.width < screen_W || ev.size.height < screen_H)
          {
              window_H = ev.size.height;
              window_W = ev.size.width;
              if(window_H>screen_H) window_H = screen_H;
              if(window_W>screen_W) window_W = screen_W;
              if(window_W<min_W) window_W = min_W;
              if(window_H<min_H) window_H = min_H;
              sf::FloatRect visibleArea(0, 0, window_W, window_H);
              window.setSize(sf::Vector2u(window_W,window_H));
              window.setView(sf::View(visibleArea));
          }
        }
        if(ev.mouseButton.button == sf::Mouse::Left)
        {
          if(ev.type == sf::Event::MouseButtonPressed)
          {
            LMClick = true,c=0;
            if(shift)
              matrix->settingOrigin = true;
            else if(ctrl)
              matrix->settingDest = true;
          }
          gui.LMClick = LMClick;
        }
        if(ev.mouseButton.button == sf::Mouse::Right && ev.type == sf::Event::MouseButtonPressed){
          if(shift && gui.weightedAlgo)
            matrix->settingWeights = true,
            matrix->settingWalls = false;
          else
            matrix->settingWalls = true,
            matrix->settingWeights = false;
        }else if(ev.mouseButton.button == sf::Mouse::Right && ev.type == sf::Event::MouseButtonReleased){
          matrix->settingWalls = false,
          matrix->settingWeights = false;
        }
        if(ev.type == sf::Event::TextEntered)
        {
          gui.inputIntoBox(ev);
        }
        if(ev.type==sf::Event::KeyPressed)
        {
          if (ev.key.code == sf::Keyboard::LShift)
            shift = true;
          if (ev.key.code == sf::Keyboard::LControl)
            ctrl = true;
        }else if(sf::Event::KeyReleased)
        {
          if (ev.key.code == sf::Keyboard::LShift)
            shift = false;
          if (ev.key.code == sf::Keyboard::LControl)
            ctrl = false;
        }
      }
      if(LMClick)
      {
        if(c<5) c++;
        else{
           LMClick = false;
           gui.LMClick = LMClick;
        }
      }

      //Matrix management
      if(matrix->getSize().x!=gui.matrix_W || matrix->getSize().y!=gui.matrix_H)
      {
        this->matrix->setSize(gui.matrix_W,gui.matrix_H);
      }
      if(gui.startAlgo)
      {
        this->algoMan->startAlgorithm(*(this->matrix),gui.selectedAlgorithm);
        gui.startAlgo = false;
      }
      if(*(this->algoMan->running) == false)
        gui.running = false;
      if(gui.resetMatrix)
        this->matrix->resetMat();
      //Window display
      window.clear();
      gui.onGUI(window);
      if(!gui.infoOn)
        matrix->renderMatrix(window);
      else
        infoTab->display(window);
      window.display();
    }
  }
};

#endif
