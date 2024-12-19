package models

type Question struct {
	ID      int
	Text    string
	Options []string
	Answer  string
}

func GetQuestions() ([]Question, error) {
	// Здесь можно добавить логику для получения вопросов из базы данных
	return []Question{
		{ID: 1, Text: "Что такое SQL-инъекция?", Options: []string{"A", "B", "C"}, Answer: "A"},
		{ID: 2, Text: "Как защититься от CSRF?", Options: []string{"A", "B", "C"}, Answer: "B"},
	}, nil
}
