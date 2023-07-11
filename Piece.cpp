//
// Created by fkflo on 7/7/2023.
//
#include <vector>
#include "Piece.h"
#include "Tretris.h"

std::vector<Color> Piece::pieceColors = {
        DARKBLUE,  // 0 - I
        PURPLE,    // 1 - J
        YELLOW,    // 2 - L
        GREEN,     // 3 - O
        ORANGE,    // 4 - S
        RED,       // 5 - T
        SKYBLUE    // 6 - Z
};

std::vector<Texture2D> Piece::pieceTextures = std::vector<Texture2D>(7); // Empty textures for now

void Piece::InitTextures(int blockSize) {
    pieceTextures[0] = GenerateSquareTexture(DARKBLUE, blockSize);
    pieceTextures[1] = GenerateSquareTexture(PURPLE, blockSize);
    pieceTextures[2] = GenerateSquareTexture(YELLOW, blockSize);
    pieceTextures[3] = GenerateSquareTexture(GREEN, blockSize);
    pieceTextures[4] = GenerateSquareTexture(ORANGE, blockSize);
    pieceTextures[5] = GenerateSquareTexture(RED, blockSize);
    pieceTextures[6] = GenerateSquareTexture(SKYBLUE, blockSize);
}

void Piece::UnloadTextures() {
    for (auto& texture : pieceTextures) {
        UnloadTexture(texture);
    }
}

void Piece::DrawPiece(Vector2 currentPiecePos, int currentPiece, int currentPieceShape[4][4], int blockSize) {
    // Draw current piece
    for (int y{0}; y < 4; ++y) {
        for (int x{0}; x < 4; ++x) {
            if (currentPieceShape[y][x] == 1) {
                // Calculate the pixel position of the block
                int blockPosX = (x + currentPiecePos.x) * blockSize;
                int blockPosY = (y + currentPiecePos.y) * blockSize;

                // Draw the block
                //DrawRectangle(blockPosX, blockPosY, blockSize, blockSize, RAYWHITE);
                DrawTextureRec(Piece::pieceTextures[currentPiece], {0.0f, 0.0f, static_cast<float>(blockSize), static_cast<float>(blockSize)}, {static_cast<float>(blockPosX), static_cast<float>(blockPosY)}, Piece::pieceColors[currentPiece]);
            }
        }
    }
}

int Piece::UpdatePiece(std::vector<std::vector<int>>& grid, Vector2 &currentPiecePos, int currentPiece, int currentPieceShape[4][4],
                       Vector2& nextPiecePos, int& nextPiece, int nextPieceShape[4][4],
                       float &fallTimer, float fallInterval, float &moveTimer, float moveInterval,
                       int gridSizeX, int gridSizeY, int& score) {
    // Update falling
    fallTimer += GetFrameTime();
    if (fallTimer > fallInterval) {
        // Check for collision before moving the piece
        if (!Tretris::CheckCollision(grid, currentPieceShape, currentPiece, {currentPiecePos.x, currentPiecePos.y + 1}, gridSizeX, gridSizeY)) {
            currentPiecePos.y += 1; // We increment the piece's y-coordinate once every second
        }
        fallTimer = 0;
    }


    moveTimer += GetFrameTime();
    if (moveTimer > moveInterval) {
        if (IsKeyDown(KEY_LEFT) && !Tretris::CheckCollision(grid, currentPieceShape, currentPiece, {currentPiecePos.x - 1, currentPiecePos.y}, gridSizeX, gridSizeY)) {
            currentPiecePos.x -= 1;
        }
        if (IsKeyDown(KEY_RIGHT) && !Tretris::CheckCollision(grid, currentPieceShape, currentPiece, {currentPiecePos.x + 1, currentPiecePos.y}, gridSizeX, gridSizeY)) {
            currentPiecePos.x += 1;
        }
        moveTimer= 0;
    }

    // Rotate tretrominoe
    if (IsKeyPressed(KEY_UP)) {
        // Copy the current tretrominoe and rotate it
        int rotatedPiece[4][4];
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                rotatedPiece[y][x] = currentPieceShape[y][x];
            }
        }
        Tretris::RotatePiece(rotatedPiece);

        // Only apply the rotation if it wouldn't cause a collision
        if (!Tretris::CheckCollisionRotated(grid, rotatedPiece, currentPiecePos, gridSizeX, gridSizeY)) {
            for (int y = 0; y < 4; ++y) {
                for (int x = 0; x < 4; ++x) {
                    currentPieceShape[y][x] = rotatedPiece[y][x];
                }
            }
        }
    }

    // Check if the piece has landed
    if (Tretris::CheckCollision(grid, currentPieceShape, currentPiece, {currentPiecePos.x, currentPiecePos.y + 1}, gridSizeX, gridSizeY)) {
        // Add the piece to the grid
        Tretris::AddToGrid(grid, currentPieceShape, currentPiecePos);

        currentPiece = nextPiece;
        currentPiecePos = {5, 0};
        for (int y{0}; y < 4; ++y) {
            for (int x{0}; x < 4; ++x) {
                currentPieceShape[y][x] = nextPieceShape[y][x];
            }
        }
        // Spawn a new piece at the top of the grid
        Piece::NewPiece(nextPiece, nextPieceShape);
    }

    // Check if lines were cleared and update score
    int linesCleared = Piece::CheckLines(grid);
    if (linesCleared > 0) {
        score += linesCleared * linesCleared * 10;  // Multiply score for clearing multiple lines at once
    }

    return nextPiece;
}

int Piece::NewPiece(int &currentPiece, int (*currentPieceShape)[4]) {
    currentPiece = GetRandomValue(0, 6);

    // Initialize the currentPieceShape
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            currentPieceShape[y][x] = TRETROMINOES[currentPiece][y][x];
        }
    }

    // Return next piece
    return GetRandomValue(0, 6);
}

int Piece::CheckLines(std::vector<std::vector<int>>& grid) {
    int linesCleared = 0;
    int gridSizeY = grid.size();
    int gridSizeX = grid.at(0).size();

    for (int y = gridSizeY - 1; y >= 0; --y) {
        bool lineComplete = true;
        for (int x = 0; x < gridSizeX; ++x) {
            if (grid[y][x] == 0) {
                lineComplete = false;
                break;
            }
        }
        if (lineComplete) {
            for (int y2 = y; y2 > 0; --y2) {
                for (int x = 0; x < gridSizeX; ++x) {
                    grid[y2][x] = grid[y2 - 1][x];  // Move rows down
                }
            }
            for (int x = 0; x < gridSizeX; ++x) {
                grid[0][x] = 0;  // Clear top row
            }
            ++linesCleared;
        }
    }
    return linesCleared;
}
