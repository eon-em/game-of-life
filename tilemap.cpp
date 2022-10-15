#include "tilemap.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

Tilemap::Tilemap(int height, int width, int size) {
    vector<vector<Quad>> newGrid;
    
    for(int x=0; x<width; x+=size) {
        vector<Quad> row;
        for(int y=0; y<height; y+=size) {
            Quad quad(x,y);
            row.push_back(quad);
        }
        newGrid.push_back(row);
    }

    this->grid = newGrid;
}

vector<vector<Quad>> Tilemap::getGrid() {
    return this->grid;
}

void Tilemap::setGrid(vector<vector<Quad>> grid) {
    this->grid = grid;
}

void Tilemap::iterate() {
    vector<vector<Quad>> updatedGrid = this->grid;
    // cout << "Here" << endl;

    for(int i=0; i<this->grid.size(); i++) {
        for(int j=0; j<this->grid[0].size(); j++) {
            // cout << "Here at (" << i << "," << j << ")" << endl;
            if(this->grid[i][j].isAlive() && !survive(i,j)){
                //kills cell
                updatedGrid[i][j].switchState();
            }

            if(!this->grid[i][j].isAlive() && revive(i,j)) {
                //revives cell
                updatedGrid[i][j].switchState();
            }
        }
    }

    this->grid = updatedGrid;
    return;
}

bool Tilemap::survive(int row, int col) {
    // Function only returns true if cell is alive
    Quad cell = this->grid[row][col];
    int aliveNeighbors = 0;

    if(!cell.isAlive())
        return false;
    
    for(int x = max(0, row-1); x <= min(row+1, (int) this->grid.size()-1); x++) {
        for(int y = max(0, col-1); y <= min(col+1, (int) this->grid[row].size()-1); y++) {
            if(x != row || y != col) {
                if(this->grid[x][y].isAlive())
                    aliveNeighbors++;
            }
        }
    }      

    return aliveNeighbors == 2 || aliveNeighbors == 3;
}

bool Tilemap::revive(int row, int col) {
    // Function only returns true if cell is dead
    Quad cell = this->grid[row][col];
    int aliveNeighbors = 0;

    // cout << "Here" << endl;

    if(cell.isAlive())
        return false;

    for(int x = max(0, row-1); x <= min(row+1, (int) this->grid.size()-1); x++) {
        for(int y = max(0, col-1); y <= min(col+1, (int) this->grid[row].size()-1); y++) {
            if(x != row || y != col) {
                // cout << "\tHere testing neighbor (" << x << "," << y << ")" << endl;

                if(this->grid[x][y].isAlive())
                    aliveNeighbors++;
            }
        }
    }       

    return aliveNeighbors == 3;   
}