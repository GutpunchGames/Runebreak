package main

import (
	"context"
	"fmt"
	"log"
	"net"
	"os"
	"os/signal"
	"time"

	"github.com/hashicorp/go-hclog"
	"google.golang.org/grpc"
)

const serviceName = "runebreak-lobbies-service"

func main() {
	port := extractArgs(os.Args)
	logger := log.New(os.Stdout,serviceName, log.LstdFlags)

	var opts []grpc.ServerOption
	grpcServer := grpc.NewServer(opts...)

	logger2 := hclog.Default()
	// accServer := accountsServer.NewServer(logger2)
	// accountsPbs.RegisterAccountsServer(grpcServer, accServer)
	// reflection.Register(grpcServer)

	endpoint := fmt.Sprintf(":%s", port)
	lis, err := net.Listen("tcp", endpoint)
	if err != nil {
		logger2.Error("unable to listen", "error", err)
		os.Exit(1)
		return
	}
	logger2.Info("listening.", "endpoint", endpoint)
	grpcServer.Serve(lis)

	// listen for termination
	sigChan := make(chan os.Signal)
	signal.Notify(sigChan, os.Interrupt)
	signal.Notify(sigChan, os.Kill)

	// "graceful" termination
	sig := <- sigChan
	logger.Println("Received terminate, graceful shutdown", sig)

	_, cancelFunc := context.WithTimeout(context.Background(), 30 * time.Second)
	cancelFunc()
}

// expecting:
// [1] port
func extractArgs(args []string) string {
	return args[1]
}
