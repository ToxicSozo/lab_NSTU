package db

import (
	"security-quiz/models"

	"gorm.io/driver/sqlite"
	"gorm.io/gorm"
)

var DB *gorm.DB

func InitDB() {
	db, err := gorm.Open(sqlite.Open("test.db"), &gorm.Config{})
	if err != nil {
		panic("Не удалось подключиться к базе данных")
	}
	DB = db
	db.AutoMigrate(&models.User{}, &models.Question{})
}
