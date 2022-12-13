package server

import (
	"context"
	"database/sql"
	"fmt"
	"time"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/protos/accounts"
	"github.com/hashicorp/go-hclog"
)

type AccountsServer struct {
	Logger hclog.Logger
	accounts.UnimplementedAccountsServer
}

type registerUserTransaction struct {
	username string
	password string
}

func NewServer(l hclog.Logger) *AccountsServer {
	return &AccountsServer{Logger: l, UnimplementedAccountsServer: accounts.UnimplementedAccountsServer{}}
}

func (server AccountsServer) Register(ctx context.Context, req *accounts.UserAuthenticationRequest) (*accounts.UserAuthenticationResponse, error) {
	server.Logger.Info("Handle Register", "username", req.Username, "pw", req.Password)
	server.insertUserIntoDb(req.Username, req.Password)
	return &accounts.UserAuthenticationResponse{UserId: "1234", Username: req.Username}, nil
}

func (server AccountsServer) insertUserIntoDb(username string, password string) error {
	fmt.Printf("attempting to interface with db\n")
	db, err := sql.Open("mysql", "accountsservice:accountsservice_pw@tcp(localhost:3306)/accounts")
    defer db.Close()

	if err != nil {
		fmt.Printf("bad stuff happened 1: %s\n", err)
		return err
	}

	query := "INSERT INTO accounts(user_name, authentication_code) VALUES (?, ?)"
	ctx, cancelfunc := context.WithTimeout(context.Background(), 5 * time.Second)
    defer cancelfunc()

    stmt, err := db.PrepareContext(ctx, query)
    if err != nil {
		server.Logger.Error("Error when preparing SQL statement", "error", err)
		return err
    }
    defer stmt.Close()

	res, err := stmt.ExecContext(ctx, username, password)  
	if err != nil {  
		server.Logger.Error("Error when inserting row into accounts table", "error", err)
		return err
	}
	rows, err := res.RowsAffected()  
	if err != nil {  
		server.Logger.Error("Error when finding rows affected", "error", err)
		return err
	}
	server.Logger.Info(fmt.Sprintf("%d users created", rows))

	return nil
}