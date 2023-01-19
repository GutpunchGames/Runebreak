package types

import (
	"errors"
	"fmt"
)

type Lobby struct {
	OwnerId   string 
	LobbyId   string
	LobbyName string
	Users     []string
}

func NewLobby(ownerId string, lobbyId string, lobbyName string) Lobby {
	users := make([]string, 0)
	return Lobby{
		OwnerId:   ownerId,
		LobbyId:   lobbyId,
		LobbyName: lobbyName,
		Users:     users,
	}
}

func (lobby *Lobby) AddUser(userId string) error {
	for _, existingUserId := range lobby.Users {
		if (existingUserId == userId) {
			return errors.New("user already exists in lobby")
		}
	}

	lobby.Users = append(lobby.Users, userId)
	fmt.Printf("appended user: %s. new lobby length: %d\n", userId, len(lobby.Users))
	
	return nil
}

// todo: this RemoveUser function is horribly inefficient. we should keep
// some sort of ordered set.
func (lobby *Lobby) RemoveUser(userId string) error {
	for i, existingUserId := range lobby.Users {
		if (existingUserId == userId) {
			lobby.Users = append(lobby.Users[:i], lobby.Users[i+1:]...)
			return nil
		}
	}

	return errors.New("user was not in lobby")
}