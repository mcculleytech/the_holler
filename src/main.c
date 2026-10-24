#include "map.h"
#include "player.h"
#include "raylib.h"

// link to raylib docs: https://www.raylib.com/

int main(void) {

  // screen info
  const int screenWidth = 800;
  const int screenHeight = 448;

  InitWindow(screenWidth, screenHeight, "the holler");
  // not sure if I love the way this would scale
  // TODO:
  // - [ ] investigate better scaled solutions for drawing map.
  // - [ ] wire directory in rsc - right now only works from bin. Fine for
  // testing

  if (!MapLoadFromFile("../rsc/test_map.txt")) {
    MapLoadTest();
  }

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
