package connections

import "golang.org/x/net/websocket"

type Connection struct {
	ws_conn *websocket.Conn
}

func (connection *Connection) SendMessage(mesage Message) {
}