package types

import "errors"

type Lobby struct {
	OwnerId   string
	LobbyId   string
	LobbyName string
	Users     map[string]interface{}
}

func NewLobby(ownerId string, lobbyId string, lobbyName string) Lobby {
	users := make(map[string]interface{}, 1)
	return Lobby{
		OwnerId:   ownerId,
		LobbyId:   lobbyId,
		LobbyName: lobbyName,
		Users:     users,
	}
}

func (lobby Lobby) AddUser(userId string) error {
	_, exists := lobby.Users[userId]
	if exists {
		return errors.New("user already exists in lobby")
	}

	lobby.Users[userId] = struct{}{}
	return nil
}

func (lobby Lobby) RemoveUser(userId string) error {
	_, exists := lobby.Users[userId]
	if !exists {
		return errors.New("user was not in lobby")
	}

	delete(lobby.Users, userId)
	return nil
}