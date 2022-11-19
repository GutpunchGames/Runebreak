package handlers

import (
	"log"
	"net/http"
)

type RegisterHandler struct {
	logger *log.Logger
}

func NewRegisterHandler(logger *log.Logger) *RegisterHandler {
	return &RegisterHandler{logger}
}

// http POST /register
func (handler *RegisterHandler) Register (rw http.ResponseWriter, req *http.Request) {
	rw.Write([]byte("hello register"))
}

// http POST /login
func (handler *RegisterHandler) Login (rw http.ResponseWriter, req *http.Request) {
	rw.Write([]byte("hello login"))
}

// http POST /logout
func (handler *RegisterHandler) Logout (rw http.ResponseWriter, req *http.Request) {
	rw.Write([]byte("hello logout"))
}