package main

import (
	"context"
	"fmt"
	"log"
	"net"
	"os"
	"os/signal"
	"time"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/accounts_provider"
	gatewaydispatcher "github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/gateway_dispatcher"
	lobbiesServer "github.com/GutpunchGames/Runebreak/runebreak-infra/lobbies/server"
	lobbiesPbs "github.com/GutpunchGames/Runebreak/runebreak-infra/protos/lobbies"
	"github.com/hashicorp/go-hclog"
	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"
)

const serviceName = "runebreak-lobbies-service"

func main() {
	port := extractArgs(os.Args)
	logger := log.New(os.Stdout,serviceName, log.LstdFlags)

	var opts []grpc.ServerOption
	grpcServer := grpc.NewServer(opts...)

	ap := accounts_provider.NewAccountsProvider(logger)

	logger2 := hclog.Default()
	gd := gatewaydispatcher.NewDispatcher(logger2)
	ls := lobbiesServer.NewServer(logger2, ap, gd)
	lobbiesPbs.RegisterLobbiesServer(grpcServer, ls)
	reflection.Register(grpcServer)

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
