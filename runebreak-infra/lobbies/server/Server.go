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
	lobby, err := server.create(req.UserId, req.LobbyName)
	if err != nil {
		return nil, err
	}

	user, err := server.accountsProvider.GetAccount(req.UserId)

	if err != nil {
		return nil, err
	}

	if err == nil {
		lobbyResp := lobbiesPbs.Lobby{}
		lobbyResp.LobbyId = lobby.LobbyId
		lobbyResp.LobbyName = lobby.LobbyName
		lobbyResp.OwnerId = lobby.OwnerId

		// add the creator to the lobby
		respUser := lobbies.User{}
		respUser.UserId = req.UserId
		respUser.UserName = user.Username
		lobbyResp.Users = []*lobbiesPbs.User{&respUser}

		return &lobbyResp, nil
	} else {
		return nil, err
	}
}

func Join(context.Context, *lobbies.JoinLobbyRequest) (*lobbiesPbs.Lobby, error) {
	return &lobbies.Lobby{}, nil
}

func GetLobby(context.Context, *lobbies.GetLobbyRequest) (*lobbiesPbs.Lobby, error) {
	return &lobbies.Lobby{}, nil
}

func GetAllLobbies(context.Context, *lobbies.GetAllLobbiesRequest) (*lobbiesPbs.GetAllLobbiesResponse, error) {
	return &lobbies.GetAllLobbiesResponse{}, nil
}

func (server LobbiesServer) create(userId string, lobbyName string) (types.Lobby, error) {
	// todo: ensure ID uniqueness. ring buffer of ints? dedicated lobbies?
	var lobbyId string = uuid.NewString()
	lobby := types.NewLobby(userId, lobbyId, lobbyName)
	return lobby, nil
}