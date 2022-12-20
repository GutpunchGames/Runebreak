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
	// Time allowed to write the file to the client.
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

	go pinger(ws, connectionManager.logger)
}

func pinger(ws *websocket.Conn, logger *log.Logger) {
	pingTicker := time.NewTicker(pingPeriod)
	defer func() {
		pingTicker.Stop()
		ws.Close()
	}()

	for {
		select {
			case <-pingTicker.C:
				ws.SetWriteDeadline(time.Now().Add(writeWait))
				if err := ws.WriteMessage(websocket.PingMessage, []byte{}); err != nil {
					return
				} else {
					logger.Println("sent ping message")
				} 
			}
	}
}

type MessageToSend struct {
	Text string `json:"text"`
	RecipientId string `json:"recipient_id"` // todo: make optional
}

func (connectionManager *ConnectionManager) SendMessage(text string, recipient_id string) {
	// first, find the connection
	conn, ok := connectionManager.connections[recipient_id]
	if !ok {
		connectionManager.logger.Printf("user was offline: %s\n", recipient_id)
		return
	}

	//debug: create message json
	json, err := json.Marshal(MessageToSend{Text: text, RecipientId: recipient_id})
	if (err != nil) {
		connectionManager.logger.Printf("failed to marshal message to user: %s\n", recipient_id)
		return
	}

	// send the message over the connection
	if err := conn.SendMessage(Message{payload: json}); err != nil {
		connectionManager.logger.Printf("failed to deliver message to user: %s\n", recipient_id)
		return
	} else {
		connectionManager.logger.Printf("delivered message to user: %s\n", recipient_id)
	} 
}