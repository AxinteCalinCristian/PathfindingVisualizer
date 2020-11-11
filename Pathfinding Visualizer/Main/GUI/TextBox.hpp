#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>

enum keys{DELETE_KEY = 8, ENTER_KEY = 13, ESC_KEY = 27};

class TextBox{
private:
  std::string defaultTxt;
  sf::Text textbox;
  sf::RectangleShape shape;
  std::ostringstream text;
  int limit;
  float width;
  float height;
  float outlineLen;
  sf::Color txtCol;
  sf::Color outColor;
  void delLastChar()
  {
    std::string s=this->text.str(),
    newS = "";
    for(int i=0;i<s.length()-1;i++)
      newS+=s[i];
    this->text.str("");
    this->text<<newS;
    this->textbox.setString(this->text.str());
  }
  void inputLogic(int charTyped)
  {
    if(charTyped!=DELETE_KEY && charTyped!=ENTER_KEY && charTyped!=ESC_KEY)
    {
      this->text << static_cast<char>(charTyped);
    }else if(charTyped==DELETE_KEY)
    {
      if(this->text.str().length()>0)
        delLastChar();
    }
    this->textbox.setString(text.str()+"_");
  }

public:
  bool isSelected = false;
  float fontSize;
  TextBox(){ }
  TextBox(sf::Color bgColor,int fontSize,sf::Color txtCol,bool selected,float width,float height,float outLen=0, sf::Color outCol = sf::Color::Black,std::string defaultText=""):
  fontSize(fontSize),width(width),height(height),defaultTxt(defaultText),outColor(outCol),outlineLen(outLen),txtCol(txtCol)
  {
    this->textbox.setCharacterSize(this->fontSize);
    this->textbox.setFillColor(txtCol);
    this->isSelected = selected;
    if(this->isSelected)
    {
      this->text<<defaultText;
      this->textbox.setString(this->text.str()+"_");
    }else
    {
      this->text<<defaultText;
      this->textbox.setString(this->text.str());
    }
    sf::FloatRect textRect = this->textbox.getLocalBounds();
    this->textbox.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);

    if(this->isSelected)
      this->shape.setOutlineThickness(outlineLen);
    else
      this->shape.setOutlineThickness(0);

    this->shape.setSize({width,height});
    this->shape.setOutlineColor(outCol);
    this->shape.setFillColor(bgColor);
    this->limit = width/fontSize+2;
  }
  void setFont(sf::Font& font)
  {
    this->textbox.setFont(font);
  }
  void setPosition(sf::Vector2f pos)
  {
    this->textbox.setPosition(pos);
    float x=pos.x-this->textbox.getLocalBounds().width/2.0f, y=pos.y-this->textbox.getLocalBounds().height/2.0f;
    this->shape.setPosition({x,y});

  }
  void setSelected(bool selected)
  {
    this->isSelected = selected;
    if(this->text.str().length()==0)
      this->text<<this->defaultTxt;
    if(!(this->isSelected))
    {
      this->shape.setOutlineThickness(0);
      this->textbox.setString(this->text.str());
    }else
    {
      this->shape.setOutlineThickness(this->outlineLen);
      this->textbox.setString(this->text.str()+"_");
    }
  }
  std::string getText()
  {
    return text.str();
  }
  void setString(std::string s)
  {
    while(this->text.str().length()>0)
      delLastChar();
    this->text<<s;
    this->textbox.setString(this->text.str());
  }
  void typedInto(sf::Event& input)
  {
    if(this->isSelected)
    {
      int charTyped = input.text.unicode;
      if(charTyped<128)
      {
        if(text.str().length()<=this->limit)
          inputLogic(charTyped);
        else if(text.str().length()>this->limit && charTyped == DELETE_KEY)
          delLastChar();
      }
    }
  }
  void render(sf::RenderWindow& window,float x,float y,float width,float height)
  {
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width,height));
    this->textbox.setCharacterSize(this->fontSize * ((width/this->width + height/this->height)/2.));
    sf::FloatRect textRect = this->textbox.getLocalBounds();
    this->textbox.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    float xt = x + width/2.;
    float yt = y + height/2.;
    this->textbox.setPosition(xt,yt);
    window.draw(this->shape);
    window.draw(this->textbox);
  }
  void update(const sf::Vector2i& mousePos, bool mouseClicked)
  {
    if(this->shape.getGlobalBounds().contains(mousePos.x,mousePos.y) && mouseClicked)
      this->setSelected(true);
    else if(mouseClicked && !(this->shape.getGlobalBounds().contains(mousePos.x,mousePos.y)))
      this->setSelected(false);
  }
};


#endif
