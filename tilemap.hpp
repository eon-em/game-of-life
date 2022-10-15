#include <vector>
#include "quad.hpp"

using namespace std;

class Tilemap {
    public:
        Tilemap(int height, int width, int size);

        vector<vector<Quad>> getGrid();

        void setGrid(vector<vector<Quad>> grid);

        void iterate();

        bool survive(int row, int col);

        bool revive(int row, int col);
    
    private:
        vector<vector<Quad>> grid;
};