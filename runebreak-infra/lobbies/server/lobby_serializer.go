package server

import (
	"encoding/json"

	lobbiesPbs "github.com/GutpunchGames/Runebreak/runebreak-infra/protos/lobbies"
)

func serializeLobby(lobby *lobbiesPbs.Lobby) ([]byte, error) {
	return json.Marshal(lobby)
}