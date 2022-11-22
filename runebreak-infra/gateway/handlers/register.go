package handlers

import (
	"encoding/json"
	"io"
	"log"
	"net/http"
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
func (handler *RegisterHandler) Register (rw http.ResponseWriter, req *http.Request) {
	requestBody := RegisterRequest{}
	err := requestBody.FromJSON(req.Body)
	if err != nil {
		http.Error(rw, "uh oh", http.StatusBadRequest)
		return
	}

	resp := &RegisterResponse{UserId: "1234"}
	respJson, _ := json.Marshal(resp)
	rw.Write(respJson)
}

// http POST /login
func (handler *RegisterHandler) Login (rw http.ResponseWriter, req *http.Request) {
	rw.Write([]byte("hello login"))
}

// http POST /logout
func (handler *RegisterHandler) Logout (rw http.ResponseWriter, req *http.Request) {
	rw.Write([]byte("hello logout"))
}