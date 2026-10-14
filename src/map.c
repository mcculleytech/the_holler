#include "map.h"

// struct of properties for each type of tile
typedef struct {
  Color color;
  bool solid;
  char symbol;
} TileProps;

// test map - player would be unable to move off this map. This will ultimately
// be replaced with a function that reads txt files from rsc.
static const char *test_map[MAP_H] = {
    "#########################", "#.......................#",
    "#.......................#", "#.......................#",
    "#.......................#", "#.......................#",
    "#.......................#", "#.......................#",
    "#.......................#", "#.......................#",
    "#.......................#", "#.......................#",
    "#.......................#", "#########################"};

// init an array of struct type TileProps using the TILE_COUNT as the size of
// the array.
static const TileProps tile_defs[TILE_COUNT] = {
    [TILE_FLOOR] = {LIGHTGRAY, false, '.'},
    [TILE_WALL] = {DARKGRAY, true, '#'},
};

// init a manually indexed flat array.
static TileType map[MAP_W * MAP_H];

// Accessor Function for returning an address of a given tile - we can then
// further access the properties of the tile from here.
static TileType *TileAt(TileType *m, int x, int y) { return &m[y * MAP_W + x]; }

// load TitleType from ascii char
static TileType TileFromChar(char c) {
  for (int i = 0; i < TILE_COUNT; i++) {
    if (tile_defs[i].symbol == c)
      return (TileType)i;
  }
  return TILE_FLOOR;
}

// draw map
void DrawMap(void) {
  for (int y = 0; y < MAP_H; y++) {
    for (int x = 0; x < MAP_W; x++) {
      DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                    tile_defs[(*TileAt(map, x, y))].color);
    }
  }
}

static void LoadMapFromASCII(TileType *m, const char **rows) {
  for (int y = 0; y < MAP_H; y++)
    for (int x = 0; x < MAP_W; x++)
      *TileAt(m, x, y) = TileFromChar(rows[y][x]);
}

void MapLoadTest(void) { LoadMapFromASCII(map, test_map); }

bool MapIsSolid(int x, int y) {
  if (x < 0 || x >= MAP_W || y < 0 || y >= MAP_H)
    return true;
  return tile_defs[*TileAt(map, x, y)].solid;
}
