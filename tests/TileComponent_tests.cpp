#include "UnitTest++/UnitTest++.h"
#include "Components.h" 
#include "Game.hpp"

SUITE(TileComponentTests)
{
    TEST(TileComponent_Constructor_InitializesProperties)
    {
        int srcX = 0;
        int srcY = 0;
        int xpos = 100;
        int ypos = 200;
        int tsize = 32;
        int tscale = 2;
        std::string textureId = "tile_texture";

        TileComponent tile(srcX, srcY, xpos, ypos, tsize, tscale, textureId);

        CHECK_EQUAL(srcX, tile.srcRect.x);
        CHECK_EQUAL(srcY, tile.srcRect.y);
        CHECK_EQUAL(tsize, tile.srcRect.w);
        CHECK_EQUAL(tsize, tile.srcRect.h);

        CHECK_EQUAL(xpos, tile.destRect.x);
        CHECK_EQUAL(ypos, tile.destRect.y);
        CHECK_EQUAL(tsize * tscale, tile.destRect.w);
        CHECK_EQUAL(tsize * tscale, tile.destRect.h);

        CHECK_EQUAL(xpos, tile.position.x);
        CHECK_EQUAL(ypos, tile.position.y);
    }

    TEST(TileComponent_Update_PositionUpdates)
    {
        TileComponent tile;
        Vector2D initialPosition = tile.position;
        Game::camera.x = 50;
        Game::camera.y = 100;

        tile.update();

        CHECK_EQUAL(initialPosition.x - Game::camera.x, tile.destRect.x);
        CHECK_EQUAL(initialPosition.y - Game::camera.y, tile.destRect.y);
    }
}

