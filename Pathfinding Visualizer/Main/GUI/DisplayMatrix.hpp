#ifndef DISPLAYMATRIX_H
#define DISPLAYMATRIX_H

const int INT_MIN = -10000000;
const int INT_MAX = 10000000;

enum cell_state{CELL_VISITED = INT_MIN, CELL_SRC=INT_MIN+1,CELL_WEIGHT=15, CELL_DEST=INT_MAX-1, CELL_IDLE = 0, CELL_WALL=INT_MAX, CELL_PATH = INT_MAX+1};

#define yellowish 243, 234, 194, 255
#define warm_orange 245, 180, 97, 255
#define avg_red 209, 31, 55, 255
#define cyan 42, 157, 143, 255
#define blue_gray 99, 115, 115, 255
#define light_teal 154, 211, 188, 255
#define mustard 233, 196, 106, 255
#define aqua 3, 64, 38, 255

class Matrix{

private:
  int width;
  int height;
  std::vector<std::vector<int>> matrix;
  sf::Vector2i origin={-1,-1},dest={-1,-1};
public:
  bool settingOrigin = false;
  bool settingDest = false;
  bool settingWalls = false;
  bool settingWeights = false;
  Matrix(int width,int height):width(width),height(height)
  {
    matrix.resize(height,std::vector<int>(width));
  }
  std::vector<std::vector<int>>* getMatrix()
  {
    std::vector<std::vector<int>>* p = &(this->matrix);
    return p;
  }
  sf::Vector2i getSource()
  {
    return this->origin;
  }
  sf::Vector2i getDest()
  {
    return this->dest;
  }
  void setSize(int width,int height)
  {
    this->width = width;
    this->height = height;
    matrix.resize(height);
    for(int i=0;i<matrix.size();i++)
      matrix[i].resize(width);
    std::cout<<this->matrix.size()<<'\t'<<this->matrix[0].size()<<'\n';
  }
  sf::Vector2i getSize()
  {
    return sf::Vector2i(this->width,this->height);
  }
  void drawCell(sf::RenderWindow& window, float x, float y, float width, float height,int i,int j)
  {
    sf::RectangleShape cell;
    cell.setPosition({x,y});
    cell.setSize({width,height});
    cell.setFillColor(sf::Color(yellowish));
    cell.setOutlineThickness(0.5);
    cell.setOutlineColor(sf::Color::Black);
    if(settingOrigin && cell.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
    {
      origin = {i,j};
      settingOrigin = false;
      matrix[i][j]=CELL_SRC;
    }
    if(settingDest && cell.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
    {
      dest = {i,j};
      settingDest = false;
      matrix[i][j]=CELL_DEST;
    }
    if(i==origin.x && j==origin.y)
    {
      cell.setFillColor(sf::Color(avg_red));
      window.draw(cell);
      return;
    }
    if(i==dest.x && j==dest.y)
    {
      cell.setFillColor(sf::Color(cyan));
      window.draw(cell);
      return;
    }
    if(settingWalls && cell.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)
    && matrix[i][j]!=CELL_DEST && matrix[i][j]!=CELL_SRC)
    {
      matrix[i][j]=CELL_WALL, cell.setFillColor(sf::Color(blue_gray));
      window.draw(cell);
      return;
    }
    if(matrix[i][j]==CELL_WALL)
    {
      cell.setFillColor(sf::Color(blue_gray));
      window.draw(cell);
      return;
    }
    if(settingWeights && cell.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)
    && matrix[i][j]!=CELL_DEST && matrix[i][j]!=CELL_SRC)
    {
      matrix[i][j]=CELL_WEIGHT, cell.setFillColor(sf::Color(aqua));
      window.draw(cell);
      return;
    }
    if(matrix[i][j]==CELL_WEIGHT)
    {
      cell.setFillColor(sf::Color(aqua));
      window.draw(cell);
      return;
    }
    if(matrix[i][j]==CELL_VISITED)
    {
      cell.setFillColor(sf::Color(light_teal));
      window.draw(cell);
      return;
    }
    else if(matrix[i][j]==CELL_PATH)
    {
      cell.setFillColor(sf::Color(mustard));
      window.draw(cell);
      return;
    }
    matrix[i][j]=CELL_IDLE;
    if(cell.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
      cell.setFillColor(sf::Color(warm_orange));
    else
      cell.setFillColor(sf::Color(yellowish));
    window.draw(cell);
  }
  void resetMat()
  {
    for(int i=0;i<this->height;i++)
      for(int j=0;j<this->width;j++)
        this->matrix[i][j]=CELL_IDLE;
    origin={-1,-1}; dest={-1,-1};
  }
  void renderMatrix(sf::RenderWindow& window)
  {
      float x,y,mat_W,mat_H;
      float xAxisAdd = window.getSize().x/4.;
      if(window.getSize().y/window.getSize().x>0.6)
      {
        y=2*window.getSize().y/12.,x=(window.getSize().x-8.*window.getSize().y/12.)/2.;
        mat_W=mat_H=8*window.getSize().y/12.;
      }
      else if(this->width==this->height)
      {
        y=window.getSize().y/8.,x=(window.getSize().x-6.*window.getSize().y/8.)/2.;
        mat_W=mat_H=6*window.getSize().y/8.;
      }else if(this->width>this->height)
      {
        float ratio = this->width/this->height;
        mat_H = 6*window.getSize().y/8./ratio;
        mat_W = 6*window.getSize().y/8.;
        x=(window.getSize().x-6.*window.getSize().y/8.)/2.;
        y=(window.getSize().y-6*window.getSize().y/8./ratio)/2.;
      }else
      {
        float ratio = this->height/this->width;
        mat_H = 6*window.getSize().y/8.;
        mat_W = 6*window.getSize().y/8./ratio;
        x=(window.getSize().x-6.*window.getSize().y/8./ratio)/2.;
        y=window.getSize().y/8.;
      }
      x+=xAxisAdd/2.;
      float cell_W = mat_W/this->width,
      cell_H = mat_H/this->height;
      for(int i=0;i<this->height;i++)
        for(int j=0;j<this->width;j++)
          drawCell(window, x+j*cell_W,y+i*cell_H,cell_W-2,cell_H-2,i,j);
  }
};

#endif
