#include "raylib.h"

// link to raylib docs: https://www.raylib.com/

// --- BEGIN MAP WORK
//  MAP  TODO: 
//  - [x] draw the map 
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
  char  symbol;
} TileProps;


// test map - player would be unable to move off this map
static const char *test_map[MAP_H] = {
  "############.############",
  "#.......................#",
  "#.......................#",
  "#.......................#",
  "#.......................#",
  "#.......................#",
  "#.......................#",
  "#.......................#",
  "#.......................#",
  "#.......................#",
  "#.......................#",
  "#.......................#",
  "#.......................#",
  "#########################"

};

// init an array of struct type TileProps using the TILE_COUNT as the size of the array.
static const TileProps tile_defs[TILE_COUNT] = {
  [TILE_FLOOR] = { PURPLE, false, '.'},
  [TILE_WALL]  = { DARKGRAY, true, '#'},
};

// init a manually indexed flat array.
static TileType map[MAP_W * MAP_H];

// Accessor Function for returning an address of a given tile - we can then further access the properties of the tile from here.
TileType *TileAt(TileType *m, int x, int y) {
  return &m[y * MAP_W + x];
}

// load TitleType from ascii char
TileType TileFromChar(char c) {
  for (int i = 0; i < TILE_COUNT; i++) {
    if (tile_defs[i].symbol == c) 
      return (TileType)i;
  }
  return TILE_FLOOR;
}

// draw map
void DrawMap(void) {
  for (int y = 0; y < MAP_H; y++) {
    for (int x = 0; x <MAP_W; x++) {
      DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, tile_defs[(*TileAt(map, x, y))].color);
    }
  }
}

void LoadMapFromASCII(TileType *m, const char **rows) {
  for (int y = 0; y < MAP_H; y++)
    for (int x = 0; x < MAP_W; x++)
      *TileAt(m, x, y) = TileFromChar(rows[y][x]);
}


// --- END MAP WORK

int main(void){

  // screen info
  const int screenWidth  = 800;
  const int screenHeight = 448;

  InitWindow(screenWidth, screenHeight, "the holler");
  // not sure if I love the way this would scale
  // TODO:
  // - [ ] investigate better scaled solutions for drawing map.
  LoadMapFromASCII(map, test_map);

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

      DrawMap();

      DrawRectangleV(playerPosition, playerSize, WHITE);

    EndDrawing();

  }

  CloseWindow();

  return 0;

}
