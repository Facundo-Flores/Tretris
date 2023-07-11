//
// Created by fkflo on 7/7/2023.
//

#ifndef CLASSYCLASH_GRID_H
#define CLASSYCLASH_GRID_H
#include <vector>
#include "Piece.h"

class Grid {
public:
    static void drawGrid(std::vector<std::vector<int>>& grid, int gridSizeY, int gridSizeX, int blockSize);
};


#endif //CLASSYCLASH_GRID_H
