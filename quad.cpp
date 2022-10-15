#include "quad.hpp"

using namespace std;
#define SIZE 20

Quad::Quad(int x, int y) {
    this->alive = 0;
    sf::RectangleShape quadShape(sf::Vector2f(SIZE, SIZE));
    quadShape.setPosition(x,y);
    quadShape.setFillColor(sf::Color::White);

    this->shape = quadShape;
}

bool Quad::isAlive() {
    return this->alive;
}

void Quad::switchState() {
    if(this->alive) {
        this->shape.setFillColor(sf::Color::White);
    } else {
        this->shape.setFillColor(sf::Color::Black);    
    }

    this->alive = !this->alive;
};

sf::RectangleShape Quad::getShape() {
    return this->shape;
}

void Quad::setShape(sf::RectangleShape shape) {
    this->shape = shape;
}