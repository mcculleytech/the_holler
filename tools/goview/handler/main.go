// Package handler deals with content being served over the web server
package handler

import (
	"fmt"
	"net/http"

	"github.com/mcculleytech/the_holler/tools/goview/mapfiles"
)

func Test(w http.ResponseWriter, req *http.Request) {
	mapContent := mapfiles.ReadLayout("the-wedding/layout.txt")
	_, err := fmt.Fprint(w, mapContent)
	if err != nil {
		fmt.Println(err)
	}
}
