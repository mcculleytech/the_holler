#include "map.h"
#include "raylib.h"

// link to raylib docs: https://www.raylib.com/

// --- START MOVEMENT WORK

const float MOVE_DELAY = 0.15f;

// Player struct to define a given player state
typedef struct {
  int tileX, tileY;
  Vector2 pixelPos;
  Vector2 size;
  float moveTimer;
} Player;

void PlayerMove(Player *p, float deltaTime) {
  // tick down the movement cooldown
  p->moveTimer -= deltaTime;

  // determine direction from input
  int dx = 0, dy = 0;

  if (IsKeyPressed(KEY_RIGHT) || (IsKeyDown(KEY_RIGHT) && p->moveTimer <= 0.0f))
    dx = 1;
  else if (IsKeyPressed(KEY_LEFT) ||
           (IsKeyDown(KEY_LEFT) && p->moveTimer <= 0.0f))
    dx = -1;
  else if (IsKeyPressed(KEY_UP) || (IsKeyDown(KEY_UP) && p->moveTimer <= 0.0f))
    dy = -1;
  else if (IsKeyPressed(KEY_DOWN) ||
           (IsKeyDown(KEY_DOWN) && p->moveTimer <= 0.0f))
    dy = 1;

  // no valid input return
  if (dx == 0 && dy == 0)
    return;

  // calc target tile
  int targetX = p->tileX + dx;
  int targetY = p->tileY + dy;

  // collision check baked in
  if (MapIsSolid(targetX, targetY))
    return;

  // actually move
  p->tileX = targetX;
  p->tileY = targetY;
  p->pixelPos.x = p->tileX * TILE_SIZE;
  p->pixelPos.y = p->tileY * TILE_SIZE;
  p->moveTimer = MOVE_DELAY;
}

// -- END MOVEMENT WORK

int main(void) {

  // screen info
  const int screenWidth = 800;
  const int screenHeight = 448;

  InitWindow(screenWidth, screenHeight, "the holler");
  // not sure if I love the way this would scale
  // TODO:
  // - [ ] investigate better scaled solutions for drawing map.

  MapLoadTest();

  // player attributes
  Player player = {
      .tileX = MAP_W / 2,
      .tileY = MAP_H / 2,
      .pixelPos = {(MAP_W / 2.0) * TILE_SIZE, (MAP_H / 2.0) * TILE_SIZE},
      .size = {32.0f, 32.0f},
      .moveTimer = 0.0f};

  SetTargetFPS(60);

  // main game loop
  while (!WindowShouldClose()) {

    // update vars
    PlayerMove(&player, GetFrameTime());

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
