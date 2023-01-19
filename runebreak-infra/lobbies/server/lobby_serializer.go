package server

import (
	"encoding/json"

	lobbiesPbs "github.com/GutpunchGames/Runebreak/runebreak-infra/protos/lobbies"
)

type serializedLobby struct {
	LobbyId   string  `json:"lobbyId"`
	LobbyName string  `json:"lobbyName"`
	OwnerId   string  `json:"ownerId"`
	Users     []*serializedUser `json:"users"`
}

type serializedUser struct {
	UserId   string `json:"userId"`
	UserName string `json:"userName"`
}

func serializeLobby(lobby *lobbiesPbs.Lobby) ([]byte, error) {
	serializedUsers := make([]*serializedUser, 0)
	for _, user := range lobby.Users {
		serializedUsers = append(serializedUsers, &serializedUser{
			UserId: user.UserId,
			UserName: user.UserName,
		})
	}

	serialized := serializedLobby{
		LobbyId: lobby.LobbyId,
		LobbyName: lobby.LobbyName,
		OwnerId: lobby.OwnerId,
		Users: serializedUsers,
	}

	return json.Marshal(serialized)
}