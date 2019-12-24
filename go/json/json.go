package main

import (
	"fmt"
	"encoding/json"
)

type Msg1 struct {
	Msg string
	Id int64
}

func main() {
	raw_data := []byte("{\"msg\": \"Hello World!\", \"id\": 12345}")
	decoded := Msg1{}
	err := json.Unmarshal(raw_data, &decoded)

	if (err != nil) {
		fmt.Printf("Failed: %s\n", err)
	}

	fmt.Println(decoded.Msg, decoded.Id)
	encoded, _ := json.Marshal(&decoded)
	fmt.Println(string(encoded))
}
