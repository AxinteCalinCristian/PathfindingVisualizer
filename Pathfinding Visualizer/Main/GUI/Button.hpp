#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

enum but_states{BTN_IDLE, BTN_HOVER, BTN_PRESSED, BTN_SELECTED};

class Button{
private:
  short unsigned btnState;
  float x,y;
  float width,height;
  bool canBeSelected;

  int fontSize;
  sf::Text text;
  sf::Font font;
  sf::RectangleShape shape;
  sf::Color idle;
  sf::Color hover;
  sf::Color hoverOut;
  sf::Color active;
  sf::Color activeOut;
  sf::Color textCol;
  float outlineLen;
public:
  bool toggled;

  Button(float x,float y,float width,float height,sf::Font& font, std::string txt,int fontSize,
    sf::Color idle, sf::Color hover, sf::Color active,sf::Color hoverOut =sf::Color::Red, sf::Color activeOut = sf::Color::Red,
    float outLen=0, sf::Color textCol=sf::Color::White,bool canSelect = false):
  font(font),idle(idle),hover(hover),active(active),x(x),y(y),width(width),height(height),
  fontSize(fontSize),btnState(BTN_IDLE),canBeSelected(canSelect), textCol(textCol),
  hoverOut(hoverOut),activeOut(activeOut),outlineLen(outLen)
  {
    toggled=false;
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width,height));
    this->shape.setOutlineThickness(this->outlineLen);
    this->text.setFont(font);
    this->text.setString(sf::String(txt));
    this->text.setFillColor(textCol);
    this->text.setCharacterSize(fontSize);
    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    float xt = x + width/2.;
    float yt = y + height/2.;
    this->text.setPosition(xt,yt);
  }
  ~Button(){}

  //Accessors
  bool isPressed()
  {
    if(this->btnState == BTN_PRESSED || this->btnState == BTN_SELECTED) return true;
    return false;
  }

  void update(const sf::Vector2i& mousePos, bool mouseClicked)
  {
    if(toggled)
    {
      this->btnState = BTN_SELECTED; //default = idle
    }else
    {
      this->btnState = BTN_IDLE; //default = idle
    }
    if(this->shape.getGlobalBounds().contains(mousePos.x,mousePos.y)) // hover
    {
      this->btnState = BTN_HOVER;
      if(mouseClicked) //clicked = active
      {
        if(canBeSelected)
        {
          if(toggled)
          {
            this->btnState = BTN_HOVER;
          }else
          {
            this->btnState = BTN_SELECTED;
          }
          toggled = !toggled;
        }
        else this->btnState = BTN_PRESSED;
      }
    }
    switch(this->btnState){
      case BTN_IDLE: this->shape.setFillColor(this->idle),this->shape.setOutlineThickness(0); break;
      case BTN_HOVER: this->shape.setFillColor(this->hover),this->shape.setOutlineThickness(outlineLen),this->shape.setOutlineColor(this->hoverOut); break;
      case BTN_PRESSED: this->shape.setFillColor(this->active),this->shape.setOutlineThickness(outlineLen),this->shape.setOutlineColor(this->activeOut); break;
      case BTN_SELECTED: this->shape.setFillColor(this->active),this->shape.setOutlineThickness(outlineLen),this->shape.setOutlineColor(this->activeOut); break;
      default: this->shape.setFillColor(sf::Color::Red); break;
    }
  }
  void render(sf::RenderWindow& target,float x, float y, float width, float height)
  {
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width,height));
    this->text.setCharacterSize(this->fontSize * ((width/this->width + height/this->height)/2.));
    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    float xt = x + width/2.;
    float yt = y + height/2.;
    this->text.setPosition(xt,yt);
    target.draw(this->shape);
    target.draw(this->text);
  }
};


#endif
