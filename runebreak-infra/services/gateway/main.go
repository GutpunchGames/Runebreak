package main

import (
	"context"
	"fmt"
	"log"
	"net/http"
	"os"
	"os/signal"
	"time"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/protos/accounts"
	"github.com/GutpunchGames/Runebreak/runebreak-infra/services/gateway/handlers"
	"github.com/gorilla/mux"
	"google.golang.org/grpc"
)

const serviceName = "runebreak-gateway-service"

func main() {
	port := extractArgs(os.Args)
	logger := log.New(os.Stdout,serviceName, log.LstdFlags)
	serveMux := mux.NewRouter()

	registerHandler := handlers.NewRegisterHandler(logger)
	getRouter := serveMux.Methods(http.MethodGet).Subrouter()
	getRouter.HandleFunc("/register", registerHandler.Register)

	conn, err := grpc.Dial(":9092", grpc.WithInsecure())
	if err != nil {
		panic(err)
	}
	defer conn.Close()

	accountsClient := accounts.NewAccountsClient(conn)
	req := accounts.ExampleRequest{ParamOne: accounts.ExampleEnum_ZERO}
	ctx, cancel := context.WithTimeout(context.Background(), 5 * time.Second)
	defer cancel()

	res, err := accountsClient.GetExample(ctx, &req)
	if err == nil {
		logger.Printf("got response: %s\n", res)
	} else {
		logger.Printf("got error: %s\n", err)
		return
	}

	url := fmt.Sprintf(":%s", port)
	server := &http.Server{
		Addr: url,
		Handler: serveMux,
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