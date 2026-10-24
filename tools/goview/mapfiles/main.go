// Package mapfiles handles reading the files to render into the web browser
package mapfiles

import (
	"log"
	"os"
)

func ReadMapFile(fp string) string {
	err := os.Chdir("../../rsc/maps")
	if err != nil {
		log.Fatal(err)
	}

	content, err := os.ReadFile(fp)
	if err != nil {
		log.Fatal(err)
	}

	return string(content)
}
