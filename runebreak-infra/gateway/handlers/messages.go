package handlers

import (
	"encoding/json"
	"io"
	"log"
	"net/http"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/connections"
)

type MessagesHandler struct {
	connections *connections.ConnectionManager
	logger *log.Logger
}

func NewMessagesHandler(connections *connections.ConnectionManager, logger *log.Logger) *MessagesHandler {
	return &MessagesHandler{
		connections: connections,
		logger: logger,
	}
}

// todo: add message type
type SendMessageRequest struct {
	Text string `json:"text"`
	RecipientId string `json:"recipient_id"` // todo: make optional
}

func (request *SendMessageRequest) FromJSON(reader io.Reader) error {
	decoder := json.NewDecoder(reader)
	return decoder.Decode(request)
}

// http POST /messages
func (handler *MessagesHandler) SendMessage(rw http.ResponseWriter, req *http.Request) {
	requestBody := SendMessageRequest{}
	err := requestBody.FromJSON(req.Body)
	if err != nil {
		http.Error(rw, "unable to unmarshal send message request ", http.StatusBadRequest)
		return
	} else {
		handler.logger.Printf("got request body: %s\n", requestBody)
		rw.Write([]byte("{}"))
	}

	// okay pretend we are in the "messages service"... need to communicate to sessions service that a message was
	// created. currently, the gateway service is serving as a sessions service, which happens to be where we are.
	handler.connections.SendMessage(requestBody.Text, requestBody.RecipientId)
}
