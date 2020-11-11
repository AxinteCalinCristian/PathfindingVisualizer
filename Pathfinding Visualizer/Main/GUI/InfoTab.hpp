#ifndef INFOTAB_H
#define INFOTAB_H

#define yellowish 243, 234, 194, 255
#define warm_orange 245, 180, 97, 255
#define avg_red 209, 31, 55, 255
#define cyan 42, 157, 143, 255
#define blue_gray 99, 115, 115, 255
#define light_teal 154, 211, 188, 255
#define mustard 233, 196, 106, 255
#define aqua 3, 64, 38, 255
#define dark_purple 28, 10, 27, 255

class InfoTab{
private:
  sf::Text text;
  std::string s="A* is weighted and generally offers the shortest path,\nas it is based on heuristics. It is generally the best choice in pathfinding.\n\nDijkstra is weighted and guarantees the shortest path.\n\nBreadth First Search is non weighted and guarantees the shortest path.\n\nDepth First Search is non weighted and does not guarantee\nthe shortest path.\n\nBest First Search is weighted and does not guarantee the shortest path.\n\n";
  std::string s2="Controls:\nShift + LMB -> Place source\t\t\t Ctrl + LMB -> Place destination\nRMB -> Place walls\t\t\t\t\t\t  Shift+RMB -> Place weights\nF11 -> Toggle fullscreen\t\t\t\t   Esc -> Close application";
public:
  InfoTab(sf::Font& font)
  {
    s+=s2;
    this->text.setString(this->s);
    this->text.setFillColor(sf::Color(dark_purple));
    this->text.setFont(font);
  }
  void display(sf::RenderWindow& window)
  {
    float x,y,mat_W,mat_H,tx, ty;
    float xAxisAdd = window.getSize().x/4.;
    if(window.getSize().y/window.getSize().x>0.6)
    {
      y=2*window.getSize().y/12.,x=(window.getSize().x-8.*window.getSize().y/12.)/2.;
      mat_W=mat_H=8*window.getSize().y/12.;
    }else{
      y=window.getSize().y/8.,x=(window.getSize().x-6.*window.getSize().y/8.)/2.;
      mat_W=mat_H=6*window.getSize().y/8.;
    }
    x+=xAxisAdd/2.;
    tx=x+mat_W/24., ty = y + mat_W/24.;
    float charSize = mat_W/32.5;
    this->text.setCharacterSize(charSize);
    this->text.setPosition({tx,ty});
    sf::RectangleShape rect;
    rect.setPosition({x,y});
    rect.setSize({mat_W,mat_H});
    rect.setFillColor(sf::Color(yellowish));
    rect.setOutlineThickness(0.5);
    rect.setOutlineColor(sf::Color(dark_purple));
    window.draw(rect);
    window.draw(this->text);
  }
};

#endif
