//
// Created by alex mcculley on 10/13/26.
//

#ifndef THE_HOLLER_PLAYER_H
#define THE_HOLLER_PLAYER_H

#include "raylib.h"

// Player struct to define a given player state
typedef struct {
    int tileX, tileY;
    Vector2 pixelPos;
    Vector2 size;
    float moveTimer;
} Player;

void PlayerMove(Player *p, float deltaTime);

#endif //THE_HOLLER_PLAYER_H
