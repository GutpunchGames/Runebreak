package connections

import (
	"github.com/gorilla/websocket"
)

type Connection struct {
	ws *websocket.Conn
}

func NewConnection(ws *websocket.Conn) *Connection {
	return &Connection{ws: ws}
}

func (connection *Connection) SendMessage(mesage Message) {
}