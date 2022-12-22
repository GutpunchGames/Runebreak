package authentication

import (
	"fmt"
	"log"
	"net/http"
)

type Authenticator interface {
	GetUserIdFromRequest(r *http.Request) (*string, error)
	AssociateToken(token string, userId string)
}

type TokenAuthenticator struct {
	tokensToUsers map[string]string
	logger *log.Logger
}

func NewTokenAuthenticator(logger *log.Logger) TokenAuthenticator {
	return TokenAuthenticator{
		tokensToUsers: make(map[string]string),
		logger: logger,
	}
}

type TokenNotFoundError struct {}

func (e *TokenNotFoundError) Error() string {
	return fmt.Sprintf("Token not found")
}

func (authenticator TokenAuthenticator) GetUserIdFromRequest(r *http.Request) (*string, error) {
	token := r.Header.Get("X-Auth-Token")
	authenticator.logger.Printf("got token: %s\n", token)
	if userId, found := authenticator.tokensToUsers[token]; !found {
		authenticator.logger.Printf("could not find user for token")
		return nil, &TokenNotFoundError{}
	} else {
		authenticator.logger.Printf("found user for token")
		return &userId, nil
	}
}

func (authenticator TokenAuthenticator) AssociateToken(token string, userId string) {
	authenticator.tokensToUsers[token] = userId
}