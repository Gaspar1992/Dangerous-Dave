#include "window.hpp"

window::window() {
    ventana = new sf::RenderWindow(sf::VideoMode(640,400,32),"Dangerous Dave",sf::Style::Default);
    ventana->setFramerateLimit(60);
    ventana->setVerticalSyncEnabled(true);
}

window::window(const window& orig) {
}

window::~window() {
    delete ventana;
}

void window::draw(const sf::Drawable& drawable) {
    ventana->draw(drawable);
}

bool window::isOpen() {
    return ventana->isOpen();
}

void window::close() {
    ventana->close();
}

bool window::pollEvent(sf::Event& event) {
    return ventana->pollEvent(event);
}

void window::display() {
    ventana->display();
}

void window::clear() {
    ventana->clear();
}

void window::clear(sf::Color color) {
    ventana->clear(color);
}

void window::setView(sf::View vista){
    ventana->setView(vista);
}