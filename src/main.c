#include "raylib.h"


int main(void){

  const int screenWidth  = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "the holler");

  Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2};

  SetTargetFPS(60);

  // main game loop
  while (!WindowShouldClose()) {

    // update vars
    //
    if (IsKeyDown(KEY_RIGHT)) ballPosition.x  += 2.0f;
    if (IsKeyDown(KEY_LEFT)) ballPosition.x   -= 2.0f;
    if (IsKeyDown(KEY_UP)) ballPosition.y     -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) ballPosition.y   += 2.0f;
    
    // draw
    //
    BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawText("and ye shall know the truth and truth will make you stranger...", 0, 200, 20, LIGHTGRAY);

      DrawCircleV(ballPosition, 50, MAROON);

    EndDrawing();

  }

  CloseWindow();

  return 0;

}
