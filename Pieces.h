//
// Created by fkflo on 7/7/2023.
//

#ifndef CLASSYCLASH_PIECES_H
#define CLASSYCLASH_PIECES_H

const int TRETROMINOES[7][4][4] {
        { // I
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
        },
        { // O
                {0, 0, 0, 0},
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0}
        },
        { // T
                {0, 0, 0, 0},
                {0, 1, 1, 1},
                {0, 0, 1, 0},
                {0, 0, 0, 0}
        },
        { // S
                {0, 0, 0, 0},
                {0, 0, 1, 1},
                {0, 1, 1, 0},
                {0, 0, 0, 0}
        },
        { // Z
                {0, 0, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 1, 1},
                {0, 0, 0, 0}
        },
        { // J
                {0, 0, 0, 0},
                {0, 1, 1, 1},
                {0, 0, 0, 1},
                {0, 0, 0, 0}
        },
        { // L
                {0, 0, 0, 0},
                {0, 1, 1, 1},
                {0, 1, 0, 0},
                {0, 0, 0, 0}
        }
};
#endif //CLASSYCLASH_PIECES_H
