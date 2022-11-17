package main

import (
	"context"
	"fmt"
	"log"
	"net/http"
	"os"
	"os/signal"
	"time"

	accountsProtos "github.com/GutpunchGames/Runebreak/runebreak-infra/services/accounts/protos"
	"github.com/gorilla/mux"
)

const serviceName = "runebreak-gateway-service"

func main() {
	port := extractArgs(os.Args)
	logger := log.New(os.Stdout,serviceName, log.LstdFlags)
	serveMux := mux.NewRouter()
	getRouter := serveMux.Methods(http.MethodGet).Subrouter()
	getRouter.HandleFunc("/",  t)

	accountsProtos.TestFunc2()

	// conn, err := grpc.Dial("localhost:9091", grpc.WithInsecure())
	// if err != nil {
	// 	panic(err)
	// }
	// defer conn.Close()

	// accountsClient := accountsProtos.NewAccountsClient(conn)

	// req := accounts.ExampleRequest{ParamOne: accounts.ExampleEnum_ZERO}
	// fmt.Printf("created request: %s\n", req)
	// res, err := accountsClient.GetExample(context.TODO(), &req)
	// fmt.Printf("got response: %s\n", res)

	url := fmt.Sprintf("localhost:%s", port)

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

func t(rw http.ResponseWriter, request *http.Request) {
	rw.Write([]byte("gateway"))
}

// expecting:
// [1] port
func extractArgs(args []string) string {
	return args[1]
}