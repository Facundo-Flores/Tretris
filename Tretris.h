//
// Created by fkflo on 7/7/2023.
//

#ifndef CLASSYCLASH_TRETRIS_H
#define CLASSYCLASH_TRETRIS_H
#include <vector>
#include "raylib.h"
#include "Piece.h"

class Tretris {
public:
    static bool CheckCollision(std::vector<std::vector<int>>& grid, int currentPieceShape[4][4], int piece, Vector2 position, int gridSizeX, int gridSizeY);
    static bool CheckCollisionRotated(std::vector<std::vector<int>>& grid, int rotatedPiece[4][4], Vector2 position, int gridSizeX, int gridSizeY);
    static void RotatePiece(int tretrominoe[4][4]);
    static void AddToGrid(std::vector<std::vector<int>>& grid, const int tretrominoe[4][4], Vector2 position);
};


#endif //CLASSYCLASH_TRETRIS_H
