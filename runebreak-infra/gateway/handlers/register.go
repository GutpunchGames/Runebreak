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
	requestBody := RegisterRequest{}
	err := requestBody.FromJSON(req.Body)
	if err != nil {
		http.Error(rw, "uh oh", http.StatusBadRequest)
		return
	}

	err = handler.rpcRegister(requestBody.Username, requestBody.Password)
	if err == nil {
		resp := &RegisterResponse{UserId: "1234"}
		respJson, _ := json.Marshal(resp)
		rw.Write(respJson)
	} else {
		http.Error(rw, fmt.Sprintf("couldn't make rpc call: %s", err), http.StatusInternalServerError)
	}
}

func (handler *RegisterHandler) rpcRegister(username string, password string) error {
	conn, err := grpc.Dial("localhost:9001", grpc.WithInsecure())
	if err != nil {
		panic(err)
	}
	defer conn.Close()

	accountsClient := accounts.NewAccountsClient(conn)
	req := accounts.ExampleRequest{ParamOne: accounts.ExampleEnum_ZERO}
	ctx, cancel := context.WithTimeout(context.Background(), 5 * time.Second)
	defer cancel()

	res, err := accountsClient.GetExample(ctx, &req)
	if err == nil {
		handler.logger.Printf("got response: %s\n", res)
		return nil
	} else {
		handler.logger.Printf("got error: %s\n", err)
		return err
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