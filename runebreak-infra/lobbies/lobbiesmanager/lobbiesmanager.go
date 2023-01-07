package lobbiesmanager

import (
	"errors"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/types"
	"github.com/google/uuid"
	"github.com/hashicorp/go-hclog"
)

type LobbiesManager struct {
	Logger hclog.Logger
	lobbies map[string]*types.Lobby
}

func NewLobbiesManager(l hclog.Logger) *LobbiesManager {
	return &LobbiesManager{
		Logger: l,
		lobbies: make(map[string]*types.Lobby),
	}
}

func (manager LobbiesManager) CreateLobby(ownerId string, lobbyName string) (*types.Lobby, error) {
	err := validateLobbyName(lobbyName)
	if (err != nil) {
		return nil, err
	}
	// todo: ensure ID uniqueness. ring buffer of ints?
	lobbyId := uuid.NewString()
	lobby := types.NewLobby(ownerId, lobbyId, lobbyName)
	lobby.AddUser(ownerId)
	manager.lobbies[lobbyId] = &lobby
	return &lobby, nil
}

func (manager LobbiesManager) JoinLobby(lobbyId string, userId string) (*types.Lobby, error) {
	lobby, exists := manager.lobbies[lobbyId]
	if !exists {
		return nil, errors.New("lobby does not exist")
	}

	err := lobby.AddUser(userId)
	if (err != nil) {
		return nil, err
	}

	return lobby, nil
}

func (manager LobbiesManager) LeaveLobby(lobbyId string, userId string) (*types.Lobby, error) {
	lobby, exists := manager.lobbies[lobbyId]
	if !exists {
		return nil, errors.New("lobby does not exist")
	}

	err := lobby.RemoveUser(userId)
	if (err != nil) {
		return nil, err
	}

	if (len(lobby.Users) == 0) {
		delete(manager.lobbies, lobby.LobbyId)
		return nil, nil
	} else {
		return lobby, nil
	}
}

func (manager LobbiesManager) GetLobby(lobbyId string) (*types.Lobby, error) {
	lobby, exists := manager.lobbies[lobbyId]
	if !exists {
		return nil, errors.New("lobby does not exist")
	}
	return lobby, nil
}

func (manager LobbiesManager) GetAllLobbies() ([]*types.Lobby, error) {
	var lobbies []*types.Lobby 
	for _, lobby := range manager.lobbies {
		lobbies = append(lobbies, lobby)
	}

	return lobbies, nil
}

func validateLobbyName(lobbyName string) error {
	length := len(lobbyName)
	if (length < 2 || length > 32) {
		return errors.New("lobby name must be between 2 and 32 characters")
	}

	return nil
}