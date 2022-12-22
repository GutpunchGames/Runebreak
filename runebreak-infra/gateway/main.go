package main

import (
	"context"
	"fmt"
	"log"
	"net/http"
	"os"
	"os/signal"
	"time"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/authentication"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/connections"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/handlers"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/middleware"
	gorillaHandlers "github.com/gorilla/handlers"
	"github.com/gorilla/mux"
)

const serviceName = "runebreak-gateway-service"

func main() {
	port := extractArgs(os.Args)
	logger := log.New(os.Stdout,serviceName, log.LstdFlags)
	authenticator := authentication.NewTokenAuthenticator(logger)

	connectionManager := connections.NewConnectionManager(logger)
	authenticationHandler := handlers.NewAuthenticationHandler(authenticator, logger)
	accountsHandler := handlers.NewAccountsHandler(logger)
	connectHandler := handlers.NewConnectHandler(connectionManager, logger)
	messagesHandler := handlers.NewMessagesHandler(connectionManager, logger)

	originsOk := gorillaHandlers.AllowedOrigins([]string{os.Getenv("ORIGIN_ALLOWED"), "*"})
	headersOk := gorillaHandlers.AllowedHeaders([]string{"X-Auth-Token"})
	methodsOk := gorillaHandlers.AllowedMethods([]string{"POST", "PATCH", "GET"})

	serveMux := mux.NewRouter()

	postRouter := serveMux.Methods(http.MethodPost).Subrouter()
	postRouter.HandleFunc("/register", authenticationHandler.Register)
	postRouter.HandleFunc("/login", authenticationHandler.Login)
	postRouter.HandleFunc("/messages", messagesHandler.SendMessage)

	patchRouter := serveMux.Methods(http.MethodPatch).Subrouter()
	patchRouter.HandleFunc("/accounts/{userId}", accountsHandler.UpdateUser)

	getRouter := serveMux.Methods(http.MethodGet).Subrouter()
	getRouter.HandleFunc("/connect/{userId}", connectHandler.Connect)

	serveMux.Use(middleware.NewAuthenticationMiddleware(authenticator, logger).Middleware)
	wrapped := gorillaHandlers.CORS(originsOk, headersOk, methodsOk)(serveMux)

	url := fmt.Sprintf(":%s", port)
	server := &http.Server{
		Addr: url,
		Handler: wrapped,
		IdleTimeout: 120 * time.Second,
		ReadTimeout: 1 * time.Second,
		WriteTimeout: 1 * time.Second,
	}

	go func() {
		logger.Printf("listening at %s\n", url)
		err := server.ListenAndServe()
		if err != nil {
			logger.Fatalf("error: %s", err)
		}
	}()

	sigChan := make(chan os.Signal)
	signal.Notify(sigChan, os.Interrupt)
	signal.Notify(sigChan, os.Kill)

	sig := <- sigChan
	logger.Println("Received terminate, graceful shutdown", sig)

	tc, cancelFunc := context.WithTimeout(context.Background(), 30 * time.Second)
	server.Shutdown(tc)
	cancelFunc()
}

// expecting:
// [1] port
func extractArgs(args []string) string {
	return args[1]
}