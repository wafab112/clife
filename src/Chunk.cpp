#include "int_types.h"
#include "Chunk.h"
#include <stdexcept>
#include <algorithm>

// removed when using gl
#include <iostream>

i64 Chunk::index() {
    return pos.x * pos.y;
}

bool& Chunk::cell_at_pos(i64 x, i64 y) {
    if (x < 0 || x >= 8) {
        throw std::invalid_argument("x < 0 or x > 7");
    }

    if (y < 0 || y >= 8) {
        throw std::invalid_argument("y < 0 or y > 7");
    }

    return array[y * 8 + x];
}

Chunk::Chunk(i64 posX, i64 posY) {
    pos.x = posX;
    pos.y = posY;

    this->array = new bool[64];
    std::fill_n(this->array, 64, 0);
}

Chunk::~Chunk() {
    delete[] array;
}

u8 Chunk::check_borders() {
    // for x, y=0 ==> 0...7
    // for x, y=7 ==> 63-8...63
    // for y, x=0 ==> 0*8, 1*8, ..., 7*8
    // for y, x=7 ==> 0*8+7, 1*8+7, ..., 7*8+7
    u8 borders{0};
    for (int i = 0; i<8; i++) {
        if (array[i]) {
            borders |= (u8) ChunkBorderBit::TOP;
        }

        if (array[63 - i]) {
            borders |= (u8) ChunkBorderBit::BOTTOM;
        }

        if (array[i * 8]) {
            borders |= (u8) ChunkBorderBit::LEFT;
        }

        if (array[i * 8 + 7]) {
            borders |= (u8) ChunkBorderBit::RIGHT;
        }
    }

    return borders;
}

void Chunk::wake(i64 x, i64 y) {
    cell_at_pos(x, y) = true;
}

void Chunk::kill(i64 x, i64 y) {
    cell_at_pos(x, y) = false;
}

void Chunk::clear() {
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            array[i * 8 + j] = false;
        }
    }
}

void Chunk::render() {
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            if (array[i * 8 + j]) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }

            std::cout << "|";
        }
        std::cout << "\n----------------\n";
    }
}

 i64 Chunk::number_of_awake_cells() {
    i64 counter = 0;
    for (int i = 0; i< 64; i++) {
        if (array[i]) counter++;
    }
    return counter;
 }
