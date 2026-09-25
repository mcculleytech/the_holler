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

Thinking about having a file that defines structs for tiles. Need to think about how to place the blocks. 


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
- [~] develop a tiling system for rendering map

### ToDo - movement
- [ ] implement shift hold speed up.
- [ ] attack key
- [ ] defend
- [ ] wasd based movement(?) 

### ToDo - tiling
- [x] create enum of TileTypes
- [x] create struct of TileProps
- [x] craft array of tile_defs
- [ ] draw map
- [ ] standalone header file
- [ ] develop a prototype system for map generation.
