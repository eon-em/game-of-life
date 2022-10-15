#include "tilemap.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>


using namespace std;

#define SIZE 20
#define SLEEP_TIME 700

#define WIDTH 1000
#define HEIGHT 1000

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game_of_Life");

    // initialize counter
    sf::Font font;
    if(!font.loadFromFile("arial.ttf")) {
        cerr << "Could not load counter font" << endl;
    }
 
    int generation = 0;
    sf::Text genCounter;
    genCounter.setFont(font);
    genCounter.setCharacterSize(40);
    genCounter.setFillColor(sf::Color::Red);

    Tilemap tilemap(WIDTH, HEIGHT, SIZE);
    vector<vector<Quad>> tiles = tilemap.getGrid();

    cout << "tiles size is " << tiles.size() << " x " << tiles[0].size() << endl;

    // seed tilemap
    std::ifstream infile("seed.txt");
    int xSeed, ySeed;
    while(infile >> xSeed >> ySeed) {
        if(0 <= xSeed && xSeed < tiles.size() && 0 <= ySeed && ySeed < tiles[0].size()) {
            tiles[xSeed][ySeed].switchState();
        } else {
            cerr << "(" << xSeed << "," << ySeed << ") is out of bounds." << endl;
        }
    }

    tilemap.setGrid(tiles);

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();
        tilemap.iterate();
        tiles = tilemap.getGrid();

        for(int i=0; i<tiles.size(); i++)
            for(int j=0; j<tiles[0].size(); j++) {
                window.draw(tiles[i][j].getShape());
            }

        genCounter.setString("Generation: " + to_string(generation));
        generation++;

        window.draw(genCounter);

        this_thread::sleep_for(chrono::milliseconds(SLEEP_TIME));
        window.display();
    }

    return 0;
}
