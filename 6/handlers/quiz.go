package handlers

import (
	"html/template"
	"models"
	"net/http"
)

func QuizHandler(w http.ResponseWriter, r *http.Request) {
	questions, _ := models.GetQuestions()
	tmpl := template.Must(template.ParseFiles("templates/quiz.html"))
	tmpl.Execute(w, questions)
}
