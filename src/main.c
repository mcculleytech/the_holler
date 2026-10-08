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


// test map - player would be unable to move off this map. This will ultimately be replaced with a function that reads txt files from rsc. 
static const char *test_map[MAP_H] = {
  "#########################",
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
  [TILE_FLOOR] = { LIGHTGRAY, false, '.'},
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


// --- START MOVEMENT WORK

const float MOVE_DELAY = 0.15f;

// Player struct to define a given player state
typedef struct {
  int tileX, tileY;
  Vector2 pixelPos;
  Vector2 size;
  float moveTimer;
} Player;


// basic collision detection
static bool IsTileSolid(TileType *map, int x, int y) {
  if(x < 0 || x >= MAP_W || y < 0 || y>= MAP_H) return true;
  return tile_defs[*TileAt(map, x, y)].solid;
}

void PlayerMove(Player *p, TileType *map, float deltaTime) {
  // tick down the movement cooldown
  p->moveTimer -= deltaTime;

  // determine direction from input
  int dx = 0, dy = 0;

  if (IsKeyPressed(KEY_RIGHT) || (IsKeyDown(KEY_RIGHT) && p->moveTimer <= 0.0f))    dx = 1;
  else if (IsKeyPressed(KEY_LEFT) || (IsKeyDown(KEY_LEFT) && p->moveTimer <= 0.0f)) dx = -1;
  else if (IsKeyPressed(KEY_UP) || (IsKeyDown(KEY_UP) && p->moveTimer <= 0.0f))     dy = -1;
  else if (IsKeyPressed(KEY_DOWN) || (IsKeyDown(KEY_DOWN) && p->moveTimer <= 0.0f)) dy = 1;

  // no valid input return
  if (dx == 0 && dy == 0) return;

  // calc target tile
  int targetX = p->tileX + dx;
  int targetY = p->tileY + dy;

  // collision check baked in
  if (IsTileSolid(map, targetX, targetY)) return;
  

  //actually move
  p->tileX = targetX;
  p->tileY = targetY;
  p->pixelPos.x = p->tileX * TILE_SIZE;
  p->pixelPos.y = p->tileY * TILE_SIZE;
  p->moveTimer = MOVE_DELAY;

}


// -- END MOVEMENT WORK

int main(void){

  // screen info
  const int screenWidth  = 800;
  const int screenHeight = 448;

  InitWindow(screenWidth, screenHeight, "the holler");
  // not sure if I love the way this would scale
  // TODO:
  // - [ ] investigate better scaled solutions for drawing map.

  // the function args work because of the decay of arrays into a pointer of its first element when you pass it into a function.
  LoadMapFromASCII(map, test_map);

  // movement cooldown

  // player attributes
  Player player = {  
    .tileX = MAP_W / 2,
    .tileY = MAP_H / 2,
    .pixelPos = { (MAP_W / 2) * TILE_SIZE, (MAP_H / 2) * TILE_SIZE},
    .size = { 32.0f, 32.0f },
    .moveTimer = 0.0f
  };


  SetTargetFPS(60);

  // main game loop
  while (!WindowShouldClose()) {

    // update vars
    PlayerMove(&player, map, GetFrameTime());
    
    // draw
    BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawMap();

      DrawRectangleV(player.pixelPos, player.size, WHITE);

    EndDrawing();

  }

  CloseWindow();

  return 0;

}
