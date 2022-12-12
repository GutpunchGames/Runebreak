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

func (server AccountsServer) Register(ctx context.Context, req *accounts.UserAuthenticationRequest) (*accounts.UserAuthenticationResponse) {
	server.Logger.Info("Handle Register", "username", req.Username, "pw", req.Password)
	testDB()
	return &accounts.UserAuthenticationResponse{UserId: "userid", Username: req.Username}
}

func testDB() {
	fmt.Printf("attempting to interface with db\n")
	db, err := sql.Open("mysql", "accountsservice:accountsservice_pw@tcp(localhost:3306)/testdb")
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