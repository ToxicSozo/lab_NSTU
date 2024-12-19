package routes

import (
	"net/http"
	"security-quiz/handlers"
)

func SetupRoutes() {
	http.HandleFunc("/", handlers.HomeHandler)
	http.HandleFunc("/login", handlers.LoginHandler)
	http.HandleFunc("/quiz", handlers.QuizHandler)
	http.HandleFunc("/results", handlers.ResultsHandler)
	http.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("static"))))
}
