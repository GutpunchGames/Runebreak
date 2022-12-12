package handlers

import (
	"context"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"time"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/protos/accounts"
	"google.golang.org/grpc"
)

type RegisterHandler struct {
	logger *log.Logger
}

type RegisterRequest struct {
	Username string `json:"username"`
	Password string `json:"password"`
}

func (request *RegisterRequest) FromJSON(reader io.Reader) error {
	decoder := json.NewDecoder(reader)
	return decoder.Decode(request)
}

type RegisterResponse struct {
	UserId string
}

func NewRegisterHandler(logger *log.Logger) *RegisterHandler {
	return &RegisterHandler{logger}
}

// http POST /register
func (handler *RegisterHandler) Register(rw http.ResponseWriter, req *http.Request) {
	handler.logger.Printf("checkpoint 1\n")
	requestBody := RegisterRequest{}
	err := requestBody.FromJSON(req.Body)
	if err != nil {
		http.Error(rw, "uh oh", http.StatusBadRequest)
		return
	}

	handler.logger.Printf("checkpoint 2\n")
	rpcResponse, err := handler.rpcRegister(requestBody.Username, requestBody.Password)
	if err == nil {
		handler.logger.Printf("checkpoint 3\n")
		resp := &RegisterResponse{UserId: rpcResponse.UserId}
		respJson, _ := json.Marshal(resp)
		rw.Write(respJson)
	} else {
		handler.logger.Printf("checkpoint 4\n")
		http.Error(rw, fmt.Sprintf("couldn't make rpc call: %s", err), http.StatusInternalServerError)
	}
}

func (handler *RegisterHandler) rpcRegister(username string, password string) (*accounts.UserAuthenticationResponse, error) {
	conn, err := grpc.Dial("accounts:9090", grpc.WithInsecure())
	if err != nil {
		panic(err)
	}
	defer conn.Close()

	accountsClient := accounts.NewAccountsClient(conn)
	req := accounts.UserAuthenticationRequest{Username: username, Password: password}
	ctx, cancel := context.WithTimeout(context.Background(), 5 * time.Second)
	defer cancel()

	resp, err := accountsClient.Register(ctx, &req)
	if err == nil {
		handler.logger.Printf("got response: %s\n", resp)
		return resp, nil
	} else {
		handler.logger.Printf("got error: %s\n", err)
		return nil, err
	}
}

// http POST /login
func (handler *RegisterHandler) Login (rw http.ResponseWriter, req *http.Request) {
	rw.Write([]byte("hello login"))
}

// http POST /logout
func (handler *RegisterHandler) Logout (rw http.ResponseWriter, req *http.Request) {
	rw.Write([]byte("hello logout"))
}