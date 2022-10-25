#include "doctest.h"
#include "Chunk.h"

TEST_SUITE("chunk test borders") {
    TEST_CASE("none") {
        Chunk c{0, 0};
        u8 borders{};

        c.wake(1, 1);

        borders = 0;

        CHECK(c.check_borders() == borders);
    }

    TEST_CASE("one border") {
        Chunk c{0, 0};
        u8 borders{};

        SUBCASE("top") {
            c.wake(1, 0);

            borders = Chunk_Border_Bit::TOP;

            CHECK(c.check_borders() == borders);
        }
        c.clear();

        SUBCASE("right") {
            c.wake(7, 1);

            borders = Chunk_Border_Bit::RIGHT;

            CHECK(c.check_borders() == borders);
        }
        c.clear();

        SUBCASE("bottom") {
            c.wake(1, 7);

            borders = Chunk_Border_Bit::BOTTOM;

            CHECK(c.check_borders() == borders);
        }
        c.clear();

        SUBCASE("left") {
            c.wake(0, 1);

            borders = Chunk_Border_Bit::LEFT;

            CHECK(c.check_borders() == borders);
        }
        c.clear();
    }
}
