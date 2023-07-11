#include <string>
#include <vector>
#include "raylib.h"
#include "Piece.h"
#include "Grid.h"

/* ----------------------------- *
 * Game configuration Parameters *
 * ----------------------------- */
// Main Window
const int winHeight{800};
const int winWidth{600};
const std::string gameTitle{"Tretris"};

// Tretris grid, 26x20
const int gridSizeX{20};  // The number of cells along the x axis
const int gridSizeY{26};  // The number of cells along the y axis
const int blockSize{30};  // The size of each block in pixels

// Fall movement, y-axis
const float fallInterval{0.5f}; // Amount of time between each fall
const float moveInterval{0.1}; // The delay between each movement

// Score tracking
int score{0};

/*-----------------------------------------------*/

/* ----------------------------- *
 * Game Loop                     *
 * ----------------------------- */
void gameLoop(std::vector<std::vector<int>>& grid, Vector2 &currentPiecePos, int &currentPiece, int(&currentPieceShape)[4][4], Vector2& nextPiecePos, int& nextPiece, int(&nextPieceShape)[4][4]) {
    // Pieces falling and left-right movement
    float fallTimer{0}; // Amount of time the current piece has been falling
    float moveTimer{0}; // Timer to regulate the left/right movement speed

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        Grid::drawGrid(grid, gridSizeY, gridSizeX, blockSize);
        Piece::DrawPiece(currentPiecePos, currentPiece, currentPieceShape, blockSize);
        nextPiece = Piece::UpdatePiece(grid, currentPiecePos, currentPiece, currentPieceShape, nextPiecePos, nextPiece, nextPieceShape,
                                       fallTimer, fallInterval, moveTimer, moveInterval, gridSizeX, gridSizeY, score);
        Piece::DrawPiece(nextPiecePos, nextPiece,nextPieceShape, blockSize);

        EndDrawing();
    }
}


int main() {

    // Game main window
    InitWindow(winWidth, winHeight, gameTitle.c_str());
    // Initialize the game grid
    std::vector<std::vector<int>> grid(gridSizeY, std::vector<int>(gridSizeX));

    int currentPiece{GetRandomValue(0, 6)};
    Vector2 currentPiecePos{5, 0};
    int currentPieceShape[4][4];
    Piece::NewPiece(currentPiece, currentPieceShape);

    int nextPiece{GetRandomValue(0, 6)};
    Vector2 nextPiecePos{15, 0};
    int nextPieceShape[4][4];
    Piece::NewPiece(nextPiece, nextPieceShape);

    Piece::InitTextures(blockSize);

    SetTargetFPS(60);
    gameLoop(grid, currentPiecePos, currentPiece, currentPieceShape, nextPiecePos,nextPiece, nextPieceShape);


    Piece::UnloadTextures();
    CloseWindow();

    return 0;
}
