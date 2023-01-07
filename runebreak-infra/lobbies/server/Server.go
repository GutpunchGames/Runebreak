package server

import (
	"context"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/accounts_provider"
	gatewaydispatcher "github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/gateway_dispatcher"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/lobbiesmanager"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/types"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/protos/gateway"
	lobbiesPbs "github.com/GutpunchGames/Runebreak/runebreak-infra/protos/lobbies"
	"github.com/hashicorp/go-hclog"
)

type LobbiesServer struct {
	Logger hclog.Logger
	accountsProvider accounts_provider.AccountsProvider
	gatewayDispatcher gatewaydispatcher.GatewayDispatcher
	lobbiesManager *lobbiesmanager.LobbiesManager
	lobbiesPbs.UnimplementedLobbiesServer
}

func NewServer(
	l hclog.Logger,
	ap accounts_provider.AccountsProvider,
  	gd gatewaydispatcher.GatewayDispatcher,
) *LobbiesServer {
	// accountsProvider := accounts_provider.NewAccountsProvider(tLogger)
	lobbiesManager := lobbiesmanager.NewLobbiesManager(l)
	return &LobbiesServer{
		Logger: l,
		accountsProvider: ap,
		gatewayDispatcher: gd,
		lobbiesManager: lobbiesManager,
		UnimplementedLobbiesServer: lobbiesPbs.UnimplementedLobbiesServer{},
	}
}

func (server LobbiesServer) Create(ctx context.Context, req *lobbiesPbs.CreateLobbyRequest) (*lobbiesPbs.Lobby, error) {
	lobby, err := server.lobbiesManager.CreateLobby(req.UserId, req.LobbyName)
	if err != nil {
		return nil, err
	}

	return server.lobbyRecordToRpcLobby(lobby)
}

func (server LobbiesServer) Join(ctx context.Context, req *lobbiesPbs.JoinLobbyRequest) (*lobbiesPbs.Lobby, error) {
	lobby, err := server.lobbiesManager.JoinLobby(req.LobbyId, req.UserId)

	if (err != nil) {
		return nil, err
	}

	// add the users to the library
	rpcLobby, err := server.lobbyRecordToRpcLobby(lobby)
	if (err != nil) {
		return nil, err
	}

	err = server.notifyLobbyUsers(rpcLobby, req.UserId)
	if (err != nil) {
		return nil, err
	}

	return rpcLobby, nil
}

func (server LobbiesServer) Leave(ctx context.Context, req *lobbiesPbs.LeaveLobbyRequest) (*lobbiesPbs.LeaveLobbyResponse, error) {
	lobby, err := server.lobbiesManager.LeaveLobby(req.LobbyId, req.UserId)
	if (err != nil) {
		return nil, err
	}

	// add the users to the library
	rpcLobby, err := server.lobbyRecordToRpcLobby(lobby)
	if (err != nil) {
		return nil, err
	}

	err = server.notifyLobbyUsers(rpcLobby, req.UserId)
	if (err != nil) {
		return nil, err
	}

	return &lobbiesPbs.LeaveLobbyResponse{}, nil
}

func (server LobbiesServer) GetLobby(ctx context.Context, req *lobbiesPbs.GetLobbyRequest) (*lobbiesPbs.Lobby, error) {
	lobby, err := server.lobbiesManager.GetLobby(req.LobbyId)

	if err != nil {
		return nil, err
	}

	return server.lobbyRecordToRpcLobby(lobby)
}

func (server LobbiesServer) GetAllLobbies(ctx context.Context, req *lobbiesPbs.GetAllLobbiesRequest) (*lobbiesPbs.GetAllLobbiesResponse, error) {
	lobbies, err := server.lobbiesManager.GetAllLobbies()
	if err != nil {
		return nil, err
	}

	lobbiesResp := make([]*lobbiesPbs.Lobby, 0)
	for _, lobby := range lobbies {
		rpcLobby, err := server.lobbyRecordToRpcLobby(lobby)
		if err != nil {
			return nil, err
		}

		lobbiesResp = append(lobbiesResp, rpcLobby)
	}

	return &lobbiesPbs.GetAllLobbiesResponse{Lobbies: lobbiesResp}, nil
}

func (server LobbiesServer) lobbyRecordToRpcLobby(lobby *types.Lobby) (*lobbiesPbs.Lobby, error) {
	rpcLobby := lobbiesPbs.Lobby{}
	rpcLobby.LobbyId = lobby.LobbyId
	rpcLobby.LobbyName = lobby.LobbyName
	rpcLobby.OwnerId = lobby.OwnerId
	rpcLobby.Users = []*lobbiesPbs.User{}

	userIds := getKeys_String(lobby.Users)
	err := server.addUsersFromAccountsService(&rpcLobby, userIds)
	if err != nil {
		return nil, err
	}

	return &rpcLobby, nil
}

func (server LobbiesServer) addUsersFromAccountsService(lobby *lobbiesPbs.Lobby, userIds []string) error {
	users, err := server.accountsProvider.GetAccounts(userIds)
	if err != nil {
		return err
	}

	for _, user := range users {
		lobby.Users = append(lobby.Users, &lobbiesPbs.User{UserId: user.UserId, UserName: user.Username})
	}

	return nil
}

func getKeys_String(m map[string]interface{}) []string {
	keys := make([]string, len(m))
	i := 0
	for key := range m {
		keys[i] = key
		i++
	}

	return keys
}

func getKeys_StringExclude(m map[string]interface{}, exclude string) []string {
	keys := make([]string, len(m))
	i := 0
	for key := range m {
		if (key != exclude) {
			keys[i] = key
		}
		i++
	}

	return keys
}

func (server LobbiesServer) notifyLobbyUsers (
	rpcLobby *lobbiesPbs.Lobby,
	excludeUser string,
) error {
	// serialize this to notify the other users of the lobby of the change
	serialized, err := serializeLobby(rpcLobby)
	if (err != nil) {
		return err
	}

	// the user making this request does not need to get a lobby update event.
	usersToNotify := make([]string, 0)
	for _, user := range rpcLobby.Users {
		if (user.UserId) != excludeUser {
			usersToNotify = append(usersToNotify, user.UserId)
		}
	}
	return server.gatewayDispatcher.DispatchBulk(usersToNotify, gateway.Type_LOBBY_UPDATE, serialized)
}