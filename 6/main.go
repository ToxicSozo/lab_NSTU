package main

import (
	"net/http"
	"routes"
)

func main() {
	routes.SetupRoutes()
	http.ListenAndServe(":8080", nil)
}
