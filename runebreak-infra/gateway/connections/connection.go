package connections

import (
	"encoding/json"
	"log"

	"github.com/gorilla/websocket"
)

type Connection struct {
	ws *websocket.Conn
}

func NewConnection(ws *websocket.Conn) *Connection {
	return &Connection{ws: ws}
}

func (connection *Connection) WriteMessage(message WSMessage) error {
	body, err := json.Marshal(message)
	if (err != nil) {
		log.Printf("failed to send message: %s\n", message) 
		return err
	}

	err = connection.ws.WriteMessage(websocket.TextMessage, body)
	if (err != nil) {
		log.Printf("failed to send message: %s\n", message)
	} 
	return err
}