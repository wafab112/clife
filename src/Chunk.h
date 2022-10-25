#ifndef CHUNK_H
#define CHUNK_H

#include "int_types.h"
#include "Vector.h"

/**
 *
 */
class Chunk {
private:
    bool& cell_at_pos(i64 x, i64 y);

public:
    bool* array;

    vec2<i64> pos;

    Chunk(i64 posX, i64 posY);
    ~Chunk();

    i64 index();
    u8 check_borders();

    void clear();
    void wake(i64 x, i64 y);
    void kill(i64 x, i64 y);

    // just for test cases.
    void render();

    i64 number_of_awake_cells();
};

enum Chunk_Border_Bit {
    TOP = 0b00000001,
    RIGHT = 0b00000010,
    BOTTOM = 0b00000100,
    LEFT = 0b00001000,
};

#endif
