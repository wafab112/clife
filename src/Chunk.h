#ifndef CHUNK_H
#define CHUNK_H

#include "int_types.h"
#include "Vector.h"

/**
 * @brief A 8x8 chunk of either dead or awake cells.
 * Is a chunk of cells within a grid. Cells are just boolean values (true = awake, false = dead).
 * Has a 2d-position within a grid.
 * @see Grid
 */
class Chunk {
private:
    /**
     * @brief Retrieves a reference to the cell with the given x and y coordinates within the chunk.
     * @param[in] x The x-coordinate within the chunk.
     * @param[in] y The y-coordinate within the chunk.
     * @return A reference to the wanted cell.
     */
    bool& cell_at_pos(i64 x, i64 y);

public:
    /**
     * @brief The actual pointer to the array of cells.
     */
    bool* array;

    /**
     * @brief The 2d-position within a grid.
     */
    vec2<i64> pos;

    /**
     * @brief Initializes the chunk at the given 2d-position within a grid.
     */
    Chunk(i64 posX, i64 posY);
    ~Chunk();

    /**
     * @brief Calculates an index, that can be sorted after in a Grid.
     * Maybe not needed.
     */
    i64 index();

    /**
     * @brief Checks which of the chunk borders have a awake cell.
     * @returns A u8 which 4 least significant bits give, whether the borders have awake cells.
     * @see ChunkBorderBit
     */
    u8 check_borders();

    /**
     * @brief Kills every cell in a chunk
     */
    void clear();

    /**
     * @brief Wakes up the cell at the given coords within a chunk.
     * @param x The x-coord of the cell.
     * @param y The y-coord of the cell.
     */
    void wake(i64 x, i64 y);

    /**
     * @brief Kills the cell at the given coords within a chunk.
     * @param x The x-coord of the cell.
     * @param y The y-coord of the cell.
     */
    void kill(i64 x, i64 y);

    /**
     * @brief Renders the chunk in cout.
     * @deprecated OpenGL used for rendering.
     */
    void render();

    /**
     * @brief Counts the number of awake cells within a chunk.
     * @return Number of awake cells.
     */
    i64 number_of_awake_cells();

    /**
     * @enum ChunkBorderBit
     * @brief Specifies which chunkborder has awake cells.
     * Using bitwise OR you can combine those borders to specify whether multiple chunkborders have living cells.
     * @example Top-Left-Border 0b00001001 tells you, that the top and the left of the chunk have borders with living cells.
     */
    enum ChunkBorderBit {
        TOP = 0b00000001,
        RIGHT = 0b00000010,
        BOTTOM = 0b00000100,
        LEFT = 0b00001000,
    };
};

#endif
