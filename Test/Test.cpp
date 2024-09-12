#include "gtest/gtest.h"
#include "../src/HPP/Tile.hpp"
#include <iostream>

// Test 1
TEST(TileTest, Constructor){
    Tile tile = Tile(0, 0, 0, 0, 2);
    EXPECT_EQ(tile.getValue(), 2);
    EXPECT_EQ(tile.getTexturePath(), "images/2.jpg");
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}