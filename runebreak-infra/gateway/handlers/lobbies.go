package handlers

import (
	"context"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"time"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/authentication"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/data/accounts/accounts_provider"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/protos/lobbies"
	"google.golang.org/grpc"
)

type LobbiesHandler struct {
	accountsProvider accounts_provider.AccountsProvider
	authenticator authentication.Authenticator
	logger *log.Logger
}

func NewLobbiesHandler(accountsProvider accounts_provider.AccountsProvider, authenticator authentication.Authenticator, logger *log.Logger) *LobbiesHandler {
	return &LobbiesHandler{
		accountsProvider: accountsProvider,
		authenticator: authenticator,
		logger: logger,
	}
}

type lobby struct {
	OwnerId   string `json:"ownerId"`
	LobbyId   string `json:"lobbyId"`
	LobbyName string `json:"lobbyName"`
	Users     []lobbyUser `json:"users"`
}

type lobbyUser struct {
	Username string `json:"username"`
	UserId string `json:"userId"`
}

func fromRPCLobby(rpcLobby *lobbies.Lobby) lobby {
	users := make([]lobbyUser, len(rpcLobby.Users))
	for i, user := range rpcLobby.Users {
		lobbyUser := lobbyUser{}
		lobbyUser.UserId = user.UserId
		lobbyUser.Username = user.UserName
		users[i] = lobbyUser
	}

	return lobby{
		OwnerId: rpcLobby.OwnerId,
		LobbyId: rpcLobby.LobbyId,
		LobbyName: rpcLobby.LobbyName,
		Users: users,
	}
}

type CreateLobbyRequest struct {
	LobbyName string `json:"lobbyName"`
}
func (request *CreateLobbyRequest) FromJSON(reader io.Reader) error {
	decoder := json.NewDecoder(reader)
	return decoder.Decode(request)
}
type CreateLobbyResponse struct {
	 Lobby lobby `json:"lobby"`
}

type JoinLobbyRequest struct {
	LobbyId string `json:"lobbyId"`
}
func (request *JoinLobbyRequest) FromJSON(reader io.Reader) error {
	decoder := json.NewDecoder(reader)
	return decoder.Decode(request)
}
type JoinLobbyResponse struct {
	 Lobby lobby `json:"lobby"`
}

type LeaveLobbyRequest struct {
	LobbyId string `json:"lobbyId"`
}
func (request *LeaveLobbyRequest) FromJSON(reader io.Reader) error {
	decoder := json.NewDecoder(reader)
	return decoder.Decode(request)
}

type GetLobbyRequest struct {
	LobbyId string `json:"lobbyId"`
}
func (request *GetLobbyRequest) FromJSON(reader io.Reader) error {
	decoder := json.NewDecoder(reader)
	return decoder.Decode(request)
}
type GetLobbyResponse struct {
	 Lobby lobby `json:"lobby"`
}

type ListLobbiesResponse struct {
	 Lobbies []lobby `json:"lobbies"`
}

// http POST /lobbies
func (handler *LobbiesHandler) CreateLobby(rw http.ResponseWriter, req *http.Request) {
	userId, err := handler.authenticator.GetUserIdFromRequest(req)
	if err != nil {
		http.Error(rw, "unable to get user from request", http.StatusBadRequest)
	}

	createLobbyRequest := CreateLobbyRequest{}
	createLobbyRequest.FromJSON(req.Body)

	rpcRequest := lobbies.CreateLobbyRequest{UserId: *userId, LobbyName: createLobbyRequest.LobbyName}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	client, conn := handler.createLobbiesClient()
	defer conn.Close()

	resp, err := client.Create(ctx, &rpcRequest)
	if err == nil {
		lobbyResp := CreateLobbyResponse{Lobby: fromRPCLobby(resp)}
		respJson, err := json.Marshal(lobbyResp)
		if err != nil {
			http.Error(rw, "unable to marshal response", http.StatusInternalServerError)
		} else {
			rw.Write(respJson)
		}
	} else {
		msg := fmt.Sprintf("error creating lobby: %s", err)
		http.Error(rw, msg, http.StatusBadRequest)
	}
}

// http PATCH /lobbies/join
func (handler *LobbiesHandler) JoinLobby(rw http.ResponseWriter, req *http.Request) {
	userId, err := handler.authenticator.GetUserIdFromRequest(req)
	if err != nil {
		http.Error(rw, "unable to get user from request", http.StatusBadRequest)
	}

	joinLobbyRequest := JoinLobbyRequest{}
	joinLobbyRequest.FromJSON(req.Body)

	rpcRequest := lobbies.JoinLobbyRequest{UserId: *userId, LobbyId: joinLobbyRequest.LobbyId}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	client, conn := handler.createLobbiesClient()
	defer conn.Close()

	resp, err := client.Join(ctx, &rpcRequest)
	if err == nil {
		lobbyResp := JoinLobbyResponse{Lobby: fromRPCLobby(resp)}
		respJson, err := json.Marshal(lobbyResp)
		if err != nil {
			http.Error(rw, "unable to marshal response", http.StatusInternalServerError)
		} else {
			rw.Write(respJson)
		}
	} else {
		msg := fmt.Sprintf("error joining lobby: %s", err)
		http.Error(rw, msg, http.StatusBadRequest)
	}
}

// http PATCH /lobbies/leave
func (handler *LobbiesHandler) LeaveLobby(rw http.ResponseWriter, req *http.Request) {
	userId, err := handler.authenticator.GetUserIdFromRequest(req)
	if err != nil {
		http.Error(rw, "unable to get user from request", http.StatusBadRequest)
	}

	leaveLobbyRequest := LeaveLobbyRequest{}
	leaveLobbyRequest.FromJSON(req.Body)

	rpcRequest := lobbies.LeaveLobbyRequest{UserId: *userId, LobbyId: leaveLobbyRequest.LobbyId}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	client, conn := handler.createLobbiesClient()
	defer conn.Close()

	_, err = client.Leave(ctx, &rpcRequest)
	if err == nil {
		rw.Write([]byte{})
	} else {
		msg := fmt.Sprintf("error leaving lobby: %s", err)
		http.Error(rw, msg, http.StatusBadRequest)
	}
}

// http GET /lobbies
func (handler *LobbiesHandler) GetLobby(rw http.ResponseWriter, req *http.Request) {
	_, err := handler.authenticator.GetUserIdFromRequest(req)
	if err != nil {
		http.Error(rw, "unable to get user from request", http.StatusBadRequest)
	}

	getLobbyRequest := GetLobbyRequest{}
	getLobbyRequest.FromJSON(req.Body)

	rpcRequest := lobbies.GetLobbyRequest{LobbyId: getLobbyRequest.LobbyId}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	client, conn := handler.createLobbiesClient()
	defer conn.Close()

	rpcResp, err := client.GetLobby(ctx, &rpcRequest)
	if err == nil {
		restResp := GetLobbyResponse{fromRPCLobby(rpcResp)}
		respJson, err := json.Marshal(restResp)
		if err != nil {
			http.Error(rw, "unable to marshal response", http.StatusInternalServerError)
		} else {
			rw.Write(respJson)
		}
	} else {
		msg := fmt.Sprintf("error getting lobby: %s", err)
		http.Error(rw, msg, http.StatusBadRequest)
	}
}

// http GET /lobbies/list
func (handler *LobbiesHandler) ListLobbies(rw http.ResponseWriter, req *http.Request) {
	_, err := handler.authenticator.GetUserIdFromRequest(req)
	if err != nil {
		http.Error(rw, "unable to get user from request", http.StatusBadRequest)
	}

	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	client, conn := handler.createLobbiesClient()
	defer conn.Close()

	rpcResp, err := client.GetAllLobbies(ctx, &lobbies.GetAllLobbiesRequest{})
	if err == nil {
		lobbies := make([]lobby, len(rpcResp.Lobbies))
		for i, rpcLobby := range rpcResp.Lobbies {
			lobbies[i] = fromRPCLobby(rpcLobby)
		}

		restResp := ListLobbiesResponse{Lobbies: lobbies}
		respJson, err := json.Marshal(restResp)
		if err != nil {
			http.Error(rw, "unable to marshal response", http.StatusInternalServerError)
		} else {
			rw.Write(respJson)
		}
	} else {
		msg := fmt.Sprintf("error leaving lobby: %s", err)
		http.Error(rw, msg, http.StatusBadRequest)
	}
}

func (handler *LobbiesHandler) createLobbiesClient() (lobbies.LobbiesClient, *grpc.ClientConn) {
	conn, err := grpc.Dial("lobbies:9090", grpc.WithInsecure())
	if err != nil {
		panic(err)
	}

	return lobbies.NewLobbiesClient(conn), conn
}
