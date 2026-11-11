# overview
---
A helper program to visualize the map of worlds in browser.  

I think the move is to have the `layout.txt` file be a source of truth for the tool and place the tiles and load the tiles all in two calls. 

## todo
- [x] serve over port 8080
- [~] read `rsc` files
  - [ ] one more function in the mapfiles main.go. Needs to read one tile file into a 2D grid of chars. 
- [ ] work on tiles/main.go
  - [ ] translate function takes Ascii chars into Tile struct. 
  - [ ] Assemble function that allows for rendering actual blocks. 
- [ ] translate the files from ASCII to proper tiles
- [ ] render in browser
- [x] create layout.txt for wedding level
- [ ] STRETCH - drag and drop? Auto edit placement? 
