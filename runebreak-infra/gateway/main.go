package main

import (
	"context"
	"fmt"
	"log"
	"net/http"
	"os"
	"os/signal"
	"time"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/handlers"
	exported "github.com/GutpunchGames/Runebreak/runebreak-infra/protos"
	gorillaHandlers "github.com/gorilla/handlers"
	"github.com/gorilla/mux"
)

const serviceName = "runebreak-gateway-service"

func main() {
	exported.ExportedFunc()
	port := extractArgs(os.Args)
	logger := log.New(os.Stdout,serviceName, log.LstdFlags)

	registerHandler := handlers.NewRegisterHandler(logger)

	serveMux := mux.NewRouter()
	postRouter := serveMux.Methods(http.MethodPost).Subrouter()
	postRouter.HandleFunc("/register", registerHandler.Register)

	originsOk := gorillaHandlers.AllowedOrigins([]string{os.Getenv("ORIGIN_ALLOWED"), "*"})
	wrapped := gorillaHandlers.CORS(originsOk)(serveMux)

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