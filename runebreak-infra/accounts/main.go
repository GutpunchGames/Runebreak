package main

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os"
	"os/signal"
	"time"

	"github.com/gorilla/handlers"

	"github.com/gorilla/mux"
)

const serviceName = "runebreak-accounts-service"

type BasicResponse struct {
    Name string
}

func main() {
	port := extractArgs(os.Args)
	logger := log.New(os.Stdout,serviceName, log.LstdFlags)
	serveMux := mux.NewRouter()
	getRouter := serveMux.Methods(http.MethodGet).Subrouter()
	getRouter.HandleFunc("/",  t)

	originsOk := handlers.AllowedOrigins([]string{"*"})
	wrapped := handlers.CORS(originsOk)(serveMux)

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

func t(rw http.ResponseWriter, request *http.Request) {
	resp := &BasicResponse{Name: "hello"}
	respJson, _ := json.Marshal(resp)
	rw.Write(respJson)
}

// expecting:
// [1] port
func extractArgs(args []string) string {
	return args[1]
}