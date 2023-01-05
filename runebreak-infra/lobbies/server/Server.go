package server

import (
	"context"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/data/accounts/accounts_provider"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/lobbiesmanager"
	lobbiesPbs "github.com/GutpunchGames/Runebreak/runebreak-infra/protos/lobbies"
	"github.com/hashicorp/go-hclog"
)

type LobbiesServer struct {
	Logger hclog.Logger
	accountsProvider accounts_provider.AccountsProvider
	lobbiesManager *lobbiesmanager.LobbiesManager
	lobbiesPbs.UnimplementedLobbiesServer
}

func NewServer(l hclog.Logger) *LobbiesServer {
	// accountsProvider := accounts_provider.NewAccountsProvider(tLogger)
	lobbiesManager := lobbiesmanager.NewLobbiesManager(l)
	return &LobbiesServer{
		Logger: l,
		accountsProvider: nil,
		lobbiesManager: lobbiesManager,
		UnimplementedLobbiesServer: lobbiesPbs.UnimplementedLobbiesServer{},
	}
}

func (server LobbiesServer) Create(ctx context.Context, req *lobbiesPbs.CreateLobbyRequest) (*lobbiesPbs.Lobby, error) {
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

func (server LobbiesServer) Leave(ctx context.Context, req *lobbiesPbs.LeaveLobbyRequest) (*lobbiesPbs.LeaveLobbyResponse, error) {
	server.lobbiesManager.LeaveLobby(req.LobbyId, req.UserId)
	return &lobbiesPbs.LeaveLobbyResponse{}, nil
}

func (server LobbiesServer) GetLobby(ctx context.Context, req *lobbiesPbs.GetLobbyRequest) (*lobbiesPbs.Lobby, error) {
	lobby, err := server.lobbiesManager.GetLobby(req.LobbyId)

	if err != nil {
		return nil, err
	}

	lobbyResp := lobbiesPbs.Lobby{}
	lobbyResp.LobbyId = lobby.LobbyId
	lobbyResp.LobbyName = lobby.LobbyName
	lobbyResp.OwnerId = lobby.OwnerId
	lobbyResp.Users = []*lobbiesPbs.User{}

	return &lobbyResp, nil
}

func (server LobbiesServer) GetAllLobbies(ctx context.Context, req *lobbiesPbs.GetAllLobbiesRequest) (*lobbiesPbs.GetAllLobbiesResponse, error) {
	lobbies, err := server.lobbiesManager.GetAllLobbies()
	if err != nil {
		return nil, err
	}

	lobbiesRpcResp := make([]*lobbiesPbs.Lobby, 0)
	for _, lobby := range lobbies {
		rpcLobby := lobbiesPbs.Lobby{}
		rpcLobby.LobbyId = lobby.LobbyId
		rpcLobby.LobbyName = lobby.LobbyName
		rpcLobby.OwnerId = lobby.OwnerId
		rpcLobby.Users = []*lobbiesPbs.User{}

		lobbiesRpcResp = append(lobbiesRpcResp, &rpcLobby)
	}

	return &lobbiesPbs.GetAllLobbiesResponse{Lobbies: lobbiesRpcResp}, nil
}