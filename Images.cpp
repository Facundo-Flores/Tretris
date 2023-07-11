//
// Created by fkflo on 8/7/2023.
//

#include "Images.h"
Texture2D GenerateSquareTexture(Color color, int blockSize) {
    Image squareImage = GenImageColor(blockSize, blockSize, color);
    Texture2D  squareTexture = LoadTextureFromImage(squareImage);
    UnloadImage(squareImage);

    return squareTexture;
}