package connections

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"

	"github.com/gorilla/websocket"
)

type ConnectionManager struct {
	connections map[string]*Connection
	logger *log.Logger
}

const (
	writeWait = 10 * time.Second
	pingPeriod = 5 * time.Second
)

func NewConnectionManager(logger *log.Logger) *ConnectionManager {
	return &ConnectionManager{
		connections: make(map[string]*Connection),
		logger: logger,
	}
}

func (connectionManager *ConnectionManager) CreateConnection(w http.ResponseWriter, r *http.Request, userId string) {
	connectionManager.logger.Printf("Create Connection: %s\n", userId)

	var upgrader  = websocket.Upgrader{
		ReadBufferSize:  1024,
		WriteBufferSize: 1024,
	}

	upgrader.CheckOrigin = func(r *http.Request) bool {
		return true
	}

	ws, err := upgrader.Upgrade(w, r, nil)

	if err != nil {
		if _, ok := err.(websocket.HandshakeError); !ok {
			log.Println(err)
		}
		errorStr := fmt.Sprintf("could not create websocket: %s", err)
		log.Println(errorStr)
		http.Error(w, errorStr, http.StatusInternalServerError)
	}
	
	// do something with the ws
	connectionManager.connections[userId] = NewConnection(ws)
}

type chatMessage struct {
	AuthorId string `json:"authorId"`
	AuthorName string `json:"authorName"`
	Text string `json:"text"`
}

func (connectionManager *ConnectionManager) DispatchMessageCreate(authorId string, authorName string, text string, recipientId string) {
	//create message json
	json, err := json.Marshal(chatMessage{AuthorId: authorId, AuthorName: authorName, Text: text})
	if (err != nil) {
		connectionManager.logger.Printf("failed to marshal message to user: %s\n", recipientId)
		return
	}

	connectionManager.Dispatch(recipientId, json)
}

func (connectionManager *ConnectionManager) Dispatch(userId string, payload []byte) {
	// first, find the connection
	conn, ok := connectionManager.connections[userId]
	if !ok {
		connectionManager.logger.Printf("user was offline: %s\n", userId)
		return
	}

	// send the message over the websocket
	if err := conn.WriteMessage(WSMessage{payload: payload}); err != nil {
		connectionManager.logger.Printf("failed to deliver message to user: %s\n", userId)
		return
	} else {
		connectionManager.logger.Printf("delivered message to user: %s\n", userId)
	} 
}