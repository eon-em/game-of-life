#include <SFML/Graphics.hpp>

class Quad {
    private:
        bool alive;
        sf::RectangleShape shape;

    public:
        Quad(int x, int y);

        void switchState();

        bool isAlive();

        sf::RectangleShape getShape();

        void setShape(sf::RectangleShape shape);
};