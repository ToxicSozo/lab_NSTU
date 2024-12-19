package handlers

import (
	"html/template"
	"net/http"
)

func ResultsHandler(w http.ResponseWriter, r *http.Request) {
	// Обработка результатов теста
	tmpl := template.Must(template.ParseFiles("templates/results.html"))
	tmpl.Execute(w, nil)
}
