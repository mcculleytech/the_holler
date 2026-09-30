# overview

The goal of this repository is twofold. 

1. Gain more experience and comfortability in C.

2. Learn some game development.

---
## building the project

As of now, this project builds for MacOS on ARM.

---

## notes

### tiling

~~Thinking about having a file that defines structs for tiles. Need to think about how to place the blocks.~~

The `TileType` stores each type of tile. `TileProps` stores all the properties of the tile. `tile_defs` is a way to access the properties of given tile. 

With that in mind, we move to the map.

The map is manually indexed 1-dimensional flat array. We define the map in ASCII chars to get an idea of what it can look like. This method serves three purposes:

1. Faster visualization of maps and (hopefully) improved speed of development.

2. Version controlled map development. 

3. If I ever wanted a TUI rogue-like, I already have the maps in ASCII. 

The key to accessing any given tile in our array is via the accessor function, which will return an address to us of a given tile in the array:

```c
TileType *TileAt(TileType *m, int x, int y) {

  return &m[y * MAP_W + x];
}
```

One of the advantages of this accessor function is that it works in both directions. We can both read and write to the map via this function. 

`TileFromChar` is an import filter that translates ASCII symbols into `TileType` enum keys. Once stored, the render path separately translates those keys into colors via `tile_defs`.

`LoadMapFromASCII` iterates over a given map layout, translates the ASCII char into a `TileType` via `TileFromChar` and writes the enum key into the map array using `TileAt`. This happens one time (out of the game loop in `main`). 

`DrawMap` iterates over the same (x, y) grid, reads the `TileType` at each coordinate via `TileAt`, looks up the tile color in `tile_defs`, and draws a rectangle at corresponding pixel position. This happens every frame. 


---

## ToDo - Master

- [x] install [raylib](https://github.com/raysan5/raylib/wiki/Working-on-macOS)
- [x] build project structure.
  - [x] init the repo w/
    - [x] Makefile - basic
    - [x] src
    - [x] rsc
    - [x] bin
- [x] draw screen
- [x] draw character (circle) to screen
- [x] implement movement
- [ ] include Windows make
- [ ] include linux make
- [ ] boundaries (collisions)
- [x] develop a tiling system for rendering map

### ToDo - movement
- [ ] implement shift hold speed up.
- [ ] attack key
- [ ] defend
- [ ] wasd based movement(?) 
- [ ] implement a more snap based movement system. 

### ToDo - tiling
- [x] create enum of TileTypes
- [x] create struct of TileProps
- [x] craft array of tile_defs
- [x] draw map
- [ ] standalone header file
- [ ] develop a prototype system for map generation.
