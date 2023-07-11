//
// Created by fkflo on 7/7/2023.
//
#include <vector>
#include "Tretris.h"

// Check if piece collides with borders or other piece
bool Tretris::CheckCollision(std::vector<std::vector<int>>& grid, int currentPieceShape[4][4], int piece, Vector2 position, int gridSizeX, int gridSizeY) {
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            // If the cell is filled in the piece
            if (currentPieceShape[y][x] == 1) {
                // If the cell is out of bounds or colliding with a filled cell on the grid
                if (x + position.x < 0 || x + position.x >= gridSizeX || y + position.y < 0 || y + position.y >= gridSizeY || grid[int(y + position.y)][int(x + position.x)] == 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Check for collision when rotating piece
bool Tretris::CheckCollisionRotated(std::vector<std::vector<int>>& grid, int rotatedPiece[4][4], Vector2 position, int gridSizeX, int gridSizeY) {
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (x + position.x < 0 || x + position.x >= gridSizeX || y + position.y < 0 || y + position.y >= gridSizeY) {
                continue;
            }
            if (rotatedPiece[y][x] == 1) {
                if (grid[int(y + position.y)][int(x + position.x)] == 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Rotate the current piece 90 degrees clockwise
void Tretris::RotatePiece(int tretrominoe[4][4]) {
    int newTretrominoe[4][4];

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            newTretrominoe[j][3 - i] = tretrominoe[i][j];
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            tretrominoe[i][j] = newTretrominoe[i][j];
        }
    }
}

// Add the current piece to the grid
void Tretris::AddToGrid(std::vector<std::vector<int>>& grid, const int tretrominoe[4][4], Vector2 position) {
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (tretrominoe[y][x] == 1) {
                grid[int(y + position.y)][int(x + position.x)] = 1;
            }
        }
    }
}