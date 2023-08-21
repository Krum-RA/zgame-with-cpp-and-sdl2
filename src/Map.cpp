#include "Map.h"
#include "Game.hpp"
#include <fstream>
#include "ECS.h"
#include "Components.h"

extern Manager manager;

Map::Map(std::string tID, int mapscale, int tilesize) : texID(tID), mscale(mapscale), tsize(tilesize)
{
    scaledsize = mapscale * tilesize;
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    LoadTiles(path, sizeX, sizeY);
    LoadColliders(path, sizeX, sizeY);
}

void Map::LoadTiles(std::string path, int sizeX, int sizeY)
{
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            mapFile.get(c);
            srcY = atoi(&c) * tsize;
            mapFile.get(c);
            srcX = atoi(&c) * tsize;
            AddTile(srcX, srcY, j * scaledsize, i * scaledsize);
            mapFile.ignore();
        }
        mapFile.ignore(); // Ignore the line break
    }

    mapFile.close();
}

void Map::LoadColliders(std::string path, int sizeX, int sizeY)
{
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    // Skip the lines containing tiles
    for (int i = 0; i < sizeY; i++)
    {
        mapFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Load the colliders around the map
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            if (i == 0 || i == sizeY - 1 || j == 0 || j == sizeX - 1)
            {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", j * scaledsize, i * scaledsize, scaledsize);
                tcol.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }
        mapFile.ignore(); // Ignore the line break
    }

    mapFile.close();
}


void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tsize, mscale, texID);
    tile.addGroup(Game::groupMap);
}

int Map::GetTileSize()
{
    return scaledsize;
}
