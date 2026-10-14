#ifndef HOLLER_MAP_H
#define HOLLER_MAP_H
// note that the header file holds things that callers need. Whatever is left over is held in the c file.

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
  TILE_COUNT // <- NEW Tile types MUST be above this entry. This is used for the size of the array below the TileProps Table.
} TileType;

// the following functions are placeholders filled in by the map.c file. Note that they are not static in that file because they are called in main.
void MapLoadTest(void);
void DrawMap(void);
bool MapIsSolid(int x, int y);

#endif
