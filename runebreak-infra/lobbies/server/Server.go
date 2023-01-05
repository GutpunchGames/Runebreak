package server

import (
	"context"
	"log"
	"os"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/data/accounts/accounts_provider"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/lobbiesmanager"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/types"
	lobbiesPbs "github.com/GutpunchGames/Runebreak/runebreak-infra/protos/lobbies"
	"github.com/google/uuid"
	"github.com/hashicorp/go-hclog"
)

type LobbiesServer struct {
	Logger hclog.Logger
	accountsProvider accounts_provider.AccountsProvider
	lobbiesManager lobbiesmanager.LobbiesManager
	lobbiesPbs.UnimplementedLobbiesServer
}

func NewServer(l hclog.Logger) *LobbiesServer {
	tLogger := log.New(os.Stdout, "lobbies server", log.LstdFlags)
	accountsProvider := accounts_provider.NewAccountsProvider(tLogger)
	return &LobbiesServer{Logger: l, accountsProvider: accountsProvider, UnimplementedLobbiesServer: lobbiesPbs.UnimplementedLobbiesServer{}}
}

func (server LobbiesServer) Create(ctx context.Context, req *lobbiesPbs.CreateLobbyRequest) (*lobbiesPbs.Lobby, error) {
	server.Logger.Info("Handle Create", "username", req.UserId, "lobby name", req.LobbyName)
	lobby, err := server.lobbiesManager.CreateLobby(req.UserId, req.LobbyName)
	if err != nil {
		return nil, err
	}

	if err != nil {
		return nil, err
	}

	// todo: make this a method for converting lobby record type to protobuf type
	lobbyResp := lobbiesPbs.Lobby{}
	lobbyResp.LobbyId = lobby.LobbyId
	lobbyResp.LobbyName = lobby.LobbyName
	lobbyResp.OwnerId = lobby.OwnerId
	lobbyResp.Users = []*lobbiesPbs.User{}

	return &lobbyResp, nil
}

func (server LobbiesServer) Join(ctx context.Context, req *lobbiesPbs.JoinLobbyRequest) (*lobbiesPbs.Lobby, error) {
	server.Logger.Info("Handle Join", "username", req.UserId, "lobby id", req.LobbyId)
	lobby, err := server.lobbiesManager.JoinLobby(req.LobbyId, req.UserId)

	if (err != nil) {
		return nil, err
	}

	lobbyResp := lobbiesPbs.Lobby{}
	lobbyResp.LobbyId = lobby.LobbyId
	lobbyResp.LobbyName = lobby.LobbyName
	lobbyResp.OwnerId = lobby.OwnerId
	lobbyResp.Users = []*lobbiesPbs.User{}

	return &lobbyResp, nil
}

func (server LobbiesServer) GetLobby(ctx context.Context, req *lobbiesPbs.GetLobbyRequest) (*lobbiesPbs.Lobby, error) {
	return nil, nil
}

func (server LobbiesServer) GetAllLobbies(ctx context.Context, req *lobbiesPbs.GetAllLobbiesRequest) (*lobbiesPbs.GetAllLobbiesResponse, error) {
	return nil, nil
}