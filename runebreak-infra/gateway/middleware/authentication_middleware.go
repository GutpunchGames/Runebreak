package middleware

import (
	"log"
	"net/http"
)

type AuthenticationMiddleware struct {
	// map of user ID to token
	userTokenMap map[string]string
	logger *log.Logger
}

func NewAuthenticationMiddleware(logger *log.Logger) *AuthenticationMiddleware {
	return &AuthenticationMiddleware{
		userTokenMap: make(map[string]string),
		logger: logger,
	}
}

// Middleware function, which will be called for each request
func (amw *AuthenticationMiddleware) Middleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        token := r.Header.Get("X-Auth-Token")
		amw.logger.Printf("Got auth token: %s\n", token)

		next.ServeHTTP(w, r)
        // if user, found := amw.userTokenMap[token]; found {
        // 	// We found the token in our map
        // 	log.Printf("Authenticated user %s\n", user)
        // 	// Pass down the request to the next middleware (or final handler)
        // 	next.ServeHTTP(w, r)
        // } else {
        // 	// Write an error and stop the handler chain
        // 	http.Error(w, "Forbidden", http.StatusForbidden)
        // }
    })
}