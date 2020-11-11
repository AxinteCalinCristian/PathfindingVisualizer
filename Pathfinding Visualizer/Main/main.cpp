#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstdlib>
#include <iostream>
#include "GUI/winManager.hpp"
#include "GUI/Button.hpp"

#define darkBlue 38, 70, 83, 255
#define cyan 42, 157, 143, 255
#define mustard 233, 196, 106, 255
#define peach 244, 162, 97, 255
#define redish 231, 111, 81, 255
#define light_teal 154, 211, 188, 255
#define yellowish 243, 234, 194, 255
#define warm_orange 245, 180, 97, 255
#define warm_red 236, 82, 75, 255
#define blue_gray 99, 115, 115, 255
#define dark_purple 28, 10, 27, 255
#define dark_red 64, 7, 27, 255

#define wid 1280
#define hei 720

int main()
{
  sf::Font font;
  if (!font.loadFromFile("Graphics/calibri.ttf"))
      std::cout<<"font fail\n";
  GUI gui(font,sf::Color(dark_purple),sf::Color(dark_red),wid,hei);
  Window mainWindow(wid,hei,"Pathfinding Visualizer",gui);
  mainWindow.run();
}
