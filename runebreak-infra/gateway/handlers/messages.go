package handlers

import (
	"encoding/json"
	"io"
	"log"
	"net/http"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/authentication"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/connections"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/data/accounts/accounts_provider"
)

type MessagesHandler struct {
	accountsProvider accounts_provider.AccountsProvider
	authenticator authentication.Authenticator
	connections *connections.ConnectionManager
	logger *log.Logger
}

func NewMessagesHandler(accountsProvider accounts_provider.AccountsProvider, authenticator authentication.Authenticator, connections *connections.ConnectionManager, logger *log.Logger) *MessagesHandler {
	return &MessagesHandler{
		accountsProvider: accountsProvider,
		authenticator: authenticator,
		connections: connections,
		logger: logger,
	}
}

// todo: add message type
type SendMessageRequest struct {
	Text string `json:"text"`
	RecipientId string `json:"recipientId"` // todo: make optional
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
	}

	authorId, err := handler.authenticator.GetUserIdFromRequest(req)
	if err != nil {
		http.Error(rw, "unable to unmarshal send message request ", http.StatusBadRequest)
		return
	}

	// okay pretend we are in the "messages service"... need to communicate to sessions service that a message was
	// created. currently, the gateway service is serving as a sessions service, which happens to be where we are.
	if authorId == nil {
		handler.logger.Printf("author ID was nil\n")
		http.Error(rw, "very weird error", http.StatusInternalServerError)
		return
	}

	recipient, err := handler.accountsProvider.GetAccount(requestBody.RecipientId)
	if err != nil {
		http.Error(rw, "unable to find recipient", http.StatusInternalServerError)
		return
	} 

	handler.connections.SendMessage(
		*authorId, 
		recipient.Username,
		requestBody.Text,
		requestBody.RecipientId,
	)
}
