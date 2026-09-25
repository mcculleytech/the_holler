#include "raylib.h"

// link to raylib docs: https://www.raylib.com/

// --- BEGIN MAP WORK
//  MAP  TODO: 
//  - [ ] draw the map 
//  - [ ] split map into header file
//  - [ ] create map prototype system for faster iteration
//  - [ ] consider scaling? screen size and map? fullscreen?

#define TILE_SIZE 32
#define MAP_W 25
#define MAP_H 14


// enum of tile type used for the array access in the tile_defs array.
typedef enum {
  TILE_FLOOR,
  TILE_WALL,
  TILE_COUNT // <- NEW Tile types MUST be above this entry. This is used for the size of the array below the TileProps Table.
} TileType;

// struct of properties for each type of tile
typedef struct {
  Color color;
  bool  solid;
} TileProps;

// init an array of struct type TileProps using the TILE_COUNT as the size of the array.
static const TileProps tile_defs[TILE_COUNT] = {
  [TILE_FLOOR] = { LIGHTGRAY, false},
  [TILE_WALL]  = {DARKGRAY, true},
};

// --- END MAP WORK

int main(void){

  // screen info
  const int screenWidth  = 800;
  const int screenHeight = 448;

  InitWindow(screenWidth, screenHeight, "the holler");

  // player attributes
  Vector2 playerPosition = { (float)screenWidth/2, (float)screenHeight/2};
  Vector2 playerSize = { 32.0f, 32.0f };

  SetTargetFPS(60);

  // main game loop
  while (!WindowShouldClose()) {

    // update vars
    //
    if (IsKeyDown(KEY_RIGHT)) playerPosition.x  += 2.0f;
    if (IsKeyDown(KEY_LEFT)) playerPosition.x   -= 2.0f;
    if (IsKeyDown(KEY_UP)) playerPosition.y     -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) playerPosition.y   += 2.0f;
    
    // draw
    //
    BeginDrawing();

      ClearBackground(RAYWHITE);


      DrawRectangleV(playerPosition, playerSize, tile_defs[TILE_FLOOR].color);

    EndDrawing();

  }

  CloseWindow();

  return 0;

}
