#include <string>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "renderer.h"
#include "exceptions.h"

// maybe should take polymorphic board class to handle CPU/GPU
void Renderer::drawBoard(const std::vector<std::vector<int>>& board,const int generation) {
    if (!window.isOpen()) { // check if window no longer open
        throw ClosedWindowException();
    }
    sf::Event event;
    while (window.pollEvent(event)) { // check if user has closed window since last draw
        if (event.type == sf::Event::Closed) {
            window.close();
            throw ClosedWindowException();
        }
    }

    window.clear(sf::Color::Black); // clear window
    // create generation text
    sf::Text gen_text;
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/tlwg/Garuda.ttf")) {
        throw std::invalid_argument("Failed to find font");
    }
    gen_text.setFont(font);
    gen_text.setString(std::string("Generation: ") + std::to_string(generation));
    gen_text.setCharacterSize(text_height);
    gen_text.setPosition(0,size*cell_size);
    gen_text.setFillColor(sf::Color::White);
    window.draw(gen_text);

    for (int i = 0; i < size; i++) { // loop through board and draw each cell 
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 1) {
                sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
                cell.setPosition(cell_size*i, cell_size*j);
                cell.setFillColor(sf::Color::White);
                window.draw(cell);
            }
        }
    }
    window.display();
}