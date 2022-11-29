package server

import (
	"context"
	"database/sql"
	"fmt"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/protos/accounts"
	"github.com/hashicorp/go-hclog"
)

type AccountsServer struct {
	Logger hclog.Logger
	accounts.UnimplementedAccountsServer
}

func NewServer(l hclog.Logger) *AccountsServer {
	return &AccountsServer{Logger: l, UnimplementedAccountsServer: accounts.UnimplementedAccountsServer{}}
}

func (server *AccountsServer) DoThing() {
	server.Logger.Info("did a thing")
}

func (server AccountsServer) GetExample(ctx context.Context, req *accounts.ExampleRequest) (*accounts.ExampleResponse, error) {
	server.Logger.Info("Handle GetRate", "base", req.ParamOne)
	testDB()
	return &accounts.ExampleResponse{Rate: 0.5}, nil
}

func testDB() {
	fmt.Printf("attempting to interface with db\n")
	db, err := sql.Open("mysql", "accountsservice:pdubz@tcp(localhost:3306)/testdb")
    defer db.Close()

	if err != nil {
		fmt.Printf("bad stuff happened 1: %s\n", err)
		return
	}

    var version string

    err = db.QueryRow("SELECT VERSION()").Scan(&version)

    if err != nil {
		fmt.Printf("bad stuff happened 2: %s\n", err)
    }

    fmt.Printf("got mysql version: %s\n", version)
}