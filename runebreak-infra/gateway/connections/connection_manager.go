package connections

import (
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
	// Time allowed to read the next pong message from the client.
	pongWait = 60 * time.Second
	// Send pings to client with this period. Must be less than pongWait.
	pingPeriod = (pongWait * 9) / 10
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

	ws, err := upgrader.Upgrade(w, r, nil)

	if err != nil {
		if _, ok := err.(websocket.HandshakeError); !ok {
			log.Println(err)
		}
		errorStr := fmt.Sprintf("could not create websocket: %s", err)
		http.Error(w, errorStr, http.StatusInternalServerError)
	}
	
	// do something with the ws
	connectionManager.connections[userId] = NewConnection(ws)
}

// func serveWs(w http.ResponseWriter, r *http.Request) {
// 	var upgrader  = websocket.Upgrader{
// 		ReadBufferSize:  1024,
// 		WriteBufferSize: 1024,
// 	}

// 	ws, err := upgrader.Upgrade(w, r, nil)

// 	if err != nil {
// 		if _, ok := err.(websocket.HandshakeError); !ok {
// 			log.Println(err)
// 		}
// 		return
// 	}

// 	var lastMod time.Time
// 	if n, err := strconv.ParseInt(r.FormValue("lastMod"), 16, 64); err == nil {
// 		lastMod = time.Unix(0, n)
// 	}

// 	go writer(ws, lastMod)
// 	reader(ws)
// }

// func reader(ws *websocket.Conn) {
// 	defer ws.Close()
// 	ws.SetReadLimit(512)
// 	ws.SetReadDeadline(time.Now().Add(pongWait))
// 	ws.SetPongHandler(func(string) error { ws.SetReadDeadline(time.Now().Add(pongWait)); return nil })
// 	for {
// 		_, _, err := ws.ReadMessage()
// 		if err != nil {
// 			break
// 		}
// 	}
// }

// func writer(ws *websocket.Conn, lastMod time.Time) {
// 	pingTicker := time.NewTicker(pingPeriod)
// 	defer func() {
// 		pingTicker.Stop()
// 		ws.Close()
// 	}()

// 	for {
// 		select {
// 			case <-pingTicker.C:
// 				ws.SetWriteDeadline(time.Now().Add(writeWait))
// 				if err := ws.WriteMessage(websocket.PingMessage, []byte{}); err != nil {
// 					return
// 				}
// 			}
// 	}
// }
