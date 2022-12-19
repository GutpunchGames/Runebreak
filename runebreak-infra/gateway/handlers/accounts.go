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
