package connections

import (
	"log"

	"github.com/gorilla/websocket"
)

type Connection struct {
	ws *websocket.Conn
}

func NewConnection(ws *websocket.Conn) *Connection {
	return &Connection{ws: ws}
}

func (connection *Connection) SendMessage(message Message) error {
	err := connection.ws.WriteMessage(websocket.TextMessage, message.payload)
	if (err != nil) {
		log.Printf("failed to send message: %s\n", message.payload)
	} else {
		log.Printf("sent message: %s\n", message.payload)
	}
	return err
}