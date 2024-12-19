package models

type User struct {
	ID       int
	Username string
	Password string
}

func GetUserByUsername(username string) (*User, error) {
	// Логика для получения пользователя из базы данных
	return &User{ID: 1, Username: "admin", Password: "password"}, nil
}
