package handlers

import (
	"log"
	"net/http"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/connections"
	"github.com/gorilla/mux"
)

type ConnectHandler struct {
	connectionManager *connections.ConnectionManager
	logger *log.Logger
}

func NewConnectHandler(connectionManager *connections.ConnectionManager, logger *log.Logger) *ConnectHandler {
	return &ConnectHandler{
		connectionManager: connectionManager,
		logger: logger,
	}
}

// http POST /connect/{userId}
func (handler *ConnectHandler) Connect(rw http.ResponseWriter, req *http.Request) {
	params := mux.Vars(req)
	userId := params["userId"]
	// responding in the case of an error is handled internally
	handler.connectionManager.CreateConnection(rw, req, userId)
}
