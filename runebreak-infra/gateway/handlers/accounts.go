package handlers

import (
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
	token := req.Header.Get("X-Auth-Token")

	handler.logger.Printf("got user id '%s' and token '%s'\n", userId, token)
	rw.Write([]byte("{}"))
}
