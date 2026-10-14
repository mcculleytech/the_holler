//
// Created by alex mcculley on 10/13/26.
//
#include "player.h"
#include "map.h"

#define MOVE_DELAY 0.15f

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
