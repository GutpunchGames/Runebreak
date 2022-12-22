package middleware

import (
	"log"
	"net/http"
	"strings"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/authentication"
)

type AuthenticationMiddleware struct {
	authenticator authentication.Authenticator
	logger *log.Logger
}

func NewAuthenticationMiddleware(authenticator authentication.Authenticator, logger *log.Logger) *AuthenticationMiddleware {
	return &AuthenticationMiddleware{
        authenticator: authenticator,
		logger: logger,
	}
}

func isExcludedRoute(uri string) bool {
    return strings.Contains(uri, "login") || strings.Contains(uri, "register") || strings.Contains(uri, "connect")
}

func (amw *AuthenticationMiddleware) Middleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        if (isExcludedRoute(r.RequestURI)) {
            next.ServeHTTP(w, r)
            return
        }

        userId, err := amw.authenticator.GetUserIdFromRequest(r)
        if err != nil {
            amw.logger.Printf("forbidden request: %s\n", r.RequestURI)
            http.Error(w, "Forbidden", http.StatusForbidden)
            return
        } else {
            amw.logger.Printf("Authenticated user %s\n", *userId)
            next.ServeHTTP(w, r)
        }
    })
}