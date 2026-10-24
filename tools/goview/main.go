package main

import (
	"log"
	"net/http"

	"github.com/mcculleytech/the_holler/tools/goview/handler"
)

func main() {
	log.Print("Starting goview...")
	http.HandleFunc("/test", handler.Test)
	log.Fatal(http.ListenAndServe(":8080", nil))
}
