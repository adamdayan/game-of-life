#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SFML/Graphics.hpp>

class Renderer {
  public:
    Renderer(int size) : size(size) {}
    void drawBoard(const std::vector<std::vector<int>>& board, const int generation);
  private:
    int size;
    const float cell_size = 2.0;
    const int text_height = 30;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(size*cell_size, (size*cell_size)+text_height+10), "game_window");
};

#endif