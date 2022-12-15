package handlers

import (
	"encoding/json"
	"io"
	"log"
	"net/http"

	"github.com/gorilla/mux"
)

type AccountsHandler struct {
	logger *log.Logger
}

type PatchUserRequest struct {
	Username string `json:"username"`
	Password string `json:"password"`
}

func (request *PatchUserRequest) FromJSON(reader io.Reader) error {
	decoder := json.NewDecoder(reader)
	return decoder.Decode(request)
}

type PatchUserResponse struct {
	UserId string
}

func NewAccountsHandler(logger *log.Logger) *AccountsHandler {
	return &AccountsHandler{logger}
}

// http PATCH /users/{userId}
func (handler *AccountsHandler) UpdateUser(rw http.ResponseWriter, req *http.Request) {
	params := mux.Vars(req)
	userId := params["userId"]
	token := req.Header.Get("X-Session-Token")

	handler.logger.Printf("got user id '%s' and token '%s'\n", userId, token)
	rw.Write([]byte("{}"))
}

// func (handler *AccountsHandler) rpcLogin(username string, password string) (*accounts.UserAuthenticationResponse, error) {
// 	conn, err := grpc.Dial("accounts:9090", grpc.WithInsecure())
// 	if err != nil {
// 		panic(err)
// 	}
// 	defer conn.Close()

// 	accountsClient := accounts.NewAccountsClient(conn)
// 	req := accounts.UserAuthenticationRequest{Username: username, Password: password}
// 	ctx, cancel := context.WithTimeout(context.Background(), 5 * time.Second)
// 	defer cancel()

// 	resp, err := accountsClient.Login(ctx, &req)
// 	if err == nil {
// 		handler.logger.Printf("got response: %s\n", resp)
// 		return resp, nil
// 	} else {
// 		handler.logger.Printf("got error: %s\n", err)
// 		return nil, err
// 	}
// }