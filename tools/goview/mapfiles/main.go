// Package mapfiles handles reading the files to render into the web browser
package mapfiles

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

// craft struct to be returned by the function that maps the tile LOCATION
// Noted here but maybe not relevant to this file, I need color defs on tiles. That's really all I need.

type TileCoordinates struct {
	Filename string
	X        int
	Y        int
}

// ReadLayout is made explicitly for the layout.
func ReadLayout(fp string) []TileCoordinates {
	err := os.Chdir("../../rsc/maps")
	if err != nil {
		log.Fatal(err)
	}

	content, err := os.Open(fp)
	if err != nil {
		log.Fatalf("[!] failed to open file %s", err)
	}
	defer content.Close()

	scanner := bufio.NewScanner(content)

	var tileMap []TileCoordinates

	for scanner.Scan() {
		var tileCoords TileCoordinates

		line := scanner.Text()

		if strings.ContainsRune(line, '#') || line == "" {
			continue
		} else {
			tokens := strings.Fields(line)
			if len(tokens) != 3 {
				continue // need to make this a proper error
			}
			tileCoords.Filename = tokens[0]
			tileCoords.X, err = strconv.Atoi(tokens[1])
			if err != nil {
				// need to err
				log.Fatalf("[!] Error reading layout.txt - converting ascii to text\n")
			}
			tileCoords.Y, err = strconv.Atoi(tokens[2])
			if err != nil {
				// need to err
				log.Fatalf("[!] Error reading layout.txt - converting ascii to text\n")
			}
			tileMap = append(tileMap, tileCoords)
		}
	}

	if err := scanner.Err(); err != nil {
		fmt.Fprintln(os.Stderr, "reading standard input:", err)
	}

	return tileMap
}

// ReadTileMap function will return an array of strings raw ascii, will break on unicode.
func ReadTileMap(fp string) ([]string, error) {
	file, err := os.Open(fp)
	if err != nil {
		return nil, err
	}

	defer file.Close()

	var lines []string
	scanner := bufio.NewScanner(file)

	// scan line by line
	for scanner.Scan() {
		lines = append(lines, scanner.Text()) // byte conversion to string
	}

	expectedWidth := len(lines[0])
	for i, line := range lines {
		if len(line) != expectedWidth {
			return nil, fmt.Errorf("line %d has width %d, expected %d", i, len(line), expectedWidth)
		}
	}

	// check for errors during scanning
	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return lines, nil
}
