package main

import (
	"fmt"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/services/gateway"
)

func main() {
	fmt.Printf("%s\n", gateway.Pong())
}