#ifndef GUI_H
#define GUI_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "TextBox.hpp"

#define darkBlue 38, 70, 83, 255
#define cyan 42, 157, 143, 255
#define mustard 233, 196, 106, 255
#define peach 244, 162, 97, 255
#define out_peach 244, 162, 97, 100
#define redish 231, 111, 81, 255
#define light_teal 154, 211, 188, 255
#define yellowish 243, 234, 194, 255
#define warm_orange 245, 180, 97, 255
#define out_warm_orange 245, 180, 97, 100
#define warm_red 236, 82, 75, 255
#define blue_gray 99, 115, 115, 255
#define cold_red 128, 15, 27, 255
#define out_cold_red 128, 15, 27, 100
#define avg_red 209, 31, 55, 255
#define light_red 238, 70, 64, 255
#define out_light_red 238, 70, 64, 100
#define dark_purple 28, 10, 27, 255

class GUI{

private:
  std::vector<Button*> buttons;
  std::vector<TextBox*> tboxes;
  std::vector<sf::Text> texts;
  sf::Color bgColor;
  sf::Color menuColor;
  TextBox* currActive;
  bool selectedAlgo = false;
  bool startPressed = false;
  int currAlgo=-1;
  int prevAlgo=-1;
  inline double maxD(double a,double b){ return (a>b?a:b); }
public:
  int matrix_W=3;
  int matrix_H=3;
  bool LMClick;
  bool running = false;
  bool startAlgo = false;
  int selectedAlgorithm=-1;
  bool resetMatrix = false;
  bool weightedAlgo = false;
  bool infoOn = false;
  sf::Font font;
  GUI(sf::Font font,sf::Color bgColor,sf::Color menuColor,int win_W, int win_H): font(font), bgColor(bgColor), menuColor(menuColor)
  {
    //Width
    TextBox* textBox = new TextBox(sf::Color(yellowish),20,sf::Color(dark_purple),false,win_W/16.,win_W/16./2.,3,sf::Color(out_warm_orange),"3");
    textBox->setFont(this->font);
    textBox->setPosition(sf::Vector2f(3*win_W/32.,2*win_H/14.));
    tboxes.push_back(textBox);
    currActive = textBox;
    LMClick = false;

    sf::Text txt;
    txt.setFont(this->font);
    txt.setCharacterSize(24);
    txt.setFillColor(sf::Color(peach));
    txt.setPosition(sf::Vector2f(win_W/32.,2*win_H/14.));
    txt.setString("Width:");
    texts.push_back(txt);
    //Height
    textBox = new TextBox(sf::Color(yellowish),20,sf::Color(dark_purple),false,win_W/16.,win_W/16./2.,3,sf::Color(out_warm_orange),"3");
    textBox->setFont(this->font);
    textBox->setPosition(sf::Vector2f(3*win_W/32.,0.8*win_H/14.));
    tboxes.push_back(textBox);
    txt.setPosition(sf::Vector2f(win_W/32.,0.8*win_H/14.));
    txt.setString("Height:");
    texts.push_back(txt);
    //Start btn
    float x=win_W/32.,y=12*win_H/14.;
    float width=3.*win_W/16.,height=win_H/14.;
    Button* b = new Button(x,y,width,height,this->font,"Start",35,sf::Color(peach), sf::Color(warm_red), sf::Color::Red, sf::Color(out_peach), sf::Color(out_cold_red),4,sf::Color(dark_purple));
    buttons.push_back(b);

    //Info
    x=win_W/32.; y=12*win_H/14.-win_H/6.; width = win_W/16., height = win_W/16.;
    b = new Button(x,y,width,height,this->font,"Info",24,sf::Color(warm_orange), sf::Color(light_red), sf::Color(avg_red),sf::Color(out_warm_orange), sf::Color(out_light_red),3,sf::Color(yellowish), true);
    buttons.push_back(b);

    //BeFS
    x=5*win_W/32.; y=12*win_H/14.-win_H/6.; width = win_W/16., height = win_W/16.;
    b = new Button(x,y,width,height,this->font,"  Best\n  First\nSearch",20,sf::Color(warm_orange), sf::Color(light_red), sf::Color(avg_red),sf::Color(out_warm_orange),sf::Color(out_light_red),3,sf::Color(yellowish),true);
    buttons.push_back(b);

    //BFS
    x=win_W/32.; y=12*win_H/14.-2*win_H/6.; width = win_W/16., height = win_W/16.;
    b = new Button(x,y,width,height,this->font,"BFS",28,sf::Color(warm_orange), sf::Color(light_red), sf::Color(avg_red),sf::Color(out_warm_orange), sf::Color(out_light_red),3,sf::Color(yellowish),true);
    buttons.push_back(b);

    //DFS
    x=5*win_W/32.; y=12*win_H/14.-2*win_H/6.; width = win_W/16., height = win_W/16.;
    b = new Button(x,y,width,height,this->font,"DFS",28,sf::Color(warm_orange), sf::Color(light_red), sf::Color(avg_red),sf::Color(out_warm_orange), sf::Color(out_light_red),3,sf::Color(yellowish),true);
    buttons.push_back(b);

    //A*
    x=win_W/32.; y=12*win_H/14.-3*win_H/6.; width = win_W/16., height = win_W/16.;
    b = new Button(x,y,width,height,this->font,"A*",28,sf::Color(warm_orange), sf::Color(light_red), sf::Color(avg_red),sf::Color(out_warm_orange), sf::Color(out_light_red),3,sf::Color(yellowish),true);
    buttons.push_back(b);

    //Dijkstra
    x=5*win_W/32.; y=12*win_H/14.-3*win_H/6.; width = win_W/16., height = win_W/16.;
    b = new Button(x,y,width,height,this->font,"Dijkstra",22,sf::Color(warm_orange), sf::Color(light_red), sf::Color(avg_red),sf::Color(out_warm_orange), sf::Color(out_light_red),3,sf::Color(yellowish),true);
    buttons.push_back(b);

    //Set dimensions
    x=win_W/32.,y=3.2*win_H/14.,width=3.*win_W/16.,height=win_H/14.;
    b = new Button(x,y,width,height,this->font,"Set dimensions",26,sf::Color(peach), sf::Color(warm_red), sf::Color::Red,sf::Color(out_peach), sf::Color(out_cold_red),4,sf::Color(dark_purple));
    buttons.push_back(b);
  }
  ~GUI()
  {
    for(auto b:buttons) delete b;
    buttons.clear();
    for(auto t:tboxes) delete t;
    tboxes.clear();
    texts.clear();
    delete currActive;
  }

  void drawBG(sf::RenderWindow& window){
    //Menu
    sf::RectangleShape menu;
    menu.setPosition(sf::Vector2f(0,0));
    menu.setSize(sf::Vector2f(window.getSize().x/4,window.getSize().y));
    menu.setFillColor(menuColor);
    window.draw(menu);
    //BG
    sf::RectangleShape bg;
    bg.setPosition(sf::Vector2f(window.getSize().x/4,0));
    bg.setSize(sf::Vector2f(3*window.getSize().x/4,window.getSize().y));
    bg.setFillColor(bgColor);
    window.draw(bg);
  }
  inline int64_t max(int64_t a,int64_t b){return (a>=b) ? a : b;}
  inline int64_t min(int64_t a,int64_t b){return (a<b) ? a : b;}
  inline std::string toString(int64_t a)
  {
    std::string s = "";
    while(a) s+=(a%10+'0'),a/=10;
    reverse(s.begin(),s.end());
    return s;
  }
  void drawButtons(sf::RenderWindow& window){
    int currActive=-1; selectedAlgo = false; startAlgo = false; resetMatrix = false;
    //Start
    float x=window.getSize().x/32.,y=12.*window.getSize().y/14., width=3.*window.getSize().x/16.,height=window.getSize().y/14.;
    buttons[0]->render(window,x,y,width,height);
    buttons[0]->update(sf::Mouse::getPosition(window),this->LMClick);
    //Info
    x=window.getSize().x/32.,y=12*window.getSize().y/14.-window.getSize().y/6., width=height=maxD(window.getSize().y/16.,window.getSize().x/16.);
    buttons[1]->render(window,x,y,width,height);
    buttons[1]->update(sf::Mouse::getPosition(window),this->LMClick);
    if(buttons[1]->toggled && !running)
    {
      for(int i = 1; i<buttons.size(); i++)
        if(i!=1)
        {
          currActive = 1;
          buttons[i]->toggled = false;
        }
    }
    //Best First Search
    x=5*window.getSize().x/32.,y=12*window.getSize().y/14.-window.getSize().y/6., width=height=maxD(window.getSize().y/16.,window.getSize().x/16.);
    buttons[2]->render(window,x,y,width,height);
    buttons[2]->update(sf::Mouse::getPosition(window),this->LMClick);
    if(buttons[2]->toggled && !running)
    {
      for(int i = 1; i<buttons.size(); i++)
        if(i!=2)
        {
          currActive = 2;
          buttons[i]->toggled = false;
        }
    }
    //BFS
    x=window.getSize().x/32.,y=12*window.getSize().y/14.-2*window.getSize().y/6., width=height=maxD(window.getSize().y/16.,window.getSize().x/16.);
    buttons[3]->render(window,x,y,width,height);
    buttons[3]->update(sf::Mouse::getPosition(window),this->LMClick);
    if(buttons[3]->toggled && !running)
    {
      for(int i = 1; i<buttons.size(); i++)
        if(i!=3)
        {
          currActive = 3;
          buttons[i]->toggled = false;
        }
    }
    //DFS
    x=5*window.getSize().x/32.,y=12*window.getSize().y/14.-2*window.getSize().y/6., width=height=maxD(window.getSize().y/16.,window.getSize().x/16.);
    buttons[4]->render(window,x,y,width,height);
    buttons[4]->update(sf::Mouse::getPosition(window),this->LMClick);
    if(buttons[4]->toggled && !running)
    {
      for(int i = 1; i<buttons.size(); i++)
        if(i!=4)
        {
          currActive = 4;
          buttons[i]->toggled = false;
        }
    }
    //A*
    x=window.getSize().x/32.,y=12*window.getSize().y/14.-3*window.getSize().y/6., width=height=maxD(window.getSize().y/16.,window.getSize().x/16.);
    buttons[5]->render(window,x,y,width,height);
    buttons[5]->update(sf::Mouse::getPosition(window),this->LMClick);
    if(buttons[5]->toggled && !running)
    {
      for(int i = 1; i<buttons.size(); i++)
        if(i!=5)
        {
          currActive = 5;
          buttons[i]->toggled = false;
        }
    }
    //Dijkstra
    x=5*window.getSize().x/32.,y=12*window.getSize().y/14.-3*window.getSize().y/6., width=height=maxD(window.getSize().y/16.,window.getSize().x/16.);
    buttons[6]->render(window,x,y,width,height);
    buttons[6]->update(sf::Mouse::getPosition(window),this->LMClick);
    if(buttons[6]->toggled && !running)
    {
      for(int i = 1; i<buttons.size(); i++)
        if(i!=6)
        {
          currActive = 6;
          buttons[i]->toggled = false;
        }
    }
    //Set dimensions
    x=window.getSize().x/32.,y=3.2*window.getSize().y/14., width=3.*window.getSize().x/16.,height=window.getSize().y/14.;
    buttons[7]->render(window,x,y,width,height);
    buttons[7]->update(sf::Mouse::getPosition(window),this->LMClick);
    if(buttons[7]->isPressed() && !running)
    {
      //Set Dimensions of Matrix
      if(tboxes[0]->getText().length()>0)
      {
        this->matrix_W = min(200,max(std::stoi(tboxes[0]->getText(),nullptr),3));
        tboxes[0]->setString(toString(this->matrix_W));
        resetMatrix = true;
      }
      if(tboxes[1]->getText().length()>0)
      {
        this->matrix_H= min(200,max(std::stoi(tboxes[1]->getText(),nullptr),3));
        tboxes[1]->setString(toString(this->matrix_H));
        resetMatrix = true;
      }
    }
    if(currActive==1)
      this->infoOn = true;
    else
      this->infoOn = false;

    if(currActive!=-1 && currActive != 1) selectedAlgo = true;
    if(currActive == 3 || currActive == 4)
      weightedAlgo = false;
    else
      weightedAlgo = true;
    if(selectedAlgo)
    {
      prevAlgo = currAlgo;
      currAlgo = currActive;
      if(prevAlgo != currAlgo && !running)
        resetMatrix = true;
    }
    if(buttons[0]->isPressed() && !startPressed)
    {
      if(selectedAlgo == false)
        std::cout<<"noAlgoSelected\n";
      else
      {
        startPressed = true;
        if(!running)
          this->selectedAlgorithm=currActive,startAlgo=true; running = true, buttons[currActive]->toggled = false;
      }
    }
    if(!buttons[0]->isPressed()) startPressed = false;
  }

  void inputIntoBox(sf::Event& input)
  {
    currActive->typedInto(input);
  }

  void drawInput(sf::RenderWindow& window)
  {
    //Width
    tboxes[0]->render(window,3*window.getSize().x/32.,2*window.getSize().y/14.,window.getSize().x/16.,window.getSize().x/16./2.);
    tboxes[0]->update(sf::Mouse::getPosition(window),this->LMClick);
    if(tboxes[0]->isSelected)
      tboxes[1]->isSelected = false,
      currActive = tboxes[0];

    //Height
    tboxes[1]->render(window,3*window.getSize().x/32.,0.8*window.getSize().y/14.,window.getSize().x/16.,window.getSize().x/16./2.);
    tboxes[1]->update(sf::Mouse::getPosition(window),this->LMClick);
    if(tboxes[1]->isSelected)
      tboxes[0]->isSelected = false,
      currActive = tboxes[1];
    if(!tboxes[0]->isSelected) tboxes[0]->setString(toString(min(200,max(std::stoi(tboxes[0]->getText(),nullptr),3))));
    if(!tboxes[1]->isSelected) tboxes[1]->setString(toString(min(200,max(std::stoi(tboxes[1]->getText(),nullptr),3))));
  }
  void drawText(sf::RenderWindow& window)
  {
    sf::FloatRect textRect = texts[0].getLocalBounds();
    texts[0].setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    texts[0].setPosition(sf::Vector2f(1.8*window.getSize().x/32.,2.35*window.getSize().y/14.));
    texts[0].setCharacterSize(tboxes[0]->fontSize*(window.getSize().x>900?1.3:1));
    texts[0].setOutlineThickness(1); texts[0].setOutlineColor(sf::Color::Black);
    textRect = texts[1].getLocalBounds();
    texts[1].setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    texts[1].setPosition(sf::Vector2f(1.8*window.getSize().x/32.,1.15*window.getSize().y/14.));
    texts[1].setCharacterSize(tboxes[1]->fontSize*(window.getSize().x>900?1.3:1));
    texts[1].setOutlineThickness(1); texts[1].setOutlineColor(sf::Color::Black);
    for(auto t:texts) window.draw(t);
  }
  void onGUI(sf::RenderWindow& window)
  {
    drawBG(window);
    drawButtons(window);
    drawInput(window);
    drawText(window);
  }
};

#endif
