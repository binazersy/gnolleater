package main

import (
	"database/sql"
)

func init() {
	sql.Register("postgres", new (PostgresDriver))
}

func main() {
	sql.Open("postgres", "mydb")
}
