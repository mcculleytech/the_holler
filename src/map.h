#ifndef HOLLER_MAP
#define HOLLER_MAP

#include "raylib.h"

#define TILE_SIZE 32
#define MAP_W 25
#define MAP_H 14

//  MAP  TODO:
//  - [x] draw the map
//  - [x] split map into header file
//  - [ ] create map prototype system for faster iteration
//  - [ ] consider scaling? screen size and map? fullscreen?

// enum of tile type used for the array access in the tile_defs array.
typedef enum {
  TILE_FLOOR,
  TILE_WALL,
  TILE_COUNT // <- NEW Tile types MUST be above this entry. This is used for the
             // size of the array below the TileProps Table.
} TileType;

void MapLoadTest(void);
void DrawMap(void);
bool MapIsSolid(int x, int y);

#endif
