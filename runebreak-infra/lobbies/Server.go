package lobbiesserver

import (
	"context"
	"log"
	"os"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/data/accounts/accounts_provider"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/protos/lobbies"
	"github.com/google/uuid"
	"github.com/hashicorp/go-hclog"
)

type LobbiesServer struct {
	Logger hclog.Logger
	accountsProvider accounts_provider.AccountsProvider
	lobbies.UnimplementedLobbiesServer
}

func NewServer(l hclog.Logger) *LobbiesServer {
	tLogger := log.New(os.Stdout, "lobbies server", log.LstdFlags)
	accountsProvider := accounts_provider.NewAccountsProvider(tLogger)
	return &LobbiesServer{Logger: l, accountsProvider: accountsProvider, UnimplementedLobbiesServer: lobbies.UnimplementedLobbiesServer{}}
}

func (server LobbiesServer) Create(ctx context.Context, req *lobbies.CreateLobbyRequest) (*lobbies.Lobby, error) {
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
		lobbyResp := lobbies.Lobby{}
		lobbyResp.LobbyId = lobby.lobbyId
		lobbyResp.LobbyName = lobby.lobbyName
		lobbyResp.OwnerId = lobby.ownerId

		// add the creator to the lobby
		respUser := lobbies.User{}
		respUser.UserId = req.UserId
		respUser.UserName = user.Username
		lobbyResp.Users = []*lobbies.User{&respUser}

		return &lobbyResp, nil
	} else {
		return nil, err
	}
}

func Join(context.Context, *lobbies.JoinLobbyRequest) (*lobbies.Lobby, error) {
	return &lobbies.Lobby{}, nil
}

func GetLobby(context.Context, *lobbies.GetLobbyRequest) (*lobbies.Lobby, error) {
	return &lobbies.Lobby{}, nil
}

func GetAllLobbies(context.Context, *lobbies.GetAllLobbiesRequest) (*lobbies.GetAllLobbiesResponse, error) {
	return &lobbies.GetAllLobbiesResponse{}, nil
}

func (server LobbiesServer) create(userId string, lobbyName string) (lobby, error) {
	// todo: ensure ID uniqueness. ring buffer of ints? dedicated lobbies?
	var lobbyId string = uuid.NewString()
	lobby := newLobby(userId, lobbyId, lobbyName)
	return lobby, nil
}

type lobby struct {
	ownerId string
	lobbyId string
	lobbyName string
}

func newLobby(ownerId string, lobbyId string, lobbyName string) lobby {
	return lobby{
		ownerId: ownerId,
		lobbyId: lobbyId,
		lobbyName: lobbyName,
	}
}