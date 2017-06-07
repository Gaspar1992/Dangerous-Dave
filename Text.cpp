#include "Text.hpp"

Text::Text() {
    font = new sf::Font;
    text = new sf::Text;
}

Text::Text(const Text& orig) {
}

Text::~Text() {
    delete font;
    delete text;
}
void Text::setFont(std::string archivo){
    font->loadFromFile("resources/"+archivo);
    text->setFont(*font);
}
void Text::setSize(int size){
    text->setCharacterSize(size);
}
void Text::setPosition(float x, float y){
    text->setPosition(x,y);
}
void Text::move(float x, float y){
    text->move(x,y);
}
void Text::setString(std::string texto){
    text->setString(texto);
}
void Text::setColor(sf::Color color){
    text->setColor(color);
}
void Text::setstyle(sf::Text::Style estilo){
    text->setStyle(estilo);
}