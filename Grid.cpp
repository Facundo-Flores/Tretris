//
// Created by fkflo on 7/7/2023.
//

#include <vector>
#include "Grid.h"
#include "raylib.h"


void Grid::drawGrid(std::vector<std::vector<int>>& grid, int gridSizeY, int gridSizeX, int blockSize) {

    // Draw the game grid
    for (int y = 0; y < gridSizeY; ++y) {
        for (int x = 0; x < gridSizeX; ++x) {
            if (grid[y][x] == 1) {
                // Calculate the pixel position of the block
                int blockPosX = x * blockSize;
                int blockPosY = y * blockSize;

                // Draw the block
                DrawRectangle(blockPosX, blockPosY, blockSize, blockSize, RAYWHITE);
            }
        }
    }
}
