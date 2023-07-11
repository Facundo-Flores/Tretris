//
// Created by fkflo on 7/7/2023.
//

#ifndef CLASSYCLASH_PIECE_H
#define CLASSYCLASH_PIECE_H
#include <vector>
#include "raylib.h"
#include "Images.h"
#include "Pieces.h"

class Piece {
public:
    static int NewPiece(int &currentPiece, int currentPieceShape[4][4]);
    static int UpdatePiece(std::vector<std::vector<int>>& grid, Vector2 &currentPiecePos, int currentPiece, int currentPieceShape[4][4],
                           Vector2& nextPiecePos, int& nextPiece, int nextPieceShape[4][4],
                           float &fallTimer, float fallInterval, float &moveTimer, float moveInterval,
                           int gridSizeX, int gridSizeY, int& score);
    static void DrawPiece(Vector2 currentPiecePos, int currentPiece, int currentPieceShape[4][4], int blockSize);
    static int CheckLines(std::vector<std::vector<int>>& grid);

    static std::vector<Color> pieceColors;
    static std::vector<Texture2D> pieceTextures;
    static void InitTextures(int blockSize);
    static void UnloadTextures();
};



#endif //CLASSYCLASH_PIECE_H
